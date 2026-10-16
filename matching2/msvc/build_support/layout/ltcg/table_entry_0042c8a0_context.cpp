// Compiler context only; its bytes are not recovered game code.
#include "../../../src/unreferenced/unassigned_42c8a0.cpp"

#pragma code_seg(".text$03context")
int __stdcall Ctx(Table* t, int n) {
    int s = 0;
    for (int i = 0; i < n; ++i) s += TableEntry(t, i, n - i);
    return s;
}
#pragma code_seg()
