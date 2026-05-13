#!/usr/bin/env python3
"""Disassemble key functions from soc_security.ko (MIPS32 LE relocatable ELF)."""

import sys
import struct
from elftools.elf.elffile import ELFFile
from elftools.elf.sections import SymbolTableSection
from elftools.elf.relocation import RelocationSection

try:
    from capstone import Cs, CS_ARCH_MIPS, CS_MODE_MIPS32, CS_MODE_LITTLE_ENDIAN
except ImportError:
    print("pip install capstone pyelftools")
    sys.exit(1)

TARGET = "/home/anthony/Documents/Hacking/Creality-K1c-Printer/tools/K1C-2025-Firmware/lib/modules/soc_security.ko"
FUNCS = ["sc_ioctl", "sc_init", "sc_open", "sc_release", "sc_clean",
         "init_module", "cleanup_module", "rsa_public_decrypt", "pdma_wait"]

def get_symbols(elf):
    syms = {}
    for sec in elf.iter_sections():
        if isinstance(sec, SymbolTableSection):
            for sym in sec.iter_symbols():
                if sym.name and sym['st_size'] > 0:
                    syms[sym.name] = {
                        'section': sym['st_shndx'],
                        'offset': sym['st_value'],
                        'size': sym['st_size'],
                    }
                elif sym.name and sym['st_value'] >= 0:
                    syms[sym.name] = {
                        'section': sym['st_shndx'],
                        'offset': sym['st_value'],
                        'size': sym['st_size'],
                    }
    return syms

def get_relocations(elf, text_sec_idx):
    """Return dict of offset -> symbol name for relocations targeting text section."""
    relocs = {}
    for sec in elf.iter_sections():
        if isinstance(sec, RelocationSection):
            if sec['sh_info'] == text_sec_idx:
                symtab = elf.get_section(sec['sh_link'])
                for rel in sec.iter_relocations():
                    sym = symtab.get_symbol(rel['r_info_sym'])
                    if sym:
                        relocs[rel['r_offset']] = sym.name
    return relocs

def find_section_by_name(elf, name):
    for i, sec in enumerate(elf.iter_sections()):
        if sec.name == name:
            return i, sec
    return None, None

def disasm_func(elf, syms, func_name):
    sym = syms.get(func_name)
    if not sym:
        print(f"  [!] Symbol '{func_name}' not found")
        return

    sec_idx = sym['section']
    offset = sym['offset']
    size = sym['size']

    if sec_idx == 'SHN_UNDEF' or sec_idx == 0:
        print(f"  [!] '{func_name}' is external (undefined)")
        return
    if size == 0:
        print(f"  [!] '{func_name}' has size 0 (may need manual range)")
        return

    sec = elf.get_section(sec_idx)
    data = sec.data()[offset:offset + size]

    relocs = get_relocations(elf, sec_idx)

    md = Cs(CS_ARCH_MIPS, CS_MODE_MIPS32 | CS_MODE_LITTLE_ENDIAN)
    md.detail = False

    print(f"\n{'='*70}")
    print(f"  {func_name}  (section={sec.name}, offset=0x{offset:x}, size={size})")
    print(f"{'='*70}")

    for insn in md.disasm(data, offset):
        rel_note = ""
        if insn.address in relocs:
            rel_note = f"  <- {relocs[insn.address]}"
        print(f"  0x{insn.address:06x}:  {insn.mnemonic:<10} {insn.op_str}{rel_note}")

with open(TARGET, 'rb') as f:
    elf = ELFFile(f)
    syms = get_symbols(elf)

    for fn in FUNCS:
        disasm_func(elf, syms, fn)
