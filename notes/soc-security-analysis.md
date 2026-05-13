# soc_security.ko — Full Reverse Engineering Analysis

## SoC Correction
- **Previous assumption**: Rockchip RK3566
- **Actual SoC**: Ingenic XBurst2 X2600E (MIPS32r2 LE, kernel 5.10.186)
- MMIO base for security/AES engine: `0xb342_0000`
- MMIO base for eFuse controller: `0xb348_0000`
- GCC 7.2.0, Ingenic toolchain (Release5.1.8-Default_xburst2)

---

## Module Overview

`soc_security.ko` registers `/dev/sc` as a Linux misc device.  
`seed.sh` loads it at boot; `cmd_sc` is the userspace client that calls into it.

**Symbol table (not stripped):**
- `sc_init / sc_exit` — `init_module / cleanup_module` wrappers
- `sc_open / sc_release` — file ops
- `sc_ioctl` — all command dispatch
- `sc_clean` — AES engine teardown
- `pdma_wait` — MIPS wait/halt loop used for PDMA polling
- `rsa_public_decrypt` — software RSA-2048 (calls `bn_mod_exp` + `bn_encode`)
- `f_rsa_public_decrypt` — **global function pointer** in `.data`, default = `rsa_public_decrypt`

**Hardware clocks enabled on load:**
`gate_ddr`, `gate_aes`, `gate_pdma`, `gate_efuse`, `gate_dtrng`, `gate_hash`

---

## ioctl Interface

Two commands:

| ioctl code   | Name           | Description                        |
|--------------|----------------|------------------------------------|
| `0xc0047300` | SC_CMD_VERIFY  | Full firmware verify + AES decrypt |
| `0xc0047301` | SC_CMD_AES     | Streaming AES block decrypt        |

### SC_CMD_AES (0xc0047301) — text offset 0x1208

- Accepts up to `0x800` (2048) bytes from userspace
- Sets up hardware AES engine registers at `0xb342_288x`
  - `0x2880`: mode byte (`0x16` = AES-CBC decrypt)
  - `0x2884`: IV/key selector
  - `0x2888`: control (`0x8000`)
  - `0x288c`: data source address
  - `0x2890`: data length
  - `0x1030`: trigger (`ori current, 0x108`)
- Polls `0xb342_2888 < 0` (PDMA busy-wait loop)
- Copies decrypted output back to userspace

### SC_CMD_VERIFY (0xc0047300) — text offset 0x1420

Full firmware package authentication:

**Step 1 — eFuse bit checks** (text 0x1484–0x14ac):
```
Read [0xb348_0008]:
  bit 21 must be 1  → eFuse "key burned" flag
  bit 22 must be 1  → eFuse secondary flag
  bit 23 must be 1  → eFuse tertiary flag
```
Any bit = 0 → `printk("error! please sign your file or burn key!!")` and return -1.

**Step 2 — Magic header check** (text 0x14b0–0x14bc):
```
input_buf[0] == 0x54424353  ("SCBT" little-endian)
```

**Step 3 — AES hardware setup** (text 0x14c4–0x1598):
- Copies data from input_buf offsets 0x200–0x5fc to AES engine MMIO
- Sets AES control registers, triggers PDMA transfer
- Busy-waits for completion polling `0xb342_2888`

**Step 4 — RSA signature check** (text 0x1604–0x1610):
```c
f_rsa_public_decrypt(
    input_buf + 0x3b00,  // RSA signature ciphertext
    input_buf + 0x3b00,  // (a0 = a1 from delay slot)
    0x40,                // 64 words = RSA-2048 key length
    input_buf + 0x3900,  // RSA modulus
    ...                  // stack args: exponent buffer, exp_len
);
```

**Step 5 — Success** (text 0x1628–0x1658):
- Copies 4 bytes to userspace
- Sets `info.authenticated = 1`
- Returns 0

---

## sc_open — AES Key Setup (text 0x1128)

