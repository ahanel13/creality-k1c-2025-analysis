# Creality K1C 2025 — Encryption Chain Analysis

## System Overview

The K1C 2025 uses a multi-layer encryption and verification scheme built around
a dedicated kernel module (`soc_security.ko`) and Ingenic X2600E hardware
security peripherals. All cryptographic enforcement gates through `/dev/sc`.

**Key facts:**
- SoC: Ingenic XBurst2 X2600E (MIPS32r2 LE, kernel 5.10.186)
- AES engine MMIO: `0xb342_0000`
- eFuse controller MMIO: `0xb348_0000`
- Hardware AES key: 24 bytes, loaded from eFuse into kernel BSS at module init
- RSA: software implementation (pure bignum), 2048-bit, key provided by caller

---

## Boot-Time Verification Checkpoints

`seed.sh` runs as PID 1's init and performs verification at three points.
**All failures call `halt` — there is no recovery prompt.**

```
insmod /lib/modules/soc_security.ko
        ↓
mount_do_userdata()          ← ext4, no crypto check
        ↓
decrypt_sn_mac()             ← cmd_sc decrypts serial/MAC from mmcblk0p2
        ↓
mount_do_deplibs()           ← cmd_sc -v src=/dev/mmcblk0p7
        │                       VERIFY deplibs squashfs (RSA+eFuse+AES)
        │                       FAIL → halt  ← BRICK POINT
        ↓
mount_do_apps()              ← ext4, no crypto check
        ↓
verify_apps()                ← cmd_sc src=app.bin dst=/tmp/apps/app (AES decrypt)
        │                       for: alchemistp nexusp onyxp quintusp thirteenthp solusp vectorp mdns
        │                       FAIL → halt
        ↓
check_login_permission()     ← optional: cmd_sc -v src=/usr/data/permission
        │                       if signed permission file + MAC match → unlocks root in /tmp/shadow
        ↓
run_system_service()         ← /etc/appetc/init.d/S??*  (= /usr/apps/etc/init.d/)
run_creality_service()       ← /etc/appetc/init.d/CS??* (runs as creality user)
```

---

## Encryption Layers

### Layer 1 — App Binary Encryption (AES-CBC, hardware key)

- **What:** App binaries on `mmcblk0p8` stored as `.bin` files
- **Where:** `/usr/apps/usr/bin/alchemistp.bin`, `nexusp.bin`, etc.
- **How decrypted:** `cmd_sc src=app.bin dst=/tmp/apps/app` at every boot
- **Key:** Hardware AES key from eFuse, never exposed in software
- **Post-root bypass:** Decrypted binaries are already in `/tmp/apps/` after boot — just copy them out. No crypto work needed.

### Layer 2 — Deplibs Partition Verification (AES + RSA-2048 + eFuse)

- **What:** Squashfs containing `/usr/deplibs` (main rootfs, signed by Creality)
- **Where:** `mmcblk0p7`
- **How verified:** Full `SC_CMD_VERIFY` pipeline (input buffer = 2048 bytes from mmcblk0p1):
  1. eFuse bits 21/22/23 must be burned (production enforcement)
  2. Magic header `SCBT` at input[0x000]
  3. AES DMA: `input[0x200]` = physical RAM address of firmware image; AES engine reads from that address
  4. RSA-2048: modulus at `input[0x300]` (→ MMIO+0x3900), signature at `input[0x500]` (→ MMIO+0x3b00) — **both caller-supplied**
- **Brick risk:** This runs at every boot. If verification fails → `halt`.
- **Note:** The SCBT signature block lives on `mmcblk0p1`, not embedded in mmcblk0p7.
  mmcblk0p7 is raw squashfs (`hsqs`); mmcblk0p1 starts with `SCBThsqs`.

### Layer 3 — Firmware Update Packages (same pipeline as Layer 2)

