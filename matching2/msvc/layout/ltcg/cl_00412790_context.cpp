// Compiler context only; never selected as recovered game code.
#include "../../src/unreferenced/unassigned_00412790.cpp"
#pragma code_seg(".text$03context")
void __stdcall SetContext_00412790(unsigned int* values, int* indexes, void** bases, int count) {
    while (count--) {
        SetRecord_00412790(*values++, *indexes++, *bases++);
    }
}
#pragma code_seg()
