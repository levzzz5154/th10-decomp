// Compiler context only; its bytes are not recovered game code.
#include "../../src/unreferenced/unassigned_00437670.cpp"

#pragma code_seg(".text$03context")
int __stdcall Ctx(GdiSurface_00437670** g, Surface_00437670** s, int n) {
    int r = 0;
    for (int i = 0; i < n; ++i) r += WriteTo_00437670(g[i], s[i]);
    return r;
}
#pragma code_seg()
