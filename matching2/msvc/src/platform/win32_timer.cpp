#include "th10/platform/win32_timer.hpp"
#include "th10/platform/midi_timer.hpp"

extern Win32TimerVtable g_win32_timer_vtable;

extern "C" {
__declspec(dllimport) unsigned int __stdcall timeGetDevCaps(Win32TimerCaps*, unsigned int);
__declspec(dllimport) unsigned int __stdcall timeBeginPeriod(unsigned int);
__declspec(dllimport) unsigned int __stdcall timeSetEvent(unsigned int, unsigned int,
                                                        Win32TimerCallback, unsigned int,
                                                        unsigned int);
void __cdecl free(void*);
}

__forceinline void Win32Timer::Finish() {
    vtable = &g_win32_timer_vtable;
    Cancel();
    // Both original cleanup bodies release the period a second time.
    timeEndPeriod(caps.minimum_period);
}

// 0x0043A600. The native LTCG caller keeps this in ESI.
#pragma code_seg(".text$50construct")
Win32Timer::Win32Timer() {
    vtable = &g_win32_timer_vtable;
    timeGetDevCaps(&caps, sizeof caps);
    timer_id = 0;
}

// 0x004203C0 and 0x0043A620 contain separate copies of the same cleanup.
#pragma code_seg(".text$30release")
void Win32Timer::Release() {
    Finish();
}

#pragma code_seg(".text$70destruct")
Win32Timer::~Win32Timer() {
    Finish();
}

// 0x0043A650. A null callback uses virtual timer notification on this object.
#pragma code_seg(".text$80start")
unsigned int Win32Timer::Start(unsigned int delay, Win32TimerCallback callback,
                              unsigned int user) {
    Cancel();
    timeBeginPeriod(caps.minimum_period);
    const unsigned int periodic = 1;
    if (callback) {
        timer_id = timeSetEvent(delay, caps.minimum_period, callback, user, periodic);
    } else {
        timer_id = timeSetEvent(delay, caps.minimum_period,
                               reinterpret_cast<Win32TimerCallback>(&MidiTimer_Callback),
                               reinterpret_cast<unsigned int>(this), periodic);
    }
    return timer_id;
}

// 0x0043A6B0. The original always reports success after cancellation.
#pragma code_seg(".text$90stop")
int Win32Timer::Stop() {
    Cancel();
    return 1;
}

// 0x004203A0. Low flag bit controls the deleting-destructor allocation release.
#pragma code_seg(".text$10delete")
Win32Timer* Win32Timer::Delete(unsigned int flags) {
    Release();
    if (flags & 1) {
        free(this);
    }
    return this;
}
#pragma code_seg()
