#include "th10/source_views/frame_timer_ef24e7_0.hpp"
#include "th10/source_views/frame_timer_ef24e7_1.hpp"
void FrameTimer::Advance(float delta) {
    previous = current;
    if (*speed > g_frame_timer_normal_lower && *speed < g_frame_timer_normal_upper) {
        elapsed += delta;
    } else {
        elapsed += delta * *speed;
    }
    current = int(elapsed);
}
