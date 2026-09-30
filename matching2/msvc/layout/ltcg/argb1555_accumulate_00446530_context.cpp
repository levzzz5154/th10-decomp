// Compiler context only; its bytes are not recovered game code.
#include "../../src/unidentified/unassigned_00446530.cpp"

#pragma code_seg(".text$03context")
int __stdcall Ctx(ColorSums_00446530* s, const unsigned short* t, int n) {
    int count = 0;
    for (int i = 0; i < n; ++i) AccumulateArgb1555_00446530(s, t + i, &count);
    return count;
}
#pragma code_seg()
