#include "th10/math/timer_return.hpp"

extern float g_frame_timer_normal_lower;
extern float g_frame_timer_normal_upper;

// Advance the timer and return its new integer frame. The value of += keeps
// the x87 sum available for conversion while storing binary32 elapsed time.
#pragma code_seg(".text$01timer")
int ReturningFrameTimer::TickReturningFrame() {
    previous = current;
    if (*speed > g_frame_timer_normal_lower && *speed < g_frame_timer_normal_upper) {
        ++current;
        elapsed += 1.0f;
    } else {
        current = int(elapsed += *speed);
    }
    return current;
}
#pragma code_seg()
