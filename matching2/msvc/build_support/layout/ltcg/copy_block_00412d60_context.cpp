// Compiler context only; never selected as recovered game code.
#include "../../../src/unreferenced/FUN.cpp_412d60.cpp"
#pragma code_seg(".text$03context")
int __stdcall CopyBlockCompilerContext_00412d60(CopyValue** blocks, int count, CopyBlock2* destination) {
    CopyValue** cursor = blocks;
    while (count--) { CopyValue* block = *cursor++; destination->Assign(*block); destination->Assign(*block); }
    return 0;
}
#pragma code_seg()
