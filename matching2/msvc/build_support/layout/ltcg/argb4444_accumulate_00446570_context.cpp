// Compiler context only; its bytes are not recovered game code.
#include "../../../src/unreferenced/unassigned_446570.cpp"

#pragma code_seg(".text$03context")
int __stdcall Ctx(ColorSums3* s, const unsigned short* t, int n) {
    int count = 0;
    for (int i = 0; i < n; ++i) AccumulateArgb44442(s, t + i, &count);
    return count;
}
#pragma code_seg()
