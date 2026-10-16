// Compiler context only; its bytes are not recovered game code.
#include "../../../src/unreferenced/unassigned_437670.cpp"

#pragma code_seg(".text$03context")
int __stdcall Ctx(GdiSurface4** g, Surface3** s, int n) {
    int r = 0;
    for (int i = 0; i < n; ++i) r += WriteTo(g[i], s[i]);
    return r;
}
#pragma code_seg()
