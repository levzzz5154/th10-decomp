#include "../../src/render/fun_0043c500_0043c500.cpp"
#include "../../src/render/special_quad.cpp"
#include "../../src/render/anm_batch_flush.cpp"
#pragma code_seg(".text$07context")
extern "C" int __stdcall OverlayDrawContext(AsciiOverlay_0043C500* overlays,int count) {
    int result=0;
    while(count--) { result += overlays->Draw(); ++overlays; }
    return result;
}
#pragma code_seg()
