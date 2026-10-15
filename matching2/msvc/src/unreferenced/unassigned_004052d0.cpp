// 0x004052D0: advance the frame timer by an integer count.
//
// The timer pointer arrives in ECX, a plain __thiscall receiver.
#include "th10/math/timer.hpp"

struct TimerAdvancer {
    __declspec(noinline) void AdvanceCount(int count);
};

void TimerAdvancer::AdvanceCount(int count) {
    ((FrameTimer*)this)->Advance((float)count);
}
