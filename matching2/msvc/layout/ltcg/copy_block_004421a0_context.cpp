// Compiler context only; never selected as recovered game code.
#include "../../src/unidentified/FUN_004421a0_004421a0.cpp"
#pragma code_seg(".text$03context")
int __stdcall CopyBlockCompilerContext_004421a0(CopyValue_004421a0** blocks, int count, CopyBlock_004421a0* destination) {
    CopyValue_004421a0** cursor = blocks;
    while (count--) { CopyValue_004421a0* block = *cursor++; destination->Assign(*block); destination->Assign(*block); }
    return 0;
}
#pragma code_seg()
