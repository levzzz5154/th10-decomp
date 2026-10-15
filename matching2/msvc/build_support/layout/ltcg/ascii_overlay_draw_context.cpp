#include "../../../src/core/screen/flash_draw.cpp"
#include "../../../src/core/screen/special_quad.cpp"
#include "../../../src/core/sprtfunc/anm_batch_flush.cpp"
#pragma code_seg(".text$07context")
extern "C" int __stdcall OverlayDrawContext(ScreenFlashQuad* overlays,int count) {
    int result=0;
    while(count--) { result += overlays->Draw(); ++overlays; }
    return result;
}
#pragma code_seg()
