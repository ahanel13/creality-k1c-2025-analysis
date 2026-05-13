# Creality K1C 2025 — Brick Recovery Research

## What Causes a Brick

The primary brick condition is `mmcblk0p7` (deplibs, signed squashfs) failing
verification at boot. `seed.sh` calls `cmd_sc -v src=/dev/mmcblk0p7` immediately
after loading `soc_security.ko`. Any failure → `halt`. No recovery prompt, no retry.

Secondary brick conditions:
- Corrupt U-Boot or SPL (first ~1 MB of eMMC)
- Corrupt kernel (`mmcblk0p5`)

`mmcblk0p8` (apps, ext4) and `mmcblk0p10` (userdata) cannot cause a boot halt —
failures there result in degraded function, not a brick.

---

## Recovery Methods — Ranked by Viability

### Method 1: Ingenic USB Boot ROM Mode — MOST PROMISING

**Confidence:** High for X2000E (older K1/K1 Max), likely for X2600E (K1C 2025)  
**Status:** Untested on X2600E, confirmed working on X2000E-based K1/K1 Max

The Ingenic XBurst2 bootROM has a USB recovery mode that predates any OS or
firmware loading. It operates below U-Boot, below `seed.sh`, below eFuse checks
(standard Ingenic pattern — eFuse enforcement begins at SPL/U-Boot, not in ROM code).

#### Trigger Procedure
1. Locate the **BOOT** button on the mainboard (physical button, near PCB edge)
2. Hold **BOOT**, press and release **RESET**
3. Hold **BOOT** for ~3 seconds, then release
4. Device enumerates over USB as `Ingenic USB BOOT DEVICE`
5. Use a data-capable USB cable (power-only cables will not work)

The USB-C port on the board is the interface (same port used for USB0).

#### Tools (Linux)
```bash
# ingenic-usbboot — community tool, supports X2000E, likely X2600E
git clone https://github.com/ballaswag/ingenic-usbboot
cd ingenic-usbboot
make
./ingenic-usbboot

# gcwnow/ingenic-boot — alternative generic Ingenic USB boot tool
git clone https://github.com/gcwnow/ingenic-boot
```

Windows: Ingenic USB Cloner (official vendor tool, available from Ingenic directly)

#### What USB Boot Mode Can Do
- Load an SPL into TCSM (SRAM at `0xb2401000`) via USB
- SPL runs at `0xb2401800`, initializes DDR
- Load U-Boot to `0x80100000` and execute
- From a running U-Boot: read/write eMMC partitions, TFTP, etc.

#### eFuse Unknown Factor
The critical unknown: does the X2600E bootROM enforce eFuse secure boot, or does
it run unsigned code freely? For X2000E the answer is "freely" — the eFuse checks
are in `soc_security.ko`, not the ROM. If X2600E follows the same pattern, USB boot
mode completely bypasses all firmware verification.

**To verify:** Attempt USB boot mode with BOOT+RESET. If device enumerates as
`Ingenic USB BOOT DEVICE`, the ROM is accessible regardless of eFuse state.

#### Reference: K1/K1 Max (X2000E) Recovery Tools
- WebUSB unbrick tool: `https://ballaswag.github.io/creality-k1-unbrick-tool-js/`
- Creality Helper Script firmware recovery: `https://guilouz.github.io/Creality-Helper-Script-Wiki/firmwares/firmware-recovery-k1/`

---

### Method 2: U-Boot Interrupt via UART — WORTH TESTING

**Confidence:** Low — `bootdelay=0` suspected  
**Status:** Untested. serial.md notes "any key pressed before login leads to kernel crash"

If U-Boot has any autoboot delay, a UART break signal or keypress during that window
drops to a U-Boot shell — from which the entire eMMC is accessible.

The "kernel crash on keypress" note from serial.md likely describes pressing keys
AFTER U-Boot has already handed off to the kernel, not during U-Boot itself.
The U-Boot countdown window may simply be too fast to catch manually.

#### Testing Procedure
1. Connect UART (see `notes/uart-access.md` — 3 Mbps, 8N1, TX/RX/GND header)
2. Power cycle the printer while watching UART output
3. The moment U-Boot banner appears, send a BREAK signal or spam any key
4. In `picocom`: `Ctrl+A`, `Ctrl+\` sends a break
5. In `screen`: `Ctrl+A`, `B` sends a break

#### If U-Boot Shell Is Accessible
```bash
# Option A: Bypass seed.sh entirely — boot to root shell without any verification
setenv bootargs "console=ttyS2,3000000n8 root=/dev/ram0 rootfstype=ramfs rdinit=/bin/sh"
boot
# From root shell: dd restore mmcblk0p7 from backup

# Option B: TFTP restore of deplibs partition
# On host: run tftpd with mmcblk0p7 backup image
setenv serverip 192.168.1.x
setenv ipaddr 192.168.1.y
tftpboot 0x80000000 mmcblk0p7.img
# p7 starts at sector 55296, size 614400 sectors (300 MB / 512)
mmc write 0x80000000 55296 614400

