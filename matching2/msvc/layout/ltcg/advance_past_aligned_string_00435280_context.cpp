// Compiler context only; never selected as recovered game code.
#include "../../src/unidentified/unassigned_00435280.cpp"
#pragma code_seg(".text$03context")
int __stdcall AdvancePastAlignedStringContext_00435280(char** cursors, int count) {
    int total = 0;
    for (int index = 0; index < count; ++index)
        total += (int)AdvancePastAlignedString_00435280(cursors + index);
    return total;
}
#pragma code_seg()
