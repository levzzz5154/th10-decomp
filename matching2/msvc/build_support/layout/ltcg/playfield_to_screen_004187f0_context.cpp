// Compiler context only; its bytes are not recovered game code.
#include "../../../src/unreferenced/unassigned_4187f0.cpp"

#pragma code_seg(".text$03context")
int __stdcall Ctx(Vec318** a, Vec318** b, int n) {
    while (n--) PlayfieldToScreen(*a++, *b++);
    return 0;
}
#pragma code_seg()
