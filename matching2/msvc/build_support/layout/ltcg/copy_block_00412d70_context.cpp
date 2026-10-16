// Compiler context only; never selected as recovered game code.
#include "../../../src/unreferenced/FUN.cpp_412d70.cpp"
#pragma code_seg(".text$03context")
int __stdcall CopyBlockCompilerContext_00412d70(CopyValue2** blocks, int count, CopyBlock3* destination) {
    CopyValue2** cursor = blocks;
    while (count--) { CopyValue2* block = *cursor++; destination->Assign(*block); destination->Assign(*block); }
    return 0;
}
#pragma code_seg()
