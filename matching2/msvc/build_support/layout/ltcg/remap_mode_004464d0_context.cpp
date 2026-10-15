// Compiler context only; its bytes are not recovered game code.
#include "../../../src/unreferenced/unassigned_004464d0.cpp"

#pragma code_seg(".text$03context")
int __stdcall Ctx(int* items, int n) {
    int s = 0;
    while (n--) s += RemapFormat(*items++);
    return s;
}
#pragma code_seg()
