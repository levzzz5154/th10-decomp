#include "th10/source_views/frame_timer_ef24e7_0.hpp"
#include "th10/source_views/frame_timer_ef24e7_1.hpp"
#include "th10/source_views/frame_timer_ef24e7_2.hpp"
void FrameTimer::Decrement(int count) {
    Advance(float(-count));
}
