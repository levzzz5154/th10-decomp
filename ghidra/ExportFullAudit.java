// Export all database functions and their evidence without changing analysis.
// @category TH10
import ghidra.app.script.GhidraScript;
import ghidra.app.decompiler.DecompInterface;
import ghidra.app.decompiler.DecompileResults;
import ghidra.framework.Application;
import ghidra.program.model.address.*;
import ghidra.program.model.data.DataTypeWriter;
import ghidra.program.model.listing.*;
import ghidra.program.model.mem.MemoryBlock;
import ghidra.program.model.symbol.*;
import java.io.*;
import java.nio.charset.StandardCharsets;

public class ExportFullAudit extends GhidraScript {
    private File output;
    private PrintWriter writer(String name) throws Exception {
        File file = new File(output, name);
        file.getParentFile().mkdirs();
        return new PrintWriter(file, StandardCharsets.UTF_8);
    }
    private String clean(Object value) {
        return String.valueOf(value).replace('\t', ' ').replace('\r', ' ').replace('\n', ' ');
    }
    private String hex(byte[] data) {
        StringBuilder text = new StringBuilder();
        for (byte b : data) text.append(String.format("%02X", b & 255));
        return text.toString();
    }
    private void listing(PrintWriter out, AddressSetView set) throws Exception {
        CodeUnitIterator units = currentProgram.getListing().getCodeUnits(set, true);
        while (units.hasNext()) {
            monitor.checkCancelled();
            CodeUnit unit = units.next();
            byte[] bytes = unit.getBytes();
            // Full bytes, including data/switch tables, are also in memory.hex.
            String encoded = bytes.length <= 32 ? hex(bytes) : hex(java.util.Arrays.copyOf(bytes, 32)) + "...";
            out.println(unit.getAddress() + "\t" + encoded + "\t" + clean(unit));
            for (Reference ref : unit.getReferencesFrom())
                out.println("; ref\t" + ref.getFromAddress() + "\t" + ref.getToAddress() + "\t" + ref.getReferenceType());
        }
    }
    public void run() throws Exception {
        if (getScriptArgs().length != 1) throw new IllegalArgumentException("expected output directory");
        output = new File(getScriptArgs()[0]);
        output.mkdirs();
        try (PrintWriter meta = writer("program.tsv")) {
            meta.println("key\tvalue");
            meta.println("program\t" + clean(currentProgram.getName()));
            meta.println("sha256\t" + currentProgram.getExecutableSHA256());
            meta.println("md5\t" + currentProgram.getExecutableMD5());
            meta.println("ghidra_version\t" + Application.getApplicationVersion());
            meta.println("language\t" + currentProgram.getLanguageID());
            meta.println("compiler_spec\t" + currentProgram.getCompilerSpec().getCompilerSpecID());
            meta.println("image_base\t" + currentProgram.getImageBase());
            meta.println("scope\t" + (new File(output, "ida_seeds.tsv").isFile()
                ? "all functions after IDA/reconstruction candidate starts and analyzeAll; analysis changes discarded"
                : "all functions in saved database; no analysis changes") + "; external imports listed separately");
        }
        DecompInterface decompiler = new DecompInterface();
        decompiler.toggleCCode(true);
        if (!decompiler.openProgram(currentProgram)) throw new IllegalStateException("decompiler open failed");
        int count = 0, failed = 0;
        try (PrintWriter index = writer("index.tsv")) {
            index.println("address\tname\tbody_ranges\tbody_bytes\tinstructions\tthunk\tstatus\tc_file\tasm_file\tdetail");
            FunctionIterator functions = currentProgram.getFunctionManager().getFunctions(true);
            while (functions.hasNext()) {
                monitor.checkCancelled();
                Function function = functions.next();
                String address = function.getEntryPoint().toString().toUpperCase();
                String cPath = "functions/" + address + ".c";
                String asmPath = "functions/" + address + ".asm";
                StringBuilder ranges = new StringBuilder();
                for (AddressRange range : function.getBody()) {
                    if (ranges.length() > 0) ranges.append(',');
                    ranges.append(range.getMinAddress()).append('-').append(range.getMaxAddress());
                }
                int instructions = 0;
                InstructionIterator instructionIterator = currentProgram.getListing().getInstructions(function.getBody(), true);
                while (instructionIterator.hasNext()) { instructionIterator.next(); instructions++; }
                try (PrintWriter asm = writer(asmPath)) {
                    asm.println("; Ghidra function " + address + " " + clean(function.getName()));
                    asm.println("; body ranges: " + ranges);
                    listing(asm, function.getBody());
                }
                DecompileResults result = decompiler.decompileFunction(function, 120, monitor);
                boolean ok = result != null && result.decompileCompleted() && result.getDecompiledFunction() != null;
                String detail = result == null ? "no result" : clean(result.getErrorMessage());
                try (PrintWriter c = writer(cPath)) {
                    c.println("/* Raw Ghidra reference; not compilable reconstruction. Address: " + address + " */");
                    if (ok) c.print(result.getDecompiledFunction().getC());
                    else { c.println("/* DECOMPILATION FAILED: " + detail.replace("*/", "* /") + " */"); failed++; }
                }
                index.println(address + "\t" + clean(function.getName()) + "\t" + ranges + "\t" + function.getBody().getNumAddresses()
                    + "\t" + instructions + "\t" + function.isThunk() + "\t" + (ok ? "ok" : "decompile-error")
                    + "\t" + cPath + "\t" + asmPath + "\t" + detail);
                if (++count % 100 == 0) { index.flush(); println("Full audit export: " + count + " functions, " + failed + " failures"); }
            }
        } finally { decompiler.dispose(); }
        try (PrintWriter symbols = writer("symbols.tsv")) {
            symbols.println("address\tname\tkind\tsource\texternal");
            SymbolIterator iterator = currentProgram.getSymbolTable().getAllSymbols(true);
            while (iterator.hasNext()) {
                Symbol symbol = iterator.next();
                symbols.println(symbol.getAddress() + "\t" + clean(symbol.getName(true)) + "\t" + symbol.getSymbolType()
                    + "\t" + symbol.getSource() + "\t" + symbol.isExternal());
            }
        }
        try (PrintWriter ext = writer("externals.tsv")) {
            ext.println("address\tname\tprototype");
            FunctionIterator iterator = currentProgram.getFunctionManager().getExternalFunctions();
            while (iterator.hasNext()) {
                Function function = iterator.next();
                ext.println(function.getEntryPoint() + "\t" + clean(function.getName(true)) + "\t" + clean(function.getPrototypeString(true, true)));
            }
        }
        AddressSet initialized = new AddressSet();
        try (PrintWriter blocks = writer("memory_blocks.tsv"); PrintWriter memory = writer("memory.hex")) {
            blocks.println("name\tstart\tend\tsize\tinitialized\tread\twrite\texecute");
            for (MemoryBlock block : currentProgram.getMemory().getBlocks()) {
                blocks.println(clean(block.getName()) + "\t" + block.getStart() + "\t" + block.getEnd() + "\t" + block.getSize()
                    + "\t" + block.isInitialized() + "\t" + block.isRead() + "\t" + block.isWrite() + "\t" + block.isExecute());
                if (!block.isInitialized()) continue;
                initialized.add(block.getStart(), block.getEnd());
                for (long offset = 0; offset < block.getSize(); offset += 16) {
                    monitor.checkCancelled();
                    Address address = block.getStart().add(offset);
                    byte[] bytes = new byte[(int)Math.min(16, block.getSize() - offset)];
                    block.getBytes(address, bytes);
                    memory.println(address + " " + hex(bytes));
                }
            }
        }
        try (PrintWriter all = writer("listing.asm")) { listing(all, initialized); }
        try (PrintWriter types = writer("types.h")) {
            new DataTypeWriter(currentProgram.getDataTypeManager(), types).write(currentProgram.getDataTypeManager(), monitor);
        }
        println("FULL_AUDIT_EXPORT_COMPLETE functions=" + count + " decompile_failures=" + failed);
    }
}
