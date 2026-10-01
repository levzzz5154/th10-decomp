#include "../../src/math/timer_return.cpp"

#pragma code_seg(".text$03context")
extern "C" __declspec(noinline) int __stdcall TimerReturnContext(
        ReturningFrameTimer* timers, int count) {
    int sum = 0;
    for (int index = 0; index < count; ++index)
        sum += timers[index].TickReturningFrame();
    return sum;
}
#pragma code_seg()
