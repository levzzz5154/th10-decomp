// Compiler context only; its bytes are not recovered game code.
#include "../../../src/unreferenced/unassigned_44bcd0.cpp"

#pragma code_seg(".text$03context")
int __stdcall Ctx(Vec28** a, Vec28** b, float f, int n) {
    while (n--) Rotate(*a++, *b++, f);
    return 0;
}
#pragma code_seg()