# Option C: Read U-Boot environment (could reveal bootdelay setting)
printenv bootdelay
printenv bootcmd
```

#### Modifying bootdelay (if shell accessible)
```bash
# Set bootdelay to 3 seconds for future recovery window
setenv bootdelay 3
saveenv
# Now future boots give a 3-second interrupt window without UART timing pressure
```

---

### Method 3: eMMC Direct Access (Physical)

**Confidence:** Medium (hardware-dependent)  
**Status:** Not attempted — requires board inspection

eMMC chips communicate over a standard interface (CMD, CLK, DAT0-7). If the PCB
exposes these as test points (common on manufacturer boards for factory programming),
they can be connected to an eMMC programmer or a Linux host with SD card reader
in eMMC-compatible mode.

#### Steps to Investigate
1. Open printer enclosure, remove mainboard
2. Photograph both sides of board at high resolution
3. Look for unpopulated headers or labeled test pads near the eMMC chip
4. eMMC pinout: CMD (command), CLK (clock), DAT0-DAT7 (data), VSS (ground)
5. If accessible: connect to `mmc-utils` on Linux host in SD compatibility mode

eMMC chips also support a "force download" mode via DAT0 being held low during
power-on — similar in concept to the USB boot ROM approach.

**Fallback:** Desolder the eMMC BGA chip and read/write in a programmer socket.
Requires BGA rework skills and carries risk of pad damage. Last resort only.

---

### Method 4: JTAG

**Confidence:** Low — no pin documentation found  
**Status:** Theoretical only

Ingenic XBurst2 supports EJTAG (MIPS JTAG). OpenOCD has XBurst support
(`github.com/XBurst/OpenOCD-XBurst`). If JTAG pads can be identified on the board,
this provides CPU-level halt and full memory/storage access regardless of software state.

No K1C 2025 JTAG pin documentation exists publicly. Would require tracing from the
X2600E BGA pads using a multimeter or high-resolution board photos.

---

## Pre-Emptive Recovery Setup (Do This Now, While Root Works)

The best recovery is one set up before anything goes wrong.

### Step 1: Full eMMC Backup — CRITICAL
```bash
# From root SSH on the printer
dd if=/dev/mmcblk0 bs=1M | gzip | ssh user@HOST 'cat > k1c_emmc_full.img.gz'

# Verify size (~7.3 GB uncompressed, ~430 MB sparse — mostly zeros)
# Already done: k1c_emmc_full.img.gz exists in project root
```

### Step 2: Partition-Level Backups (faster to restore)
```bash
# deplibs — the one that bricks on corruption
dd if=/dev/mmcblk0p7 bs=1M | gzip | ssh user@HOST 'cat > mmcblk0p7_deplibs.img.gz'

# kernel — brick risk if corrupted
dd if=/dev/mmcblk0p5 bs=1M | gzip | ssh user@HOST 'cat > mmcblk0p5_kernel.img.gz'

# SPL + U-Boot (first 1 MB)
dd if=/dev/mmcblk0 bs=512 count=2048 | gzip | ssh user@HOST 'cat > emmc_first1mb.img.gz'
```

### Step 3: Test UART NOW
Before doing anything risky, establish UART and test the U-Boot interrupt window.
If U-Boot can be interrupted, Method 2 becomes a reliable recovery path for any
future brick scenario. This is the highest-value test to run next.

### Step 4: Test USB Boot ROM Mode NOW
While the printer boots normally, test whether holding BOOT + pressing RESET while
plugged in via USB causes the device to enumerate as `Ingenic USB BOOT DEVICE`.
If yes, Method 1 is confirmed and you have hardware-level recovery regardless of
what you do to the firmware.

---

## Partition Reference for Recovery

| Partition | Start Sector | Size | Brick Risk | Notes |
|-----------|-------------|------|------------|-------|
| SPL+UBoot | 0 | ~2048 sectors | Critical | First ~1 MB of eMMC |
| mmcblk0p5 (kernel) | 22528 | 16384 | High | AES+signed |
| mmcblk0p6 (kernel2) | 38912 | 16384 | High | Backup kernel |
| mmcblk0p7 (deplibs) | 55296 | 614400 | **Critical** | RSA+eFuse+AES, halt on fail |
| mmcblk0p8 (apps) | 669696 | 614400 | None | ext4, no halt on fail |
| mmcblk0p10 (userdata) | 1488896 | 13781000 | None | ext4, no verification |

---

## Unknown / Needs Investigation

- Does the X2600E bootROM enforce eFuse checks (blocking USB recovery on production units)?
- Does the K1C 2025 physically have a labeled BOOT button, or must it be identified on the PCB?
- Does U-Boot `bootdelay` have any value other than 0 — check with `fw_printenv bootdelay` via UART
- Are there eMMC test points accessible on the CR4SU200382C13 mainboard?
- Does kernel2 (mmcblk0p6) provide any A/B fallback if kernel (mmcblk0p5) fails?

---

## References

- Ingenic USB boot tool: `https://github.com/ballaswag/ingenic-usbboot`
- K1/K1 Max unbrick (X2000E precedent): `https://ballaswag.github.io/creality-k1-unbrick-tool-js/`
- UART notes: `notes/uart-access.md`
- Partition layout: `notes/attack-surface.md`
- Encryption chain + brick risks: `notes/encryption-chain.md`
