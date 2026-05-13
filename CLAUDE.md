# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Project Purpose

Personal reverse-engineering project to restore root access to a Creality K1C 2025 3D printer. Creality removed the root-unlock capability present on earlier K1/K1 Max models. This is the owner's own device.

## Hardware Profile

- **SoC**: Ingenic XBurst2 **X2600E** — MIPS32r2 LE, kernel 5.10.186
- **OS**: Buildroot Linux, GCC 7.2.0 (Ingenic toolchain Release5.1.8-Default_xburst2)
- **Storage**: eMMC (`/dev/mmcblk0`), ~7.3 GB
- **SSH**: Dropbear on port 22, runs at boot via `S50dropbear`
- **Key ports**: WebSocket 9999 (`wsslicer` subprotocol), Moonraker API 7125 (nexusp)

## Repository Layout

```
firmware/
  apps_decrypted/       # 8 app binaries pulled from /tmp/apps/ on rooted device
  sc_patched.ko         # patched soc_security.ko (eFuse + RSA bypass)
ghidra-projects/
  K1C-2025.gpr          # Ghidra project (all 8 app binaries imported)
notes/
  attack-surface.md     # master attack vector map + status
  encryption-chain.md   # full crypto layer breakdown + brick risks
  soc-security-analysis.md  # soc_security.ko RE details
  flows.md              # Mermaid diagrams: boot, exploit, seed.sh, print, cloud
  ipc-protocol-map.md   # inter-daemon IPC protocol map
  recovery-methods.md   # brick recovery options, ranked by viability
  vulnerability-research.md  # additional attack surfaces from static analysis
  firmware-analysis.md  # firmware unpacking, OTA package format
  binary-analysis/      # per-binary: elf-header, sections, strings, imports, r2 functions
tools/
  K1C-2025-Firmware/    # rsync'd filesystem from rooted printer (reference copy)
  Creality-K1C-Tools/   # community tools (root exploit, OTA parser)
    root-exploit/k1c-2025-exploit.py
    OTA-Parser/upg_show.py
  analyze.sh            # Ghidra headless analysis for soc_security.ko + cmd_sc
  ghidra-import-apps.sh # import all apps_decrypted/ into Ghidra project
  ghidra.sh             # launch Ghidra GUI
  static-analysis.sh    # batch strings/readelf/rabin2/r2 on apps_decrypted/
  patch_soc_security.py # generate firmware/sc_patched.ko
  disasm_ko.py          # capstone disassembly of soc_security.ko functions
  reccon/               # recovery console (C, statically linked, MIPS framebuffer terminal)
  ingenic-usbboot/      # USB boot tool for hardware recovery
```

## Common Commands

```bash
# Run the root exploit (requires LAN access to printer)
pip install websocket-client
python3 tools/Creality-K1C-Tools/root-exploit/k1c-2025-exploit.py \
    --host-ip <YOUR_IP> --printer-ip <PRINTER_IP> --public-key ~/.ssh/id_ecdsa.pub
ssh root@<PRINTER_IP>

# Regenerate sc_patched.ko after any patcher change
source .venv/bin/activate
python3 tools/patch_soc_security.py

# Disassemble key soc_security.ko functions (capstone + pyelftools)
source .venv/bin/activate
python3 tools/disasm_ko.py

# Import all app binaries into Ghidra (headless)
./tools/ghidra-import-apps.sh           # all 8 binaries
./tools/ghidra-import-apps.sh vectorp   # single binary

# Open Ghidra GUI with K1C project
./tools/ghidra.sh

# Run headless analysis on soc_security.ko / cmd_sc / upgbox
./tools/analyze.sh [optional-binary-path]

# Batch static analysis on all decrypted app binaries
./tools/static-analysis.sh             # output → notes/binary-analysis/<name>/

# Deploy patched module to printer (NEVER leave loaded at reboot)
scp firmware/sc_patched.ko root@<PRINTER_IP>:/usr/data/
ssh root@<PRINTER_IP> 'rmmod soc_security && insmod /usr/data/sc_patched.ko'
# Restore before reboot:
ssh root@<PRINTER_IP> 'rmmod soc_security && insmod /lib/modules/soc_security.ko'

# Take full eMMC backup (do this before touching any partition)
ssh root@<PRINTER_IP> 'dd if=/dev/mmcblk0 bs=1M | gzip' > k1c_emmc_full.img.gz

# Build reccon (recovery console for printer)
cd tools/reccon && cmake -B build && cmake --build build

# UART connection (baud is 3 Mbps — not 115200)
picocom -b 3000000 --databits 8 --parity n --stopbits 1 /dev/ttyUSB0
```

## Python Environment

A `.venv` exists at project root. Activate it for all Python tool work:
```bash
source .venv/bin/activate
# Key packages: pyelftools, capstone, websocket-client
```
Ghidra requires Java 21: `export JAVA_HOME=/usr/lib/jvm/java-21-openjdk-amd64`  
Ghidra is installed at `/opt/ghidra_12.0.4_PUBLIC`.

## Architecture: Boot and Security Chain

