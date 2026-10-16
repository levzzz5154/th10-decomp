// Compiler context only; its bytes are not recovered game code.
#include "../../../src/unreferenced/unassigned_4043d0.cpp"

#pragma code_seg(".text$03context")
int __stdcall Ctx(Object** o, const Vec34* a, const Vec34* b, int n) {
    for (int i = 0; i < n; ++i) SetVectors(o[i], a + i, b + i);
    return 0;
}
#pragma code_seg()
