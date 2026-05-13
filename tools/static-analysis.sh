#!/bin/bash
# Static analysis pass for all binaries in firmware/apps_decrypted.
# Extracts strings, ELF metadata, imports, and r2 function lists.
# Output: notes/binary-analysis/<binary-name>/

set -euo pipefail

BASE="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
APPS="$BASE/firmware/apps_decrypted"
OUT="$BASE/notes/binary-analysis"

echo "[*] Base: $BASE"
echo "[*] Input: $APPS"
echo "[*] Output: $OUT"
echo ""

for bin in "$APPS"/*; do
    name=$(basename "$bin")
    dir="$OUT/$name"
    mkdir -p "$dir"
    echo "[*] ── $name ──────────────────────────────────"

    # ELF header + section layout
    readelf -h  "$bin" > "$dir/elf-header.txt"   2>&1
    readelf -S  "$bin" > "$dir/sections.txt"      2>&1
    readelf -d  "$bin" > "$dir/dynamic.txt"       2>&1
    readelf -r  "$bin" > "$dir/relocations.txt"   2>&1
    readelf -s  "$bin" > "$dir/symbols.txt"       2>&1

    # Strings (min length 8 to cut noise; also plain -n 4 pass for short tokens)
    strings -n 8 "$bin" > "$dir/strings.txt"
    strings -n 4 "$bin" > "$dir/strings-short.txt"

    # rabin2 fast metadata (no full analysis needed)
    rabin2 -i "$bin" > "$dir/imports-rabin2.txt"  2>/dev/null || true
    rabin2 -s "$bin" > "$dir/symbols-rabin2.txt"  2>/dev/null || true
    rabin2 -l "$bin" > "$dir/libs-rabin2.txt"     2>/dev/null || true
    rabin2 -z "$bin" > "$dir/strings-rabin2.txt"  2>/dev/null || true

    # r2 function list with auto-analysis (timeout 180s per binary)
    echo "    [r2] running analysis (timeout 180s)..."
    timeout 180 r2 \
        -e scr.color=0 \
        -e asm.arch=mips \
        -e asm.bits=32 \
        -e cfg.bigendian=false \
        -e anal.timeout=120 \
        -A -q \
        -c "afl" \
        "$bin" > "$dir/functions-r2.txt" 2>/dev/null || echo "    [!] r2 analysis timed out or failed"

    echo "    [+] done"
done

echo ""
echo "═══════════════════════════════════════════════════════"
echo " Cross-binary grep results"
echo "═══════════════════════════════════════════════════════"

echo ""
echo "── Root / auth / privilege keywords ──────────────────"
grep -rhi "root\|authoriz\|token\|passwd\|permission\|privilege\|unlock\|enable_root\|disable_root" \
    "$OUT"/*/strings.txt 2>/dev/null | sort -u | grep -v "^$" | head -80

echo ""
echo "── IPC socket / device paths ──────────────────────────"
grep -rhi "/tmp/.*sock\|/var/run/.*sock\|\.sock\b\|\.fifo\b\|/dev/sc\b\|/dev/sc[^/]" \
    "$OUT"/*/strings.txt 2>/dev/null | sort -u | head -40

echo ""
echo "── CMD_ command identifiers ───────────────────────────"
grep -rhi "CMD_\|cmd_[A-Z]" "$OUT"/*/strings.txt 2>/dev/null | sort -u | head -60

echo ""
echo "── Cloud endpoints ────────────────────────────────────"
grep -rhi "crealit\|aliyun\|crealitycloud\|aliyuncs\|mqtt\|58\.48\." \
    "$OUT"/*/strings.txt 2>/dev/null | sort -u | head -40

echo ""
echo "[*] Full output in: $OUT"
