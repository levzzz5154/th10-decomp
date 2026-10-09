// 0x0044BF40's body, compiled here only so this link derives its entry
// convention (timer in ESI). The recovered function is src/math/frame_timer.cpp.
#include "th10/math/timer.hpp"
#pragma code_seg(".text$09bucketm_timer")
void FrameTimer::Advance(float delta) {
    previous = current;
    if (*speed > g_frame_timer_normal_lower && *speed < g_frame_timer_normal_upper) {
        elapsed += delta;
    } else {
        elapsed += delta * *speed;
    }
    current = int(elapsed);
}
#pragma code_seg()
