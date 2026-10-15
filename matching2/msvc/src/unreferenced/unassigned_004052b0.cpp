#include "th10/math/timer.hpp"

// 0x004052B0: advance the timer by minus an integer count.
//
// The timer pointer arrives in ECX (a plain __thiscall receiver) and the count
// in EAX, which only the whole-program pass of a native LTCG link selects, so
// the body is compiled as a single-function cluster.
struct TimerDecrementer {
    __declspec(noinline) void Decrement(int count);
};

#pragma code_seg(".text$01accessor")
void TimerDecrementer::Decrement(int count) {
    ((FrameTimer*)this)->Advance((float)(-count));
}
#pragma code_seg()
