#include "th10/math/timer.hpp"

extern float g_frame_timer_normal_lower;  // 0x00470B68
extern float g_frame_timer_normal_upper;  // 0x00470B64

// 0x00404ED0. The value of += retains the x87 sum for the integer conversion,
// while also storing the binary32 elapsed field.
#pragma code_seg(".text$010timer")
void FrameTimer::Tick() {
    previous = current;
    if (*speed > g_frame_timer_normal_lower && *speed < g_frame_timer_normal_upper) {
        ++current;
        elapsed += 1.0f;
    } else {
        current = int(elapsed += *speed);
    }
}
