#!/usr/bin/env python3
"""
Patch soc_security.ko to bypass eFuse checks and RSA signature verification.

Targets:
  1. NOP three eFuse bit-check beqz branches in sc_ioctl (SC_CMD_VERIFY path)
  2. Replace f_rsa_public_decrypt call with a stub that always returns 0 (success)

Usage:
  python3 patch_soc_security.py [input.ko] [output.ko]
  defaults: input=K1C-2025-Firmware/lib/modules/soc_security.ko, output=sc_patched.ko
"""

import sys
import shutil
import struct
from pathlib import Path
from elftools.elf.elffile import ELFFile

INPUT  = Path(__file__).parent / "K1C-2025-Firmware/lib/modules/soc_security.ko"
OUTPUT = Path(__file__).parent.parent / "firmware/sc_patched.ko"

NOP_MIPS_LE = b'\x00\x00\x00\x00'  # sll $zero, $zero, 0

# Unconditional branch to next instruction (NOP the conditional branch):
# MIPS LE: beq $zero, $zero, +0  →  0x00 0x00 0x00 0x10
B_NEXT_MIPS_LE = b'\x00\x00\x00\x10'

# li $v0, 0  (addiu $v0, $zero, 0)  MIPS LE: 0x00 0x00 0x02 0x24
LI_V0_ZERO = b'\x00\x00\x02\x24'
# jr $ra  MIPS LE: 0x08 0x00 0xe0 0x03
JR_RA = b'\x08\x00\xe0\x03'


def get_section_file_offset(elf, name):
    for sec in elf.iter_sections():
        if sec.name == name:
            return sec['sh_offset'], sec['sh_size']
    return None, None


def get_symbol_info(elf, sym_name):
    from elftools.elf.sections import SymbolTableSection
    for sec in elf.iter_sections():
        if isinstance(sec, SymbolTableSection):
            for sym in sec.iter_symbols():
                if sym.name == sym_name:
                    return sym['st_shndx'], sym['st_value'], sym['st_size']
    return None, None, None


def patch(data: bytearray, file_offset: int, patch_bytes: bytes, description: str):
    original = bytes(data[file_offset:file_offset + len(patch_bytes)])
    data[file_offset:file_offset + len(patch_bytes)] = patch_bytes
    print(f"  [+] {description}")
    print(f"      file offset 0x{file_offset:06x}: {original.hex()} → {patch_bytes.hex()}")


