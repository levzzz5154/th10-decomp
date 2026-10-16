// Compiler context only; never selected as recovered game code.
#include "../../../src/unreferenced/FUN.cpp_41ac20.cpp"
#pragma code_seg(".text$03context")
int __stdcall CopyBlockCompilerContext_0041ac20(CopyValue6** blocks, int count, CopyBlock7* destination) {
    CopyValue6** cursor = blocks;
    while (count--) { CopyValue6* block = *cursor++; destination->Assign(*block); destination->Assign(*block); }
    return 0;
}
#pragma code_seg()