On every `/dev/sc` open, loads 24 bytes from `BSS+0x10cc` (= `info + 0xbc`) into AES key registers `0xb342_2000`–`0xb342_2014`. This is the AES-192 or partial AES-256 key, populated at runtime from eFuse via the hardware during module init.

---

## Input Buffer Layout (for SC_CMD_VERIFY) — CORRECTED 2026-05-13

**Previous layout was wrong.** The buffer is NOT 15 KB. Verified by reading mmcblk0p1
and tracing the copy loop in sc_ioctl.

The kernel copies exactly **0x800 bytes (2048 bytes)** from userspace via `copy_from_user`.

```
offset 0x000 : magic "SCBT" (0x54424353)
offset 0x004 : first 0x1fc bytes of the signed data (e.g. squashfs header bytes)
offset 0x200 : AES DMA physical address — RAM address where firmware image is loaded
offset 0x204 : (zero in observed sample)
offset 0x208 : AES DMA size (e.g. 0x800)
offset 0x20c : (0x800 in observed sample)
offset 0x210–0x2ff: remaining AES engine config words
offset 0x300 : RSA-2048 public key modulus (256 bytes, 64 × 4-byte LE words) ← CALLER SUPPLIED
offset 0x400–0x4fb: RSA exponent padding (zeros)
offset 0x4fc : RSA public exponent e = 0x00010001 (65537)
offset 0x500 : RSA signature ciphertext (256 bytes) ← CALLER SUPPLIED
Total: 0x800 bytes (2048 bytes)
```

**How input maps to AES MMIO:** The copy loop deposits input[0x200..0x5ff] into AES
engine MMIO at `input_offset + 0x3600`. So:
- `input[0x300]` → `MMIO+0x3900` (RSA modulus passed to rsa_public_decrypt)
- `input[0x500]` → `MMIO+0x3b00` (RSA signature passed to rsa_public_decrypt)

The offsets 0x3900/0x3b00 in the original notes were MMIO offsets, not input buffer offsets.

**mmcblk0p1 is the SCBT signature block** for mmcblk0p7 (deplibs squashfs). The raw
squashfs on mmcblk0p7 does NOT start with SCBT — it starts with `hsqs`. cmd_sc reads
the signature from mmcblk0p1 and the physical address of the loaded image, then calls
SC_CMD_VERIFY. The SCBT block on mmcblk0p1 starts with `SCBThsqs` (SCBT magic
followed immediately by the squashfs header bytes).

**AES DMA caveat:** `input[0x200]` must be a valid physical RAM address where the
firmware image has been DMA-loaded. Providing zero or an invalid address causes the
AES PDMA busy-wait loop to spin forever (uninterruptible D-state hang). Power cycle
required to recover.

**Observed real values from mmcblk0p1:**
```
input[0x000] = 0x54424353 ("SCBT")
input[0x200] = 0x05ce1000  ← physical RAM address of loaded squashfs
input[0x208] = 0x00000800  ← size
input[0x300..0x3ff] = RSA-2048 modulus (Creality's public key)
input[0x4fc] = 0x00010001  ← e = 65537
input[0x500..0x5ff] = RSA signature
```

**sc_open exclusive lock:** `/dev/sc` enforces single-opener via BSS+0x1028 flag.
sc_open returns -EPERM if already open. sc_release clears the flag. If a process
hangs inside an ioctl (e.g. stuck AES DMA), the fd cannot be recovered without
a reboot.

---

## f_rsa_public_decrypt — Software RSA (text 0x0)

```
rsa_public_decrypt(out, sig, key_len_words, modulus, exp_is_1, exp_buf, exp_buf_len):
  bn_mod_exp(&result, sig, ?, modulus, 1, ...)
  bn_encode(out, 0x100 /*256 bytes*/, &result, key_len_words)
```

Pure software bignum — `bn_mod_exp` is a standard left-to-right modular exponentiation. No hardware RSA is involved.

---

## Note on B_NEXT_MIPS_LE — Bug Already Fixed in Current Patcher

