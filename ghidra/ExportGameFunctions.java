// Bulk-export Ghidra pseudocode for addresses listed as GAME in tracking.csv.
//
// Headless usage:
//   analyzeHeadless <project-dir> <project-name> -process th10.exe -noanalysis \
//     -readOnly -scriptPath <script-dir> \
//     -postScript ExportGameFunctions.java <tracking.csv> <output-dir>

import ghidra.app.decompiler.DecompInterface;
import ghidra.app.decompiler.DecompileResults;
import ghidra.app.script.GhidraScript;
import ghidra.program.model.address.Address;
import ghidra.program.model.listing.Function;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.nio.charset.StandardCharsets;

public class ExportGameFunctions extends GhidraScript {
    private static String safeName(String name) {
        return name.replaceAll("[^A-Za-z0-9_@.-]", "_");
    }

    private static BufferedWriter writer(File file) throws Exception {
        return new BufferedWriter(new OutputStreamWriter(
            new FileOutputStream(file), StandardCharsets.UTF_8));
    }

    @Override
    public void run() throws Exception {
        String[] args = getScriptArgs();
        if (args.length != 2) {
            throw new IllegalArgumentException(
                "expected arguments: <tracking.csv> <output-dir>");
        }

        File trackingFile = new File(args[0]);
        File outputDirectory = new File(args[1]);
        if (!outputDirectory.exists() && !outputDirectory.mkdirs()) {
            throw new IllegalStateException(
                "could not create output directory: " + outputDirectory);
        }

        DecompInterface decompiler = new DecompInterface();
        decompiler.toggleCCode(true);
        decompiler.toggleSyntaxTree(true);
        if (!decompiler.openProgram(currentProgram)) {
            throw new IllegalStateException("could not open program in decompiler");
        }

        File indexFile = new File(outputDirectory, "index.tsv");
        BufferedWriter index = writer(indexFile);
        index.write("address\ttracking_name\tghidra_name\tsize\tstatus\tfile\tdetail\n");

        BufferedReader tracking = new BufferedReader(new InputStreamReader(
            new FileInputStream(trackingFile), StandardCharsets.UTF_8));
        String line = tracking.readLine(); // header
        int requested = 0;
        int exported = 0;
        int failed = 0;

        while ((line = tracking.readLine()) != null) {
            if (monitor.isCancelled()) {
                break;
            }
            String[] fields = line.split(",", -1);
            if (fields.length < 4 || !"GAME".equals(fields[3])) {
                continue;
            }

            requested++;
            String addressText = fields[0];
            String trackingName = fields[1];
            String size = fields[2];
            long addressValue = Long.parseLong(addressText.substring(2), 16);
            Address address = toAddr(addressValue);
            Function function = getFunctionAt(address);

            if (function == null) {
                failed++;
                index.write(addressText + "\t" + trackingName + "\t\t" + size +
                    "\tno-function\t\tGhidra has no function at this address\n");
                continue;
            }

            String ghidraName = function.getName();
            String fileName = String.format("%08X_%s.c", addressValue,
                safeName(trackingName));
            DecompileResults result = decompiler.decompileFunction(
                function, 120, monitor);
            if (result == null || !result.decompileCompleted() ||
                    result.getDecompiledFunction() == null) {
                failed++;
                String detail = result == null ? "no result" : result.getErrorMessage();
                detail = detail == null ? "decompilation failed" : detail;
                detail = detail.replace('\t', ' ').replace('\n', ' ');
                index.write(addressText + "\t" + trackingName + "\t" + ghidraName +
                    "\t" + size + "\tdecompile-error\t\t" + detail + "\n");
                continue;
            }

            BufferedWriter output = writer(new File(outputDirectory, fileName));
            output.write("/*\n");
            output.write(" * Raw Ghidra pseudocode reference; not directly compilable.\n");
            output.write(" * Address: " + addressText + "\n");
            output.write(" * Tracking name: " + trackingName + "\n");
            output.write(" * Ghidra name: " + ghidraName + "\n");
            output.write(" * Tracked span: " + size + " bytes\n");
            output.write(" */\n\n");
            output.write(result.getDecompiledFunction().getC());
            output.close();

            exported++;
            index.write(addressText + "\t" + trackingName + "\t" + ghidraName +
                "\t" + size + "\tok\t" + fileName + "\t\n");
            if (requested % 25 == 0) {
                println("Processed " + requested + " GAME entries (" + exported +
                    " exported, " + failed + " failed)");
            }
        }

        tracking.close();
        index.close();
        decompiler.dispose();
        println("Export complete: requested=" + requested + ", exported=" + exported +
            ", failed=" + failed + ", output=" + outputDirectory);
    }
}
