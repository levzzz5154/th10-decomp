#pragma once
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

