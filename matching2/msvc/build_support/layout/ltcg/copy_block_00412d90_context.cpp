// Compiler context only; never selected as recovered game code.
#include "../../../src/unreferenced/FUN.cpp_412d90.cpp"
#pragma code_seg(".text$03context")
int __stdcall CopyBlockCompilerContext_00412d90(CopyValue4** blocks, int count, CopyBlock5* destination) {
    CopyValue4** cursor = blocks;
    while (count--) { CopyValue4* block = *cursor++; destination->Assign(*block); destination->Assign(*block); }
    return 0;
}
#pragma code_seg()
