#include "th10/platform/timer.hpp"

extern "C" __declspec(dllimport) UINT __stdcall timeKillEvent(UINT timer_id);
extern "C" __declspec(dllimport) UINT __stdcall timeEndPeriod(UINT period);

#ifdef _MSC_VER
extern "C" char off_46F810;
extern "C" void* __imp_timeKillEvent;
extern "C" void* __imp_timeEndPeriod;
#endif

// 0x004203C0 - Restore the timer vtable and retire the multimedia timer:
// kill the pending event when one is active, then end the period twice
// around clearing the identifier. The duplicated timeEndPeriod is retail
// behavior; the MIDI teardown sequence repeats the same pair.
#ifdef _MSC_VER
__declspec(naked) void TimerWin32_Release(TimerWin32* timer, void* vtable) {
    __asm {
        mov eax, [esi+4]
        test eax, eax
        mov dword ptr [esi], offset off_46F810
        jz loc_4203D4
        push eax
        call dword ptr [__imp_timeKillEvent]
loc_4203D4:
        mov eax, [esi+8]
        push edi
        mov edi, dword ptr [__imp_timeEndPeriod]
        push eax
        call edi
        mov ecx, [esi+8]
        push ecx
        mov dword ptr [esi+4], 0
        call edi
        pop edi
        ret
    }
}
#else
void TimerWin32_Release(TimerWin32* timer, void* vtable) {
    timer->vtable = (void**)vtable;
    if (timer->timer_id != 0) {
        timeKillEvent(timer->timer_id);
    }
    timeEndPeriod(timer->period);
    timer->timer_id = 0;
    timeEndPeriod(timer->period);
}
#endif