`seed.sh` is sourced by `/etc/init.d/rcS` and acts as the security gate before any app daemon starts. Understanding it is essential for any firmware modification work.

**Boot sequence** (`seed.sh` execution order):
1. `insmod soc_security.ko` → registers `/dev/sc` (all crypto goes through here)
2. `mount_do_userdata` → mounts `/usr/data` (ext4, safe to modify)
3. `upg_do` → if upgrade package present, verify + flash → reboot
4. `decrypt_sn_mac` → AES decrypt serial/MAC from mmcblk0p2
5. `mount_do_deplibs` → `cmd_sc -v /dev/mmcblk0p7` → **FAIL = `halt` (brick point)**
6. `verify_apps` → AES decrypt each `.bin` to `/tmp/apps/` → **FAIL = `halt`**
7. `check_login_permission` → optional permission file to unlock root in shadow
8. `run_system_service` / `run_creality_service` → start daemons

**`/dev/sc` ioctl interface** (all crypto through `soc_security.ko`):
- `SC_CMD_AES (0xc0047301)` — streaming AES-CBC decrypt, ≤2048 bytes/call, **no eFuse check**
- `SC_CMD_VERIFY (0xc0047300)` — full firmware auth: eFuse bits 21+22+23 → magic `SCBT` → AES → RSA-2048 → **requires eFuse bypass for custom packages**

**OTA package format** (two-layer):
- Outer: SCBT-magic envelope verified by `cmd_sc -v` (RSA modulus is caller-supplied at offset 0x3900 — this is the exploitable design flaw)
- Inner: Creality UPG header (424 bytes) + per-partition images with CRC32

## Attack Chain Status

| Step | Attack | Status |
|------|--------|--------|
| 1 | WebSocket RCE → root SSH (port 9999, `wsslicer`, `print` method, Content-Disposition injection) | **Ready to run** |
| 2 | `sc_patched.ko` eFuse+RSA bypass (load interactively post-root, never at boot) | **Ready** |
| 3 | Self-sign custom firmware packages with own RSA-2048 key | **Unblocked once step 2 works** |
| 4 | UART console (3 Mbps, GND/RX2/TX2 header) | Not attempted |
| 5 | USB boot ROM recovery (hold BOOT + press RESET, enumerate as Ingenic USB BOOT DEVICE) | Not tested on X2600E |

**Persistence**: `S999persistence` in `/usr/apps/etc/init.d/` (writable ext4, survives reboot, not erased by OTA that doesn't reformat apps partition).

## Critical Safety Rules

**Brick risk**: `mmcblk0p7` (deplibs squashfs, RSA+eFuse+AES signed) — `halt` on any verification failure. There is no confirmed hardware recovery for the X2600E; the full eMMC backup at `k1c_emmc_full.img.gz` is the only recovery path.

- **Never modify mmcblk0p7 without a working eFuse bypass AND a full partition backup**
- **Never load `sc_patched.ko` at boot** — `seed.sh` calls SC_CMD_VERIFY on mmcblk0p7 at startup; the patched module must only be loaded interactively and unloaded before reboot
- **Always restore original module before reboot**: `rmmod soc_security && insmod /lib/modules/soc_security.ko`
- **Safe partitions** (no halt on failure): mmcblk0p8 (`/usr/apps`), mmcblk0p10 (`/usr/data`)

## App Daemon Map

All 8 daemons are AES-encrypted on disk (`.bin` files on mmcblk0p8), decrypted to `/tmp/apps/` at boot. Ghidra project has all 8 imported.

| Binary | Role | Notable |
|--------|------|---------|
| `vectorp` | UI (LVGL), MQTT, WebSocket 9999 | Root-exploit entry point |
| `nexusp` | File API, Moonraker compat, port 7125 | Hardcoded API key `3fadf317c8d9459780a909de4e56e286` |
| `solusp` | OTA + Klipper bridge (`/tmp/klippy_uds`) | IPC via POSIX shm + semaphores |
| `quintusp` | OTA command dispatcher | Shell injection via IPC message fields |
| `onyxp` + `thirteenthp` | WebRTC (JWT + DTLS/SRTP) | Cloud video streaming |
| `alchemistp` | Camera/file mgmt (Go, stripped) | Connects to hardcoded IP `58.48.202.36` |
| `mdns` | mDNS advertisement | No auth |

IPC: POSIX shared memory + semaphores (solusp), System V message queues (quintusp), named pipes `/tmp/alchemistp_*pipe` (alchemistp), Unix domain sockets for Klipper and H.264 streams.

## Key Reference Files

- `notes/attack-surface.md` — authoritative status of all attack vectors
- `notes/encryption-chain.md` — full crypto chain + bypass workflows + brick risk table
- `notes/soc-security-analysis.md` — soc_security.ko RE, verified patch offsets, RSA call address
- `notes/flows.md` — Mermaid diagrams for boot, exploit, seed.sh, and cloud flows
- `tools/K1C-2025-Firmware/` — full reference filesystem (do not treat as writable target)
- Community Discord: https://discord.gg/FffAZcUJtr
