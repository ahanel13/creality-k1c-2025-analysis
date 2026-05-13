# Creality K1C 2025 — Software Inventory

Firmware version: V1.0.0.26 (CR4SU200382C13)  
Sourced from: eMMC dump + static analysis of decrypted binaries

---

## 1. Creality Proprietary — Closed Source

No source available, no open-source license obligation. Creality's own code.

### App Binaries (encrypted at rest in `/usr/apps/usr/bin/`, decrypted to `/tmp/apps/` at boot)

| Binary | Language | Size | Role |
|--------|----------|------|------|
| `vectorp` | C++ (symbols present) | 3.2 MB | LVGL touchscreen UI, MQTT telemetry client, wsslicer WebSocket server (port 9999) |
| `alchemistp` | Go (stripped) | — | Camera management, print file handling, connects to hardcoded IP `58.48.202.36` |
| `nexusp` | C (symbols present) | — | Moonraker-compatible file/API server (port 7125), SQLite, JWT auth |
| `solusp` | C++ (symbols present) | 575 KB | OTA orchestration, AI/lidar bridge, Klipper WebSocket bridge, libwebsockets server |
| `quintusp` | C | — | OTA command dispatcher, LED/camera/hardware I/O control |
| `onyxp` | C | — | WebRTC signaling (WSS to Creality cloud) |
| `thirteenthp` | C | — | WebRTC DTLS/SRTP media transport, H.264 streams |
| `mdns` | C | — | mDNS/Bonjour service advertisement |

### System Binaries (in `/usr/deplibs`, read-only squashfs)

| Binary | Role |
|--------|------|
| `soc_security.ko` | Kernel module. Registers `/dev/sc`, implements SC_CMD_VERIFY (eFuse + RSA-2048 + AES-CBC) and SC_CMD_AES. Hardware AES key loaded from eFuse at init. |
| `cmd_sc` | Userspace client for `/dev/sc`. Called by `seed.sh` to decrypt/verify firmware blobs. |
| `upgbox` | Firmware update applier. Parses inner UPG package format, writes partition images. |
| `seed.sh` | Boot orchestrator. Loads `soc_security.ko`, decrypts all app binaries, verifies deplibs, optionally unlocks root via permission file, launches init scripts. |

### Proprietary Shared Libraries

| Library | Used by | Notes |
|---------|---------|-------|
| `liboss_c_sdk.so` | vectorp | Alibaba OSS SDK (closed source, Alibaba-proprietary) — log and timelapse upload |
| `libvod_sdk.so` | vectorp | Alibaba VOD SDK (closed source) — video upload |
| `libAIInfer.so` | solusp | AI inference library — runs on ObbrecLidar depth sensor data |
| `libCrLog.so` | onyxp | Creality logging library |
| `librtp.so` | onyxp, thirteenthp | RTP framing library (origin unclear — may be internal or third-party without source) |
| `libhardware2.so` | solusp | Hardware abstraction layer (Android HAL-style, Ingenic BSP) |
| `libutils2.so` | solusp | Utility layer (Ingenic BSP) |

---

## 2. GPL Violations — Open Source, Source Withheld

These components are licensed under GPL/LGPL, which requires Creality to provide
corresponding source code to recipients of the firmware. Source has not been released.

### Klipper Extensions (GPL-3.0)

Klipper is GPL-3.0. Creality ships compiled Python C extension `.so` files for
K1-series printers (confirmed for K2 Plus, likely same pattern for K1C 2025)
without releasing the corresponding C source:

| File | Function |
|------|----------|
| `prtouch_v3_wrapper.cpython-39.so` | Probe/bed leveling touch sensor |
| `filament_rack_wrapper.cpython-39.so` | Multi-filament rack control |
| `motor_control_wrapper.cpython-39.so` | Motor control extensions |
| `serial_485_wrapper.cpython-39.so` | RS-485 serial communication |

Creality's public Klipper fork (`github.com/CrealityOfficial/K1_Series_Klipper`)
covers the K1/K1 Max/K1C but is frozen since 2022 and does not include source for
these extensions. The K1C 2025 firmware (V1.0.0.26) is newer than anything in that repo.

Community discussion: `https://klipper.discourse.group/t/creality-violating-klipper-license/8990`

### Linux Kernel Modifications (GPL-2.0)

The kernel is Linux 5.10.186, built with the Ingenic toolchain. Any Creality-authored
modifications to the kernel (beyond the Ingenic BSP) require source release under GPL-2.0.
No kernel source specific to the K1C 2025 has been published.

---

## 3. Open Source — Available or Upstream

Components with available source, either from upstream or Creality's public repos.

### Klipper (GPL-3.0)

- Python bytecode (`.pyc`) files present in firmware — decompilable
- Partial source at `github.com/CrealityOfficial/K1_Series_Klipper` (frozen 2022)
- Runs via `/tmp/klippy_uds` Unix socket, bridged by `solusp`

### Linux Kernel 5.10.186 (GPL-2.0)

- Base kernel source: `kernel.org`
- Ingenic XBurst2 BSP: Ingenic publishes some BSP source for the X2600 series
- Compiled with GCC 7.2.0 (Ingenic Linux-Release5.1.8-Default_xburst2)

