// 0x004052A0: rewind the frame timer one step.
//
// The timer pointer arrives in ECX, a plain __thiscall receiver.
#include "th10/math/timer.hpp"

struct TimerResetter {
    __declspec(noinline) void Rewind();
};

void TimerResetter::Rewind() {
    ((FrameTimer*)this)->Advance(-1.0f);
}
