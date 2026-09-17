// Compiler context only; never selected as recovered game code.
#include "../../src/unidentified/FUN_0041ac20_0041ac20.cpp"
#pragma code_seg(".text$03context")
int __stdcall CopyBlockCompilerContext_0041ac20(CopyValue_0041ac20** blocks, int count, CopyBlock_0041ac20* destination) {
    CopyValue_0041ac20** cursor = blocks;
    while (count--) { CopyValue_0041ac20* block = *cursor++; destination->Assign(*block); destination->Assign(*block); }
    return 0;
}
#pragma code_seg()
