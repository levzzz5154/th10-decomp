// Compiler context only; never selected as recovered game code.
#include "../../../src/unreferenced/FUN.cpp_41ac30.cpp"
#pragma code_seg(".text$03context")
int __stdcall CopyBlockCompilerContext_0041ac30(CopyValue7** blocks, int count, CopyBlock8* destination) {
    CopyValue7** cursor = blocks;
    while (count--) { CopyValue7* block = *cursor++; destination->Assign(*block); destination->Assign(*block); }
    return 0;
}
#pragma code_seg()