def main():
    src = Path(sys.argv[1]) if len(sys.argv) > 1 else INPUT
    dst = Path(sys.argv[2]) if len(sys.argv) > 2 else OUTPUT

    if not src.exists():
        print(f"[!] Input not found: {src}")
        sys.exit(1)

    dst.parent.mkdir(parents=True, exist_ok=True)
    shutil.copy2(src, dst)
    print(f"[*] Copied {src} → {dst}")

    data = bytearray(dst.read_bytes())

    with open(src, 'rb') as f:
        elf = ELFFile(f)
        text_off, text_size = get_section_file_offset(elf, '.text')
        init_off, init_size = get_section_file_offset(elf, '.init.text')

    if text_off is None:
        print("[!] .text section not found")
        sys.exit(1)

    print(f"\n[*] .text section: file offset 0x{text_off:x}, size 0x{text_size:x}")
    print(f"[*] .init.text section: file offset 0x{init_off:x}")

    print("\n[*] Patching eFuse bit checks (sc_ioctl CMD 0xc0047300 path)...")

    # sc_ioctl is at .text offset 0x11cc
    # eFuse check 1: text offset 0x148c  → beqz $v0, error_path
    # eFuse check 2: text offset 0x149c  → beqz $v0, error_path
    # eFuse check 3: text offset 0x14ac  → beqz $v0, error_path
    for text_offset, label in [
        (0x148c, "eFuse bit 21 check (beqz $v0, error)"),
        (0x149c, "eFuse bit 22 check (beqz $v0, error)"),
        (0x14ac, "eFuse bit 23 check (beqz $v0, error)"),
    ]:
        file_off = text_off + text_offset
        current = bytes(data[file_off:file_off + 4])
        # Verify it looks like a beqz: opcode bits [31:26] = 0x04 (BEQ) or 0x01 (REGIMM)
        # In MIPS LE, the opcode is in the high byte of the 4-byte word
        opcode = struct.unpack_from('<I', data, file_off)[0] >> 26
        if opcode not in (0x04, 0x01, 0x05):
            print(f"  [!] Unexpected opcode 0x{opcode:02x} at text+0x{text_offset:x}, skipping")
            print(f"      bytes: {current.hex()}")
            continue
        patch(data, file_off, NOP_MIPS_LE, f"NOP branch: {label}")

    print("\n[*] Patching RSA signature call in SC_CMD_VERIFY (text offset 0x1604)...")

    # At text 0x1604: lui $v0, 0  (load f_rsa_public_decrypt ptr)
    # At text 0x1608: lw  $v0, ($v0)
    # At text 0x160c: jalr $v0
    # At text 0x1610: move $a0, $a1  (delay slot)
    #
    # Replace with:
    #   0x1604: li $v0, 0       (addiu $v0, $zero, 0)
    #   0x1608: jr $ra          (return success = 0)
    #   0x160c: nop             (delay slot)
    #   0x1610: nop             (was delay slot of jalr)
    #
    # After this, the caller at 0x1614 checks $v0 for alignment/NULL — $v0=0 will
    # trigger the error path. We need to make it look like success instead.
    # Better: patch the post-call check at 0x1624 (bnez $v0, error) to always skip the error.

    # Actually the cleanest patch: replace the 4 instructions with a success setup:
    #   lui $v0, 0  → li $v0, 0  (already zero from lui; fine)
    #   lw $v0,($v0) → nop
    #   jalr $v0    → nop
    #   move $a0,$a1 → nop
    # Then the code continues to 0x1614 with $v0 = 0.
    # At 0x1614: addiu $v0, $s0, 4  — overwrites $v0, fine.
    # At 0x1624: bnez $v0, error — if this $v0 is nonzero, jump to error.
    # $s0 is the userspace output pointer. If valid, $v0 = $s0 + 4 which is nonzero → error!
    #
    # Better approach: just patch the bnez at 0x1624 to be a NOP (skip error):

    # Patch 1: NOP the jalr call (prevent calling RSA verify)
    for text_offset, label in [
        (0x1604, "lui (load f_rsa_public_decrypt hi)"),
        (0x1608, "lw  (dereference f_rsa_public_decrypt ptr)"),
        (0x160c, "jalr $v0 (RSA verify call)"),
        (0x1610, "move $a0, $a1 (jalr delay slot)"),
    ]:
        patch(data, text_off + text_offset, NOP_MIPS_LE, f"NOP RSA call: {label}")

    # Patch 2: force $v0 = 0 before the post-call alignment check at 0x1614
    # Insert "li $v0, 0" at the now-NOP'd 0x1604 slot
    patch(data, text_off + 0x1604, LI_V0_ZERO, "Set $v0 = 0 (RSA success stub)")

    # Patch 3: the check at 0x1624 is:  bnez $v0, 0x16c8 (error)
    # $v0 at that point = ($s0 + 4) | $s0  which is nonzero if $s0 is valid.
    # Patch this branch to always-not-taken (NOP):
    text_offset_0x1624 = 0x1624
    file_off_check = text_off + text_offset_0x1624
    current_instr = struct.unpack_from('<I', data, file_off_check)[0]
    opcode = current_instr >> 26
    if opcode in (0x05, 0x04, 0x01):  # bne/beq/regimm
        patch(data, file_off_check, NOP_MIPS_LE, "NOP post-RSA alignment check (bnez $v0, error)")
    else:
        print(f"  [!] Expected branch at text+0x1624, got opcode 0x{opcode:02x}, skipping")

    dst.write_bytes(data)
    print(f"\n[+] Patched module written to: {dst}")
    print()
    print("Deploy on printer:")
    print("  scp firmware/sc_patched.ko root@<printer_ip>:/usr/data/")
    print("  ssh root@<printer_ip> 'rmmod soc_security && insmod /usr/data/sc_patched.ko'")
    print("  ssh root@<printer_ip> 'cmd_sc src=/path/to/encrypted.img dst=/tmp/decrypted.img'")


if __name__ == "__main__":
    main()
