/* 
 * TH10 Ghidra Analysis Script
 * Run with: analyzeHeadless <project_dir> <project_name> -import <th10.exe> 
 *           -postScript DecompileTh10.java
 *
 * This script exports all decompiled functions and known breakpoints.
 */
import ghidra.app.script.GhidraScript;
import ghidra.app.decompiler.DecompInterface;
import ghidra.app.decompiler.DecompileResults;
import ghidra.program.model.listing.*;
import ghidra.program.model.symbol.*;
import ghidra.program.model.address.*;

public class DecompileTh10 extends GhidraScript {

    // Known TH10 function addresses (from thcrap patches)
    private static final long[] KNOWN_ADDRS = {
        0x44b3eaL, // file_size
        0x44b410L, // file_load
        0x434ee1L, // file_loaded
        0x410edcL, // spell_id
        0x410f30L, // spell_id_real
        0x409678L, // spell_name
        0x43278bL, // spell_id_result
        0x432876L, // spell_name_result
        0x434201L, // music_title
        0x4343beL, // music_cmt_params
        0x4343d1L, // music_cmt
        0x41631aL, // enemy_text_offset
        0x447a7eL, // sprintf_call
    };

    @Override
    public void run() throws Exception {
        println("TH10 Decompilation Analysis");
        println("============================");
        println("Image Base: " + currentProgram.getImageBase());

        DecompInterface decompInterface = new DecompInterface();
        decompInterface.openProgram(currentProgram);

        for (long addr : KNOWN_ADDRS) {
            Address address = currentProgram.getImageBase().add(addr);
            Function func = getFunctionAt(address);

            println(String.format("\n--- 0x%08X ---", addr));

            if (func != null) {
                println("Function: " + func.getName());
                println("Signature: " + func.getSignature());

                DecompileResults results = decompInterface.decompileFunction(func, 30, monitor);
                if (results != null && results.decompileCompleted()) {
                    println("Decompiled:\n" + results.getDecompiledFunction().getC());
                }
            } else {
                Listing listing = currentProgram.getListing();
                Instruction inst = listing.getInstructionAt(address);
                if (inst != null) {
                    println("Instruction: " + inst.toString());
                } else {
                    println("No code found at this address");
                }
            }
        }
    }
}
