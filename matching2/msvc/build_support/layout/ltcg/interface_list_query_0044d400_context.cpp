// Compiler context only; its bytes are not recovered game code.
#include "../../../src/unreferenced/unassigned_0044d400.cpp"

#pragma code_seg(".text$03context")
int __stdcall Ctx(InterfaceList_0044d400** l, unsigned int* x, void** o, int n) {
    int r = 0;
    for (int i = 0; i < n; ++i) r += QueryItem_0044d400(l[i], x[i], o + i);
    return r;
}
#pragma code_seg()
