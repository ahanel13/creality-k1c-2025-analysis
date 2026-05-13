#!/bin/bash
# Import all firmware/apps_decrypted binaries into the K1C-2025 Ghidra project.
# Runs auto-analysis for each binary sequentially.
#
# Usage:
#   ./ghidra-import-apps.sh           # import + analyze all 8 binaries
#   ./ghidra-import-apps.sh vectorp   # import + analyze a single named binary

set -euo pipefail

BASE="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
GHIDRA=/opt/ghidra_12.0.4_PUBLIC
export JAVA_HOME=/usr/lib/jvm/java-21-openjdk-amd64
ANALYZER=$GHIDRA/support/analyzeHeadless
PROJECT_DIR=$BASE/ghidra-projects
PROJECT_NAME=K1C-2025
APPS=$BASE/firmware/apps_decrypted
SCRIPTS=$BASE/tools/ghidra-scripts

# Single binary mode
if [ -n "${1:-}" ]; then
    TARGET="$APPS/$1"
    if [ ! -f "$TARGET" ]; then
        echo "[!] Not found: $TARGET"
        exit 1
    fi
    TARGETS=("$TARGET")
else
    mapfile -t TARGETS < <(find "$APPS" -maxdepth 1 -type f | sort)
fi

echo "[*] Ghidra project: $PROJECT_DIR/$PROJECT_NAME"
echo "[*] Binaries to import: ${#TARGETS[@]}"
echo ""

for TARGET in "${TARGETS[@]}"; do
    NAME=$(basename "$TARGET")
    echo "[*] ── $NAME ──────────────────────────────────"
    $ANALYZER "$PROJECT_DIR" "$PROJECT_NAME" \
        -import "$TARGET" \
        -overwrite \
        -processor "MIPS:LE:32:default" \
        -cspec "default" \
        -analysisTimeoutPerFile 600 \
        2>&1 | grep -E "INFO.*Importing|INFO.*Analysis|INFO.*Saving|WARN|ERROR|Done importing"
    echo "[+] Done: $NAME"
    echo ""
done

echo "[*] All imports complete."
echo "[*] Run export script to extract analysis artifacts:"
echo "    ./ghidra-import-apps.sh <binary-name>  to re-analyze one binary"
echo "    See tools/ghidra-scripts/ExportAnalysis.py for post-analysis export"