**Status: sc_patched.ko in firmware/ is VALID. Patcher code is correct.**  
*(Earlier notes incorrectly said this was broken — the code was fixed before those notes were written.)*

The `B_NEXT_MIPS_LE = b'\x00\x00\x00\x10'` constant is defined (line 27) but never used in any `patch()` call. All eFuse patches use `NOP_MIPS_LE`. The constant is dead code.

For historical reference, `B_NEXT_MIPS_LE` would be `beq $zero,$zero,0` as a LE uint32 (`0x10000000`).

The current patcher (line 105) correctly uses `NOP_MIPS_LE = b'\x00\x00\x00\x00'` for all
eFuse patches — execution falls through past the branch. The `B_NEXT_MIPS_LE` constant
is defined but never referenced in any patch call.

**Verified patch offsets against real binary** (ELF .text at file offset 0x60):
```
text+0x148c  file 0x014ec: 0x104000c9  beqz $v0, +0x324   ← eFuse bit21
text+0x149c  file 0x014fc: 0x104000c6  beqz $v0, +0x318   ← eFuse bit22
text+0x14ac  file 0x0150c: 0x104000c1  beqz $v0, +0x304   ← eFuse bit23
text+0x1604  file 0x01664: 0x3c020000  lui $v0, 0          ← RSA call setup
text+0x1608  file 0x01668: 0x8c420000  lw $v0, 0($v0)      ← deref fptr
text+0x160c  file 0x0166c: 0x0040f809  jalr $v0            ← RSA call
text+0x1610  file 0x01670: 0x00a02025  move $a0, $a1       ← delay slot
text+0x1624  file 0x01684: 0x14400028  bnez $v0, error     ← post-call check
```

---

## Attack Surface

### Attack 1: f_rsa_public_decrypt pointer overwrite (kernel memory write)

`f_rsa_public_decrypt` is a function pointer in the writable `.data` section. At runtime, with root shell:

```bash
# 1. Find module base
cat /proc/modules | grep soc_security
# → soc_security 12345 0 - Live 0xc0123456

# 2. Calculate pointer address
# f_rsa_public_decrypt is at .data offset 0x00 (first .data symbol)
# Module base + 0x1f50 (section offset) = f_rsa_public_decrypt address

# 3. Write nop-stub address over the pointer (4 bytes, little-endian)
# Requires /dev/mem access or a helper kernel module
```

**Easiest implementation**: load a tiny helper .ko that:
1. Looks up `soc_security`'s `f_rsa_public_decrypt` via `symbol_get()` or direct pointer arithmetic
2. Writes the address of a `return 0` stub function over it

### Attack 2: Patch soc_security.ko on disk, reload module

Since rootfs is read-only signed squashfs (mounted at `/usr/deplibs`), we cannot modify the original. But we can:

1. Copy `soc_security.ko` to `/tmp` or `/usr/data`
2. Patch the binary bytes (see byte patch table below)
3. `rmmod soc_security && insmod /tmp/soc_security_patched.ko`

The kernel likely does NOT enforce `CONFIG_MODULE_SIG` (Ingenic Buildroot default, and module loading by `cmd_sc` would break if it did).

**Byte patches** (offsets are within the ELF `.text` section, ELF file offset = section_offset + text_offset):

`.text` section starts at ELF file offset `0x60`.

| Goal | Text offset | Current bytes | Patch to |
|------|-------------|---------------|----------|
| Skip eFuse bit 21 check | 0x148c | `10 40 xx xx` (beqz) | `00 00 00 00` (nop) |
| Skip eFuse bit 22 check | 0x149c | `10 40 xx xx` (beqz) | `00 00 00 00` (nop) |
| Skip eFuse bit 23 check | 0x14ac | `10 40 xx xx` (beqz) | `00 00 00 00` (nop) |
| Skip RSA verify | 0x1604–0x1610 | call f_rsa_public_decrypt | Replace with `li $v0, 0; jr $ra; nop` |

### Attack 3: cmd_sc interception

