// Ghidra GhidraScript: exports per-binary analysis artifacts.
// Outputs to notes/binary-analysis/<prog-name>/
//   ghidra-functions.txt    — all functions with addresses + sizes
//   ghidra-decompiled.c     — decompiled C for security-relevant functions
//
// Run via analyzeHeadless ... -process <binary> -postScript ExportAnalysis.java

import ghidra.app.script.GhidraScript;
import ghidra.app.decompiler.DecompInterface;
import ghidra.app.decompiler.DecompileResults;
import ghidra.program.model.listing.Function;
import ghidra.program.model.listing.FunctionIterator;
import ghidra.util.task.ConsoleTaskMonitor;

import java.io.File;
import java.io.FileWriter;
import java.io.PrintWriter;

public class ExportAnalysis extends GhidraScript {

    private static final String[] SECURITY_KEYWORDS = {
        "root", "auth", "token", "authoriz", "permission", "privilege",
        "reboot", "update", "ota", "upgrade", "password", "passwd",
        "cmd_", "unlock", "enable", "disable", "verify",
        "sign", "crypt", "key", "cert", "tls", "ssl",
    };

    @Override
    public void run() throws Exception {
        String base = "/home/anthony/Documents/Hacking/Creality-K1c-Printer";
        String progName = currentProgram.getName();
        String outDir = base + "/notes/binary-analysis/" + progName;

        File dir = new File(outDir);
        if (!dir.exists()) dir.mkdirs();

        println("[ExportAnalysis] Program: " + progName);
        println("[ExportAnalysis] Output:  " + outDir);

        // Export all functions
        File fnFile = new File(outDir + "/ghidra-functions.txt");
        int fnCount = 0;
        try (PrintWriter pw = new PrintWriter(new FileWriter(fnFile))) {
            FunctionIterator fns = currentProgram.getFunctionManager()
                                                 .getFunctions(true);
            while (fns.hasNext()) {
                Function fn = fns.next();
                pw.printf("%s\t%d\t%s%n",
                    fn.getEntryPoint(),
                    fn.getBody().getNumAddresses(),
                    fn.getName());
                fnCount++;
            }
        }
        println("[ExportAnalysis] Exported " + fnCount + " functions");

        // Decompile security-relevant functions
        DecompInterface decomp = new DecompInterface();
        decomp.openProgram(currentProgram);
        ConsoleTaskMonitor monitor = new ConsoleTaskMonitor();

        File dcFile = new File(outDir + "/ghidra-decompiled.c");
        int dcCount = 0;
        try (PrintWriter pw = new PrintWriter(new FileWriter(dcFile))) {
            FunctionIterator fns = currentProgram.getFunctionManager()
                                                 .getFunctions(true);
            while (fns.hasNext()) {
                Function fn = fns.next();
                String lower = fn.getName().toLowerCase();
                boolean match = false;
                for (String kw : SECURITY_KEYWORDS) {
                    if (lower.contains(kw)) { match = true; break; }
                }
                if (!match) continue;

                DecompileResults res = decomp.decompileFunction(fn, 90, monitor);
                if (res != null && res.decompileCompleted()) {
                    ghidra.app.decompiler.DecompiledFunction dc =
                        res.getDecompiledFunction();
                    if (dc != null) {
                        pw.println("\n// === " + fn.getName()
                                 + " @ " + fn.getEntryPoint() + " ===");
                        pw.println(dc.getC());
                        dcCount++;
                    }
                }
            }
        }
        println("[ExportAnalysis] Decompiled " + dcCount
              + " security-relevant functions → " + dcFile.getPath());
        println("[ExportAnalysis] Done.");
    }
}
