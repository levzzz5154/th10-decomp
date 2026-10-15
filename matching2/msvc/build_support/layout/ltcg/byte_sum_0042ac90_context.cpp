// Compiler context only; its bytes are not recovered game code.
#include "../../../src/unreferenced/unassigned_0042ac90.cpp"

#pragma code_seg(".text$03context")
int __stdcall Ctx(const unsigned char** a, int* b, int n) {
    int s = 0;
    for (int i = 0; i < n; ++i) s += SumPayload(a[i], b[i]);
    return s;
}
#pragma code_seg()
