#include "th10/app/frame_rate_counter_native.hpp"

// 0x00413690: the FPS counter's draw task: counter in ECX, result in EAX, plain RET.
#pragma code_seg(".text$09callback")
__declspec(noinline) int __fastcall FpsCounter_OnDraw(FrameRateCounter_004134b0 *counter) {
    return counter->Draw();
}
#pragma code_seg()
