# Creality K1C 2025: Root Access Research

Reverse-engineering project to restore root access to the **Creality K1C 2025** 3D printer. Creality removed the root-unlock capability present on earlier K1/K1 Max models. This is research on a personally-owned device.

> **DISCLAIMER: Everything in this repository is theoretical and untested. All techniques, exploits, patches, and procedures described here are based on static analysis and reverse engineering only. None of this has been verified to work on real hardware. Attempting any of this on your own device is entirely at your own risk. The authors take no responsibility for bricked printers, voided warranties, or any other damage.**

---

## Hardware

| Property | Value |
|----------|-------|
| SoC | Ingenic XBurst2 **X2600E** (MIPS32r2 LE) |
| Kernel | Linux 5.10.186 |
| OS | Buildroot Linux, GCC 7.2.0 |
| Storage | eMMC (`/dev/mmcblk0`), 10 partitions |
| RAM | ~1 GB |
| Firmware tested | K1C-2025_V1.0.0.26.20251024S |

---

## Getting Root

The exploit script is a fork of [C0DEbrained/Creality-K1C-Tools](https://github.com/C0DEbrained/Creality-K1C-Tools). Full credit to the original author for the initial exploit work. The fork ([ahanel13/Creality-K1C-Tools](https://github.com/ahanel13/Creality-K1C-Tools)) fixes several bugs that prevented it from working on the K1C 2025 firmware (V1.0.0.26.20251024S): incorrect SSH directory permissions that caused dropbear to reject the authorized_keys file, a wrong key type passed to `dropbearkey` for the ecdsa host key, a missing `chattr -i` before unlocking the root account in shadow, a trailing newline in the public key that broke key auth, and a missing thread join that could cause the HTTP server to exit before the printer fetched the payload.

### What you need

- Python 3 + `pip install websocket-client`
- LAN access to the printer (same network)
- An SSH public key (`~/.ssh/id_ecdsa.pub` or similar)

### Run the exploit

```bash
git clone --recurse-submodules https://github.com/ahanel13/creality-k1c-2025-analysis
cd creality-k1c-2025-analysis

python3 tools/Creality-K1C-Tools/root-exploit/k1c-2025-exploit.py \
    --host-ip <YOUR_IP> \
    --printer-ip <PRINTER_IP> \
    --public-key ~/.ssh/id_ecdsa.pub

ssh root@<PRINTER_IP>
```

The exploit injects a shell payload via the WebSocket print API on port 9999. The printer fetches and executes a bootstrap script from your machine, which writes your SSH key and unlocks the root account in the shadow file. A persistence script is deployed to `/usr/apps/etc/init.d/S999persistence` so root SSH survives reboots.

### How the exploit works

The `vectorp` daemon exposes a WebSocket API on port 9999 (subprotocol `wsslicer`). The `print` method accepts a URL for the printer to download a gcode file. The HTTP server's `Content-Disposition` filename is interpolated unsanitized into a shell command. Injecting a semicolon breaks out into arbitrary execution. The payload runs as root via `udhcpc`, which requires `CAP_NET_ADMIN`.

See `notes/attack-surface.md` for full technical details.

---

## Bypassing Firmware Signature Verification

After getting root, `tools/patch_soc_security.py` generates a patched `soc_security.ko` that bypasses the eFuse checks and RSA signature verification in `SC_CMD_VERIFY`. This is required to flash custom firmware packages.

```bash
source .venv/bin/activate
python3 tools/patch_soc_security.py
# output: firmware/sc_patched.ko

# Deploy (NEVER leave loaded at reboot)
scp firmware/sc_patched.ko root@<PRINTER_IP>:/usr/data/
ssh root@<PRINTER_IP> 'rmmod soc_security && insmod /usr/data/sc_patched.ko'

# Restore before reboot
ssh root@<PRINTER_IP> 'rmmod soc_security && insmod /lib/modules/soc_security.ko'
```

**Warning:** The patched module must only be loaded interactively, never at boot. `seed.sh` calls `SC_CMD_VERIFY` on the deplibs partition (`mmcblk0p7`) during every boot. Loading the patched module at boot would corrupt the verification state and halt the device. See [Brick Risks](#brick-risks).

---

## Repository Layout

```
notes/
  attack-surface.md         # all attack vectors + status
  encryption-chain.md       # full crypto chain + bypass workflows
  soc-security-analysis.md  # soc_security.ko RE, verified patch offsets
  flows.md                  # Mermaid diagrams: boot, exploit, seed.sh
  ipc-protocol-map.md       # inter-daemon IPC protocol map
  vulnerability-research.md # additional attack surfaces
  firmware-analysis.md      # OTA package format, unpacking
  binary-analysis/          # per-daemon: strings, imports, Ghidra decompile
tools/
  patch_soc_security.py     # generate sc_patched.ko (eFuse + RSA bypass)
  disasm_ko.py              # capstone disassembly of soc_security.ko
  static-analysis.sh        # batch strings/readelf/rabin2/r2 on app binaries
  analyze.sh                # Ghidra headless analysis
  ghidra-import-apps.sh     # import all app binaries into Ghidra project
  ghidra.sh                 # launch Ghidra GUI
  Creality-K1C-Tools/       # submodule: root exploit + OTA parser
  ingenic-usbboot/          # submodule: USB boot tool for hardware recovery
  reccon/                   # submodule: recovery console (MIPS framebuffer terminal)
```

Not included in this repo (Creality copyright): decrypted app binaries, firmware filesystem, eMMC backup, Ghidra project.

---

## App Daemons

All 8 daemons are AES-encrypted on disk (`mmcblk0p8`), decrypted to `/tmp/apps/` at boot by `seed.sh`.

| Binary | Role | Notes |
|--------|------|-------|
| `vectorp` | UI (LVGL), MQTT, WebSocket 9999 | Exploit entry point |
| `nexusp` | File API, Moonraker compat, port 7125 | |
| `solusp` | OTA + Klipper bridge | IPC via POSIX shm + semaphores |
| `quintusp` | OTA command dispatcher | Shell injection via IPC message fields |
| `onyxp` + `thirteenthp` | WebRTC (JWT + DTLS/SRTP) | Cloud video streaming |
| `alchemistp` | Camera/file management (Go, stripped) | Connects to hardcoded cloud IP |
| `mdns` | mDNS advertisement | No auth |

---

## Boot and Security Chain

`seed.sh` is sourced by `/etc/init.d/rcS` and is the security gate before any daemon starts:

1. `insmod soc_security.ko`: registers `/dev/sc` (all crypto goes through here)
2. `mount_do_userdata`: mounts `/usr/data` (ext4, safe to modify)
3. `upg_do`: if an OTA package is present, verify + flash → reboot
4. `decrypt_sn_mac`: AES decrypt serial/MAC from `mmcblk0p2`
5. `mount_do_deplibs`: `cmd_sc -v /dev/mmcblk0p7` → **FAIL = `halt`**
6. `verify_apps`: AES decrypt each `.bin` to `/tmp/apps/` → **FAIL = `halt`**
7. `check_login_permission`: optional permission file to unlock root in shadow
8. `run_system_service` / `run_creality_service`: start daemons

---

## Brick Risks

The primary brick condition is `mmcblk0p7` (deplibs squashfs, RSA+eFuse+AES signed) failing verification. `seed.sh` halts with no recovery prompt on any failure.

**Safe partitions** (no halt on failure): `mmcblk0p8` (`/usr/apps`), `mmcblk0p10` (`/usr/data`)

**Rules:**
- Take a full eMMC backup before modifying any partition: `ssh root@<IP> 'dd if=/dev/mmcblk0 bs=1M | gzip' > k1c_emmc_full.img.gz`
- Never modify `mmcblk0p7` without a working eFuse bypass AND a full partition backup
- Always restore original `soc_security.ko` before rebooting
- Never load `sc_patched.ko` at boot

Hardware recovery via Ingenic USB boot ROM mode (hold BOOT + press RESET, enumerate as `Ingenic USB BOOT DEVICE`) is untested on the X2600E but confirmed working on the older X2000E-based K1/K1 Max. See `notes/recovery-methods.md`.

---

## UART

UART is available on the mainboard header (GND/RX2/TX2). Baud rate is **3,000,000 bps**: not the standard 115200.

```bash
picocom -b 3000000 --databits 8 --parity n --stopbits 1 /dev/ttyUSB0
```

---

## Community

Discord: https://discord.gg/FffAZcUJtr
