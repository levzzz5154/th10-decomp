// Compiler context only; never selected as recovered game code.
#include "../../../src/unreferenced/FUN.cpp_412d80.cpp"
#pragma code_seg(".text$03context")
int __stdcall CopyBlockCompilerContext_00412d80(CopyValue3** blocks, int count, CopyBlock4* destination) {
    CopyValue3** cursor = blocks;
    while (count--) { CopyValue3* block = *cursor++; destination->Assign(*block); destination->Assign(*block); }
    return 0;
}
#pragma code_seg()
