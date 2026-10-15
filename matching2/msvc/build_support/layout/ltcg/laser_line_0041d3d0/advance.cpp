#include "types.hpp"
#pragma code_seg(".text$90advance")
void FrameTimer::Advance(float delta) {
    previous=current;
    if (*speed>g_frame_timer_normal_lower && *speed<g_frame_timer_normal_upper)
        elapsed+=delta;
    else elapsed+=delta * *speed;
    current=int(elapsed);
}
#pragma code_seg()
