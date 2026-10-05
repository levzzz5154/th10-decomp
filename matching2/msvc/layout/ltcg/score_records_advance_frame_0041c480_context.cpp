// Compiler context only; these bytes do not enter the recovered image.
#include "../../src/unidentified/FUN_0041c480_0041c480.cpp"

// Synthetic entry: the primary scheduler task only ever reaches this callback
// with the object the score manager published at 0x0047781C, so the context
// materialises that global's link-time address and calls the modelled member.
extern "C" ScoreRecords_0041c480 data_0047781c;

#pragma code_seg(".text$05context")
int __stdcall ScoreRecordsAdvanceFrameCompilerContext() {
    return data_0047781c.AdvanceFrame();
}
#pragma code_seg()