### Third-Party Libraries (linked by app binaries)

| Library | License | Used by | Notes |
|---------|---------|---------|-------|
| `libwebsockets.so.19` | LGPL-2.1 | vectorp, solusp, onyxp, thirteenthp | WebSocket server/client |
| `libssl.so.1.1` / `libcrypto.so.1.1` | Apache-2.0 | most binaries | OpenSSL 1.1.x |
| `libcurl.so.4` | MIT-style | vectorp | HTTP client |
| `libpaho-mqtt3a.so.1` | EPL-2.0 | vectorp | Eclipse Paho MQTT client |
| `libsqlite3.so.0` | Public domain | nexusp | Embedded database |
| `libzip.so.5` | BSD-3-Clause | nexusp | ZIP archive handling |
| `libpng16.so.16` | libpng license | nexusp | PNG image handling |
| `libfreetype.so.6` | FTL/GPL | vectorp | Font rendering |
| `libopencv_*.so.408` | Apache-2.0 | solusp | Computer vision (image decode, processing) |
| `libavformat.so.58` / `libavcodec.so.58` / `libavutil.so.56` / `libswscale.so.5` | LGPL-2.1/GPL | solusp | FFmpeg — video encode/decode |
| `libnice.so.10` | LGPL-2.1 | onyxp, thirteenthp | libnice ICE agent for WebRTC |
| `libsrtp2.so.1` | BSD-3-Clause | onyxp, thirteenthp | SRTP for WebRTC media |
| `libglib-2.0.so.0` / `libgobject-2.0.so.0` | LGPL-2.1 | onyxp, thirteenthp | GLib object system |
| `libjson-c.so.5` | MIT | onyxp | JSON parsing |
| `libcjson.so.1` | MIT | quintusp, onyxp, thirteenthp | Lightweight JSON |
| `libjsoncpp.so.23` | MIT | vectorp, solusp | C++ JSON |
| `libzbar.so.0` | LGPL-2.1 | solusp | QR/barcode scanning |
| `libuuid.so.1` | BSD/LGPL | vectorp, nexusp | UUID generation |
| `libiconv.so.2` | LGPL | solusp | Character encoding |
| `libapr-1.so.0` / `libaprutil-1.so.0` | Apache-2.0 | vectorp | Apache Portable Runtime (used by OSS SDK) |
| `libmxml.so.1` | Apache-2.0 | vectorp | Mini-XML |
| `libc.so.6` / `libm.so.6` / `libpthread.so.0` / `librt.so.1` | LGPL-2.1 | all | GNU C library (glibc 2.29) |
| `libstdc++.so.6` | GPL-3.0 with runtime exception | vectorp, solusp | GNU C++ standard library |
| `libgcc_s.so.1` | GPL-3.0 with runtime exception | vectorp | GCC runtime |

### Other Open-Source System Components

| Component | License | Notes |
|-----------|---------|-------|
| Busybox | GPL-2.0 | Shell utilities (`sh`, `wget`, `udhcpc`, `picocom`, etc.) |
| Dropbear SSH | MIT/custom | SSH daemon, `S50dropbear` init script, already running at boot |
| wpa_supplicant | GPL-2.0 | WiFi client management |
| LVGL | MIT | Embedded GUI library used by vectorp for touchscreen UI |

---

## 4. Unidentified / Unknown Origin

| Component | Notes |
|-----------|-------|
| `alchemistp` hardcoded IP `58.48.202.36` | Go binary, stripped. Destination IP unknown — no hostname, no public documentation. Likely Creality cloud infrastructure. |
| `libAIInfer.so` | AI inference backend for ObbrecLidar. Possibly a vendor SDK from Obbrec. No public source or documentation found. |
| `librtp.so` | Custom or vendored RTP framing library. Not clearly identifiable as a known open-source project. |

---

## 5. What Creality Controls That You Don't Have Source For

Summary of the black boxes that matter most for understanding or modifying the printer:

| Component | Why It Matters |
|-----------|---------------|
| `vectorp` | Everything the touchscreen does. Root UI stub lives here. MQTT telemetry. |
| `soc_security.ko` | All firmware verification and AES decryption gates through this. |
| `alchemistp` | Unknown cloud communication to hardcoded IP. Camera/file role unclear. |
| Klipper `.so` extensions | Bed leveling, motor control, filament rack — physical hardware behavior. GPL violation. |
| `seed.sh` | Full boot and security policy. Read-only on squashfs but readable post-root. |
| `libAIInfer.so` | AI sensor stack used by `solusp`. Closed, unknown vendor. |

---

## References

- Creality K1_Series_Klipper: `https://github.com/CrealityOfficial/K1_Series_Klipper`
- GPL violation thread: `https://klipper.discourse.group/t/creality-violating-klipper-license/8990`
- K2 Plus GPL violations: `https://klipper.discourse.group/t/creality-k2-plus-and-gpl-violations/22402`
- Partition layout: `notes/attack-surface.md`
- Encryption chain: `notes/encryption-chain.md`
- App binary analysis: `notes/binary-analysis/*/analysis.md`
