// Compiler context only; never selected as recovered game code.
#include "../../../src/unreferenced/FUN_00412d70_00412d70.cpp"
#pragma code_seg(".text$03context")
int __stdcall CopyBlockCompilerContext_00412d70(CopyValue_00412d70** blocks, int count, CopyBlock_00412d70* destination) {
    CopyValue_00412d70** cursor = blocks;
    while (count--) { CopyValue_00412d70* block = *cursor++; destination->Assign(*block); destination->Assign(*block); }
    return 0;
}
#pragma code_seg()
