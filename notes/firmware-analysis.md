# Firmware Analysis Notes

## Obtaining Firmware
- Official update packages: https://www.creality.com/pages/download-k1c (check for 2025 model variant)
- File formats seen on prior K1: `.img` wrapped in `.zip` or a `.tar.gz` bundle
- Also check: Creality GitHub org, third-party mirrors

## Unpacking Workflow

```bash
# 1. Identify file type
file firmware.img

# 2. Try binwalk scan
binwalk -e firmware.img

# 3. If squashfs found
unsquashfs -d rootfs/ squashfs-root.squashfs

# 4. If ext4 partition
sudo mount -o loop,ro partition.img /mnt/firmware

# 5. For Rockchip .img (RK format)
# Use: https://github.com/neo-technologies/rockchip-mkbootimg
# Or: rkdeveloptool / upgrade_tool from Rockchip SDK
```

## Key Files to Inspect
- `/etc/shadow` — hashed root password (attempt offline crack or look for well-known hashes)
- `/etc/passwd` — user list, shells
- `/etc/ssh/sshd_config` — is SSH enabled? What auth methods?
- `/etc/init.d/` or `/etc/rc*` — startup scripts, look for debug modes
- `/usr/data/` — Creality-specific app data, common location for their scripts
- `/root/` — root homedir, may have authorized_keys or scripts
- `/etc/sudoers` — privilege escalation paths

## Shadow Hash Attack
If shadow is accessible:
```bash
# Extract hash
grep root /etc/shadow

# Crack with hashcat (assuming bcrypt or sha512crypt)
hashcat -m 1800 hash.txt /usr/share/wordlists/rockyou.txt

# Or john
john --wordlist=/usr/share/wordlists/rockyou.txt shadow.txt
```

## OTA Package Format (two-layer structure)

Firmware update packages have two distinct layers:

```
┌─────────────────────────────────────────────────────────┐
│  OUTER LAYER — verified by cmd_sc -v (soc_security.ko)  │
│  Format: SCBT-magic envelope                            │
│    offset 0x000  : magic 0x54424353 ("SCBT")            │
│    offset 0x200  : AES-CBC encrypted body               │
│    offset 0x3900 : RSA-2048 modulus (caller-supplied)   │
│    offset 0x3b00 : RSA signature                        │
│  Verified via SC_CMD_VERIFY ioctl on /dev/sc            │
│  eFuse bits 21-23 + RSA check — needs bypass to forge   │
├─────────────────────────────────────────────────────────┤
│  INNER LAYER — parsed by upgbox after verification      │
│  Format: Creality UPG package                           │
│  Package header (424 bytes):                            │
│    name[128], desc[64], sn[64], version[32]             │
│    build_time[8], size[8], img_count[4]                 │
│    write_mode[4], hd_crc32[4]                           │
│  Per-image node descriptors:                            │
│    img_name[128], partition[64], size[8], offset[8]     │
│    write_offset[8], img_crc32[4], node_crc32[4]         │
│  Raw partition images follow (CRC32 verified)           │
└─────────────────────────────────────────────────────────┘
```

**Boot-time flow:**
1. `seed.sh` calls `cmd_sc -v src=upgfile` → verifies outer SCBT layer (halt on fail)
2. `upgbox -U -f upgfile` → parses inner UPG layer, writes each image to its partition
3. Reboot applies the flashed partitions

**Tooling:**
- `tools/Creality-K1C-Tools/OTA-Parser/upg_show.py` — inspect inner UPG layer metadata and extract partition images
- `tools/patch_soc_security.py` + `firmware/sc_patched.ko` — bypass outer SCBT verification
- To forge a complete update: build inner UPG → wrap in SCBT with self-signed RSA key → bypass outer check with patched module

## Notes