`cmd_sc` is a userspace binary in `/usr/deplibs` (signed rootfs). However:
- The decrypted copies land in `/tmp/apps` (tmpfs, writable)
- We can intercept at the library level with `LD_PRELOAD`
- Or replace the `seed.sh` call to `cmd_sc` with a custom script (since `/bin/seed.sh` may be in a writable location, or we can create an earlier init script that intercepts)

### Attack 4: Self-sign with own RSA key

The RSA modulus is passed **in the input buffer** at offset 0x3900. This means:
- The verifier uses whatever modulus you provide
- Security depends entirely on eFuse bits 21–23 being burned

If eFuse bits are burned (device is production): you still need to bypass the eFuse check (Attack 2 or 1).
If eFuse bits are NOT burned (unlikely on production units): you can self-sign with any key.

---

## UART Access

Per hardware docs:
- **Pins**: GND/RX2/TX2 header on mainboard
- **Baud**: 3,000,000 bps (not 115200!)
- **Format**: 8-bit, no parity, 1 stop bit, LSB-first

```bash
picocom -b 3000000 --databits 8 --parity n --stopbits 1 /dev/ttyUSB0
```

---

## Partition Layout (for flashing strategy)

| Partition | Mount | Encryption | Writable |
|-----------|-------|------------|----------|
| `mmcblk0p5` kernel | — | AES+signed | No (needs soc_security bypass) |
| `mmcblk0p7` rootfs | `/usr/deplibs` | signed squashfs | No |
| `mmcblk0p8` rootfs2 | `/usr/apps` | none (ext4) | **Yes** |
| `mmcblk0p9` rootfs_data | — | none | Yes |
| `mmcblk0p10` userdata | `/usr/data` | none (ext4) | **Yes** |

**Immediate persistence target**: `/usr/apps` (ext4, unencrypted, persists reboots, writable).  
The exploit's `S999persistence` script correctly targets `/etc/appetc/init.d/` which is on `/usr/apps`.

---

## Recommended Attack Sequence

1. **Run `k1c-2025-exploit.py`** → get root SSH
   - WebSocket injection via `wsslicer` protocol on port 9999
   - Command injection through malicious `Content-Disposition` filename
   - Privilege escalation via `udhcpc -s privesc.py` (runs script as root)
   - Writes SSH authorized_keys, starts dropbear

2. **Make full eMMC backup** before touching anything:
   ```bash
   dd if=/dev/mmcblk0 bs=1M | ssh user@host 'cat > k1c_emmc_full.img'
   ```
   This is the only recovery path. There is no maskrom/rescue mode confirmed
   for the Ingenic X2600E.

3. **Confirm persistence** via `/etc/appetc/init.d/S999persistence`
   - `/etc/appetc` is a symlink/mount to `/usr/apps/etc` (writable ext4)
   - `S999persistence` survives reboots
   - Dropbear host keys are persistent (not tmpfs-backed on this device)

4. **Fix and regenerate sc_patched.ko** (see bug section above):
   ```bash
   python3 tools/patch_soc_security.py
   scp firmware/sc_patched.ko root@<printer_ip>:/usr/data/
   ```

5. **Load patched module interactively** (never at boot):
   ```bash
   rmmod soc_security
   insmod /usr/data/sc_patched.ko
   ```
   ⚠️  Restore original before reboot:
   ```bash
   rmmod soc_security && insmod /lib/modules/soc_security.ko
   ```

6. **Decrypt / inspect with patched module loaded**:
   ```bash
   cmd_sc src=/dev/mmcblk0p7 dst=/usr/data/deplibs_decrypted.img  # AES decrypt only
   cmd_sc -v src=/usr/data/test_package.img                        # full verify bypass
   ```

7. **Extract deplibs squashfs** for inspection (no patch needed — it's mounted):
   ```bash
   cp -r /usr/deplibs /usr/data/deplibs_extracted/
   ```

8. **Build custom rootfs** → sign with own RSA key → flash mmcblk0p7
   - Requires working eFuse bypass (step 5) and full backup (step 2)
   - See encryption-chain.md for self-signing workflow
