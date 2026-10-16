// Compiler context only; its bytes are not recovered game code.
#include "../../../src/unreferenced/unassigned_437590.cpp"

#pragma code_seg(".text$03context")
int __stdcall Ctx(GdiSurface3** g, Surface2** s, int n) {
    int r = 0;
    for (int i = 0; i < n; ++i) r += ReadFrom(g[i], s[i]);
    return r;
}
#pragma code_seg()
