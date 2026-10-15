// Compiler context only; never selected as recovered game code.
#include "../../src/unreferenced/FUN_00413220_00413220.cpp"
#pragma code_seg(".text$03context")
int __stdcall CopyBlockCompilerContext_00413220(CopyValue_00413220** blocks, int count, CopyBlock_00413220* destination) {
    CopyValue_00413220** cursor = blocks;
    while (count--) { CopyValue_00413220* block = *cursor++; destination->Assign(*block); destination->Assign(*block); }
    return 0;
}
#pragma code_seg()
