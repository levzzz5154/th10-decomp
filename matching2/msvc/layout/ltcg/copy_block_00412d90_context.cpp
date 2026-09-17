// Compiler context only; never selected as recovered game code.
#include "../../src/unidentified/FUN_00412d90_00412d90.cpp"
#pragma code_seg(".text$03context")
int __stdcall CopyBlockCompilerContext_00412d90(CopyValue_00412d90** blocks, int count, CopyBlock_00412d90* destination) {
    CopyValue_00412d90** cursor = blocks;
    while (count--) { CopyValue_00412d90* block = *cursor++; destination->Assign(*block); destination->Assign(*block); }
    return 0;
}
#pragma code_seg()
