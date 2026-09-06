// Supplement a read-only copy of the saved analysis with requested candidate starts.
// All mutations are discarded by analyzeHeadless -readOnly.
// @category TH10
import ghidra.app.script.GhidraScript;
import ghidra.program.model.address.Address;
import ghidra.program.model.listing.Function;
import java.nio.file.*;
import java.nio.charset.StandardCharsets;
import java.io.*;

public class PrepareFullAudit extends GhidraScript {
    public void run() throws Exception {
        String[] args = getScriptArgs();
        if (args.length != 2) throw new IllegalArgumentException("expected seeds file and report file");
        try (PrintWriter report = new PrintWriter(args[1], StandardCharsets.UTF_8)) {
            report.println("address\tstatus\tcontaining_function");
            for (String line : Files.readAllLines(Path.of(args[0]), StandardCharsets.UTF_8)) {
                monitor.checkCancelled();
                Address address = toAddr(Long.parseLong(line.trim(), 16));
                Function existing = getFunctionAt(address);
                if (existing != null) { report.println(line + "\texisting\t" + existing.getEntryPoint()); continue; }
                Function containing = getFunctionContaining(address);
                if (containing != null) { report.println(line + "\tinside-existing-body\t" + containing.getEntryPoint()); continue; }
                disassemble(address);
                Function created = createFunction(address, null);
                report.println(line + "\t" + (created == null ? "creation-failed" : "created-from-requested-start") + "\t");
            }
        }
        analyzeAll(currentProgram);
        println("AUGMENTED_AUDIT_ANALYSIS_COMPLETE; saved project remains unchanged in read-only mode");
    }
}
