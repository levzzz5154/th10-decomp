// Compiler context only; its bytes are not recovered game code.
#include "../../../src/unreferenced/unassigned_00437590.cpp"

#pragma code_seg(".text$03context")
int __stdcall Ctx(GdiSurface_00437590** g, Surface_00437590** s, int n) {
    int r = 0;
    for (int i = 0; i < n; ++i) r += ReadFrom(g[i], s[i]);
    return r;
}
#pragma code_seg()
