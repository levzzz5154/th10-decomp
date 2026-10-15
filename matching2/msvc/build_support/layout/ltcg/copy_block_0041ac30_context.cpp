// Compiler context only; never selected as recovered game code.
#include "../../../src/unreferenced/FUN_0041ac30_0041ac30.cpp"
#pragma code_seg(".text$03context")
int __stdcall CopyBlockCompilerContext_0041ac30(CopyValue_0041ac30** blocks, int count, CopyBlock_0041ac30* destination) {
    CopyValue_0041ac30** cursor = blocks;
    while (count--) { CopyValue_0041ac30* block = *cursor++; destination->Assign(*block); destination->Assign(*block); }
    return 0;
}
#pragma code_seg()
