#!/bin/bash
# Launch Ghidra GUI and open the K1C project
GHIDRA=/opt/ghidra_12.0.4_PUBLIC
export JAVA_HOME=/usr/lib/jvm/java-21-openjdk-amd64
PROJECT_DIR=/home/anthony/Documents/Hacking/Creality-K1c-Printer/ghidra-projects
PROJECT_NAME=K1C-2025

$GHIDRA/ghidraRun \
    "$PROJECT_DIR/${PROJECT_NAME}.gpr" 2>/dev/null \
    || $GHIDRA/ghidraRun
