// 0x004052D0: advance the frame timer by an integer count.
//
// The timer pointer arrives in ECX, a plain __thiscall receiver.
#include "th10/math/timer.hpp"

struct TimerAdvancer_004052d0 {
    __declspec(noinline) void AdvanceCount(int count);
};

void TimerAdvancer_004052d0::AdvanceCount(int count) {
    ((FrameTimer*)this)->Advance((float)count);
}
