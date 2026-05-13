# Ghidra headless post-analysis script (Jython/Python 2.7 compatible).
# Exports per-binary analysis artifacts to notes/binary-analysis/<name>/:
#   ghidra-functions.txt   — all functions with addresses
#   ghidra-decompiled.c    — decompiled C for security-relevant functions
#
# Run via:
#   analyzeHeadless <project> K1C-2025 -process <binary> \
#     -postScript ExportAnalysis.py -scriptPath tools/ghidra-scripts/

import os
from ghidra.app.decompiler import DecompInterface
from ghidra.util.task import ConsoleTaskMonitor

BASE = "/home/anthony/Documents/Hacking/Creality-K1c-Printer"
OUT_ROOT = os.path.join(BASE, "notes", "binary-analysis")

SECURITY_KEYWORDS = [
    "root", "auth", "token", "authoriz", "permission", "privilege",
    "reboot", "update", "ota", "upgrade", "password", "passwd",
    "CMD_", "cmd_", "unlock", "enable", "disable", "verify",
    "sign", "crypt", "key", "cert", "tls", "ssl",
]

prog_name = currentProgram.getName()  # noqa: F821 (Ghidra API global)
out_dir = os.path.join(OUT_ROOT, prog_name)
if not os.path.exists(out_dir):
    os.makedirs(out_dir)

print("[ExportAnalysis] Program: {}".format(prog_name))
print("[ExportAnalysis] Output:  {}".format(out_dir))

# --- Export all function addresses + names ---
fn_manager = currentProgram.getFunctionManager()  # noqa: F821
fn_list_path = os.path.join(out_dir, "ghidra-functions.txt")
count = 0
with open(fn_list_path, "w") as f:
    for fn in fn_manager.getFunctions(True):
        f.write("{}\t{}\n".format(fn.getEntryPoint(), fn.getName()))
        count += 1
print("[ExportAnalysis] Exported {} functions to {}".format(count, fn_list_path))

# --- Decompile security-relevant functions ---
decomp = DecompInterface()
decomp.openProgram(currentProgram)  # noqa: F821
monitor = ConsoleTaskMonitor()

decompiled_path = os.path.join(out_dir, "ghidra-decompiled.c")
decompiled_count = 0
with open(decompiled_path, "w") as f:
    for fn in fn_manager.getFunctions(True):
        fn_name_lower = fn.getName().lower()
        if any(kw.lower() in fn_name_lower for kw in SECURITY_KEYWORDS):
            result = decomp.decompileFunction(fn, 90, monitor)
            if result.decompileCompleted():
                dc = result.getDecompiledFunction()
                if dc is not None:
                    f.write("\n// === {} @ {} ===\n".format(
                        fn.getName(), fn.getEntryPoint()))
                    f.write(dc.getC())
                    decompiled_count += 1

print("[ExportAnalysis] Decompiled {} security-relevant functions".format(decompiled_count))
print("[ExportAnalysis] Output: {}".format(decompiled_path))
print("[ExportAnalysis] Done.")
