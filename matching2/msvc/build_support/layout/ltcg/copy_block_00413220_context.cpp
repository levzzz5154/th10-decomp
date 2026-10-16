// Compiler context only; never selected as recovered game code.
#include "../../../src/unreferenced/FUN.cpp_413220.cpp"
#pragma code_seg(".text$03context")
int __stdcall CopyBlockCompilerContext_00413220(CopyValue5** blocks, int count, CopyBlock6* destination) {
    CopyValue5** cursor = blocks;
    while (count--) { CopyValue5* block = *cursor++; destination->Assign(*block); destination->Assign(*block); }
    return 0;
}
#pragma code_seg()
