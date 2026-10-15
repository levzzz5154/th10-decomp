// Compiler context only; its bytes are not recovered game code.
#include "../../src/unreferenced/unassigned_0044d640.cpp"

#pragma code_seg(".text$03context")
int __stdcall Ctx(InterfaceList_0044d640** l, int n) {
    int r = 0;
    for (int i = 0; i < n; ++i) r += AnyFlagSet_0044d640(l[i]);
    return r;
}
#pragma code_seg()
