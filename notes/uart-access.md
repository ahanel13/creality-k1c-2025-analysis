# UART Access Notes

## Equipment Needed
- USB-to-UART adapter (CP2102, CH340, or FTDI) — **must be 3.3V logic level**
- Dupont jumper wires
- Soldering iron + fine tip (may need to solder to test pads)
- Multimeter (for continuity and voltage verification)

## Finding UART Pads
1. Open printer enclosure (typically 4-6 screws on bottom/back)
2. Locate main control board
3. Look for: labeled test pads (TX, RX, GND), 4-pin headers, unpopulated connectors
4. Prior K1 mainboard had pads near edge, labeled clearly
5. Verify with multimeter: GND = 0V, TX = ~3.3V idle (logic high), RX = ~3.3V idle

## Wiring
```
Printer Board    ->    USB-UART Adapter
TX               ->    RX
RX               ->    TX  
GND              ->    GND
(do NOT connect VCC — printer is self-powered)
```

## Confirmed Configuration (from /proc/cmdline)

```
console=ttyS2,3000000n8
```

- **Device**: ttyS2 (UART2 on Ingenic X2600E)
- **Baud**: 3,000,000 (3 Mbps)
- **Format**: 8N1 (8 data bits, no parity, 1 stop bit)
- **`fw_printenv` not accessible from userspace** — u-boot environment only visible via UART

Full kernel cmdline:
```
console=ttyS2,3000000n8 mem=242M@0x0 rmem=13M@0xf200000 rtos_size=1M@0xff00000
rdinit=/linuxrc root=/dev/ram0 rootwait rootfstype=ramfs rw clk_ignore_unused
```

Note: `root=/dev/ram0 rootfstype=ramfs` — the entire `/` is loaded into RAM at boot.
All writes to `/root/`, `/etc/`, `/tmp/` etc. are volatile and wiped on reboot.
Only `/usr/apps` (mmcblk0p8) and `/usr/data` (mmcblk0p10) persist across reboots.

## Connection

```bash
# Find the device
ls /dev/ttyUSB*

# Connect — must use 3,000,000 baud
picocom -b 3000000 --databits 8 --parity n --stopbits 1 /dev/ttyUSB0
# or
screen /dev/ttyUSB0 3000000
```

## What to Look For on Boot
- U-Boot banner: shows SoC (Ingenic X2600E), RAM, u-boot version
- U-Boot countdown: press any key to interrupt → get u-boot shell
- Kernel boot messages
- `fw_printenv` / `fw_setenv` available from u-boot shell directly

## U-Boot Shell — Recovery Commands

```
# Check eMMC partitions
mmc part

# Boot from SD card (potential recovery path)
mmc dev 1; fatload mmc 1:1 0x80000000 boot.img; bootm 0x80000000

# Override init for root shell (bypasses seed.sh entirely)
setenv bootargs "console=ttyS2,3000000n8 root=/dev/ram0 rootfstype=ramfs rdinit=/bin/sh"
boot

# Dump mmcblk0p7 (deplibs) to TFTP for backup/restore
tftpput 0x80000000 <size> deplibs.img

# Write a partition image from TFTP (recovery)
tftpboot 0x80000000 deplibs.img
mmc write 0x80000000 <start_block> <block_count>
```

## Notes
