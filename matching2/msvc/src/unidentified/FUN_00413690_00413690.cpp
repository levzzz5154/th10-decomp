#include "th10/app/frame_rate_counter_native.hpp"

// Actual scheduler callback: counter in ECX, result in EAX, plain RET.
#pragma code_seg(".text$09callback")
__declspec(noinline) int __fastcall FpsDrawCallback_00413690(FrameRateCounter_004134b0 *counter) {
    return counter->Draw();
}
#pragma code_seg()