- **What:** OTA update `.img` files placed in `/usr/data/upgrade/state`
- **How verified:** `cmd_sc -v src=upgfile` — identical `SC_CMD_VERIFY` path
- **Note:** The RSA modulus is embedded in the update package, not burned into hardware. This is exploitable — see bypass section below.

### Layer 4 — SN/MAC Partition (AES, base64-wrapped)

- **What:** Serial number and MAC address
- **Where:** `mmcblk0p2`
- **How decrypted:** `cmd_sc src=/tmp/sn_mac.signed dst=/tmp/params`
- **Format:** First 4 bytes = LE length, then base64-encoded AES blob
- **Post-root:** Params land in `/tmp/params` at boot — readable directly.

---

## `/dev/sc` ioctl Interface

| ioctl          | Name           | eFuse check | RSA check | Use case                        |
|----------------|----------------|-------------|-----------|-------------------------------|
| `0xc0047301`   | SC_CMD_AES     | **No**      | No        | Streaming AES-CBC decrypt, ≤2048 bytes/call |
| `0xc0047300`   | SC_CMD_VERIFY  | **Yes**     | Yes       | Full firmware package auth + decrypt |

`SC_CMD_AES` is the low-risk path. `SC_CMD_VERIFY` is gated by eFuse and is what we need to bypass for custom firmware.

---

## The RSA Design Flaw — UPDATED 2026-05-13

The RSA public key modulus is **supplied by the caller in the input buffer** at
**input offset `0x300`** (which maps to MMIO+0x3900 via the AES copy loop).
The verifier performs `rsa_public_decrypt(sig, modulus_from_mmio, ...)` using
caller-supplied values — it does not compare the modulus against any hardware-burned value.

Security depends on eFuse bits 21–23 being set on production units (which they are —
confirmed by the fact that SC_CMD_VERIFY succeeds at every boot and our test showed
no eFuse error). The eFuse check prevents unauthorized callers from reaching the RSA step.

**Confirmed:** eFuse bits ARE burned on this production printer (2026-05-13 test).
The eFuse check passes in the unpatched original module.

**RSA return value is discarded** (confirmed by disassembly at 0x1614):
After `jalr $v0` (RSA call), the return value in `$v0` is immediately overwritten by
`addiu $v0, $s0, 4`. The subsequent check at 0x1624 is a **userspace pointer validity
check** on the output buffer `$s0`, NOT a check on the RSA result.

**Implication for Option B (self-signing without module patch):**
On a production printer with burned eFuse, the original unpatched module can be used
to verify self-signed packages:
1. Generate your own RSA-2048 keypair
2. Load firmware image into a physical RAM buffer (physical address needed)
3. Fill SCBT input buffer: modulus at input[0x300], signature at input[0x500], physical address at input[0x200]
4. Call SC_CMD_VERIFY ioctl directly — RSA result is discarded, eFuse passes naturally

The main open question is how to obtain/provide the physical RAM address for
the DMA step. cmd_sc handles this internally via some pre-loading mechanism.

---

## AES Key — Where It Lives

`sc_open` (called on every `/dev/sc` open) loads 24 bytes from kernel BSS
(`&info + 0xbc`) into AES engine MMIO registers `0xb342_2000`–`0xb342_2014`.
These 24 bytes are the hardware AES key, populated from eFuse during module init.

The key is **never returned to userspace** and is not in any file on disk.

**To extract it post-root:**
- Load a custom `.ko` that calls `symbol_get("sc_open")`, walks the BSS to
  `module_base + bss_offset + 0xbc`, and copies 24 bytes to userspace.
- Alternatively, read kernel memory via `/dev/mem` if `CONFIG_STRICT_DEVMEM` is not set.

