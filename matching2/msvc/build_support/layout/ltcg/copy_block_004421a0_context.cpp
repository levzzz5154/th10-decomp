// Compiler context only; never selected as recovered game code.
#include "../../../src/unreferenced/FUN.cpp_4421a0.cpp"
#pragma code_seg(".text$03context")
int __stdcall CopyBlockCompilerContext_004421a0(CopyValue8** blocks, int count, CopyBlock9* destination) {
    CopyValue8** cursor = blocks;
    while (count--) { CopyValue8* block = *cursor++; destination->Assign(*block); destination->Assign(*block); }
    return 0;
}
#pragma code_seg()
