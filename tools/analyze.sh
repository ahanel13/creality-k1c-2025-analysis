#!/bin/bash
# Run Ghidra headless analysis on K1C binaries to pre-process before GUI work.
# Usage: ./analyze.sh [binary]   (no arg = analyze all key targets)

GHIDRA=/opt/ghidra_12.0.4_PUBLIC
export JAVA_HOME=/usr/lib/jvm/java-21-openjdk-amd64
ANALYZER=$GHIDRA/support/analyzeHeadless
PROJECT_DIR=/home/anthony/Documents/Hacking/Creality-K1c-Printer/ghidra-projects
PROJECT_NAME=K1C-2025
FIRMWARE=/home/anthony/Documents/Hacking/Creality-K1c-Printer/tools/K1C-2025-Firmware

TARGETS=(
    "$FIRMWARE/lib/modules/soc_security.ko"
    "$FIRMWARE/bin/cmd_sc"
    "$FIRMWARE/bin/upgbox"
    "$FIRMWARE/bin/busybox"
)

if [ -n "$1" ]; then
    TARGETS=("$1")
fi

for TARGET in "${TARGETS[@]}"; do
    NAME=$(basename "$TARGET")
    echo "[*] Analyzing: $NAME"
    $ANALYZER "$PROJECT_DIR" "$PROJECT_NAME" \
        -import "$TARGET" \
        -overwrite \
        -processor "MIPS:LE:32:default" \
        -cspec "default" \
        -analysisTimeoutPerFile 300 \
        2>&1 | grep -E "INFO|WARN|ERROR|Importing|Analysis|Done"
    echo "[+] Done: $NAME"
    echo ""
done

echo "[*] Project saved to: $PROJECT_DIR/$PROJECT_NAME"
echo "[*] Open Ghidra GUI and File > Open Project to load it."