**When you need this:** Only if you want to encrypt new app binaries completely
offline (e.g., build a custom app binary without using the printer's hardware).
For most goals (modifying system behavior, adding packages, reflashing deplibs),
you do not need the raw key — you can use `SC_CMD_AES` through `/dev/sc`.

---

## Bypass Considerations

### Consideration 1 — The patched module must never load at boot

`seed.sh` calls `cmd_sc -v src=/dev/mmcblk0p7` (SC_CMD_VERIFY) immediately after
`insmod soc_security.ko`. If the patched module is what loads, this call will hang
(due to the eFuse patch bug — see soc-security-analysis.md) or bypass verification
silently. Either way, **do not persist the patched module as the boot-time module**.

Safe use: load interactively post-root SSH for a specific operation, then unload.

```bash
# Load patched module interactively
rmmod soc_security
insmod /usr/data/sc_patched.ko

# ... do your work with cmd_sc ...

# Restore original before next reboot
rmmod soc_security
insmod /lib/modules/soc_security.ko
```

### Consideration 2 — Safe vs. brick-risk partitions

| Partition    | Mount            | Writable | Verified at boot | Brick risk if corrupted |
|--------------|------------------|----------|------------------|-------------------------|
| mmcblk0p2    | (SN/MAC)         | No       | AES decrypt only | Low (no halt on fail)   |
| mmcblk0p5    | (kernel)         | No       | Unknown          | **High**                |
| mmcblk0p7    | `/usr/deplibs`   | No       | RSA+eFuse+AES    | **Critical — halt**     |
| mmcblk0p8    | `/usr/apps`      | **Yes**  | AES decrypt only | Low (apps fail, no halt)|
| mmcblk0p9    | (rootfs_data)    | Yes      | None             | None                    |
| mmcblk0p10   | `/usr/data`      | **Yes**  | None             | None                    |

**Rule:** Never modify mmcblk0p7 without a tested, working bypass and a full partition backup.

### Consideration 3 — Backup before anything

Before touching any partition:
```bash
# Full eMMC image backup (requires root + sufficient remote storage)
dd if=/dev/mmcblk0 bs=1M | ssh user@host 'cat > k1c_emmc_full.img'

# Or partition by partition (safer over slow links)
dd if=/dev/mmcblk0p7 bs=1M | gzip | ssh user@host 'cat > mmcblk0p7_deplibs.img.gz'
```

With no hardware recovery method confirmed for the X2600E, this backup IS the
recovery plan.

### Consideration 4 — eFuse bits are permanent

eFuse bits 21/22/23 are one-time programmable and are burned on production units.
There is no way to un-burn them. The bypass must go through software (patched
module) — hardware enforcement cannot be removed.

### Consideration 5 — Firmware updates will undo root persistence

A Creality OTA update rewrites mmcblk0p7 (deplibs) and mmcblk0p8 (apps). The
`S999persistence` script on `/usr/apps/etc/init.d/` survives this only if the apps
partition is not reformatted. Monitor for updates and disable the auto-update
service once persistent root is confirmed stable.

---

## Practical Decryption Workflow (Post-Root)

### Read encrypted app binaries
```bash
# Already decrypted at boot — just grab them
cp /tmp/apps/nexusp /usr/data/nexusp_decrypted
cp /tmp/apps/alchemistp /usr/data/alchemistp_decrypted
```

### Decrypt an arbitrary AES blob using hardware
```bash
# SC_CMD_AES via cmd_sc — up to 2048 bytes per call, no eFuse check
cmd_sc src=/path/to/encrypted.bin dst=/tmp/decrypted.bin
```

### Read the mounted deplibs squashfs
```bash
# Already mounted read-only at /usr/deplibs — just read it
cp -r /usr/deplibs /usr/data/deplibs_extracted/
# Or repack to squashfs on your host:
# ssh root@printer 'tar czf - /usr/deplibs' > deplibs.tar.gz
```

### Use patched module for SC_CMD_VERIFY bypass
```bash
# Fix sc_patched.ko first (see soc-security-analysis.md)
scp sc_patched.ko root@<printer_ip>:/usr/data/

rmmod soc_security
insmod /usr/data/sc_patched.ko

# Verify a self-signed package (after fixing the patcher bug)
cmd_sc -v src=/usr/data/my_custom_package.img
```
