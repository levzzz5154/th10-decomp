#ifndef TH10_PLATFORM_WIN32_TIMER_HPP
#define TH10_PLATFORM_WIN32_TIMER_HPP

#include <stddef.h>

typedef void (__stdcall *Win32TimerCallback)(unsigned int, unsigned int,
                                            unsigned int, unsigned int,
                                            unsigned int);

struct Win32TimerCaps {
    unsigned int minimum_period;
    unsigned int maximum_period;
};

struct Win32TimerVtable;

// The first word contains the existing timer dispatch table. Its slot zero
// is used by MidiTimer_Callback; the remaining derived behavior is separate.
struct Win32Timer {
    Win32TimerVtable* vtable;       // +0x00
    unsigned int timer_id;         // +0x04
    Win32TimerCaps caps;           // +0x08

    __declspec(noinline) Win32Timer();
    __declspec(noinline) ~Win32Timer();
    __declspec(noinline) void Release();
    __declspec(noinline) unsigned int Start(unsigned int delay,
                                           Win32TimerCallback callback,
                                           unsigned int user);
    __declspec(noinline) int Stop();
    __declspec(noinline) Win32Timer* Delete(unsigned int flags);

private:
    __forceinline void Cancel();
    __forceinline void Finish();
};

typedef char Win32Timer_size_must_be_16[sizeof(Win32Timer) == 16 ? 1 : -1];
typedef char Win32Timer_id_offset_must_be_4[offsetof(Win32Timer, timer_id) == 4 ? 1 : -1];
typedef char Win32Timer_caps_offset_must_be_8[offsetof(Win32Timer, caps) == 8 ? 1 : -1];

#endif
