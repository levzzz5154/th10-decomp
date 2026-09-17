// Compiler context only; never selected as recovered game code.
#include "../../src/unidentified/FUN_00412d80_00412d80.cpp"
#pragma code_seg(".text$03context")
int __stdcall CopyBlockCompilerContext_00412d80(CopyValue_00412d80** blocks, int count, CopyBlock_00412d80* destination) {
    CopyValue_00412d80** cursor = blocks;
    while (count--) { CopyValue_00412d80* block = *cursor++; destination->Assign(*block); destination->Assign(*block); }
    return 0;
}
#pragma code_seg()
