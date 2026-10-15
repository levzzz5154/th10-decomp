// Compiler context only; its bytes are not recovered game code.
#include "../../src/core/main/gdi_font_cache.cpp"

#pragma code_seg(".text$03context")
int __stdcall Ctx(GdiSurface_00436a30** s, int n) {
    int r = 0;
    for (int i = 0; i < n; ++i) r += ReleaseSurface_00436a30(s[i]);
    return r;
}
#pragma code_seg()
