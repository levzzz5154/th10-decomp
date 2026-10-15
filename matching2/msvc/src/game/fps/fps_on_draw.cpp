#include "th10/game/fps_runtime.hpp"

// 0x00413690: the FPS counter's draw task: counter in ECX, result in EAX, plain RET.
#pragma code_seg(".text$09callback")
__declspec(noinline) int __fastcall FPS_OnDraw(FPS *counter) {
    return counter->Draw();
}
#pragma code_seg()
