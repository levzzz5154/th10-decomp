#include "th10/platform/timer.hpp"

extern "C" __declspec(dllimport) UINT __stdcall timeKillEvent(UINT timer_id);
extern "C" __declspec(dllimport) UINT __stdcall timeEndPeriod(UINT period);


// 0x004203C0 - Restore the timer vtable and retire the multimedia timer:
// kill the pending event when one is active, then end the period twice
// around clearing the identifier. The duplicated timeEndPeriod is retail
// behavior; the MIDI teardown sequence repeats the same pair.
void TimerWin32_Release(TimerWin32* timer, void* vtable) {
    timer->vtable = (void**)vtable;
    if (timer->timer_id != 0) {
        timeKillEvent(timer->timer_id);
    }
    timeEndPeriod(timer->period);
    timer->timer_id = 0;
    timeEndPeriod(timer->period);
}
