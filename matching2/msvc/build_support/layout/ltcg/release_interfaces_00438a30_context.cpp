// Compiler context only; its bytes are not recovered game code.
#include "../../../src/core/main/sprt_ctrl_release_surfaces.cpp"

#pragma code_seg(".text$03context")
int __stdcall Ctx(SprtCtrl** h, int n) {
    for (int i = 0; i < n; ++i) ReleaseAll(h[i]);
    return 0;
}
#pragma code_seg()
