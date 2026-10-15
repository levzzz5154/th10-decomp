#include "th10/platform/derived_timer_state_0043a750.hpp"

extern PauseVtable g_base_timer_vtable;
extern PauseVtable g_derived_timer_vtable;
extern "C" __declspec(dllimport) unsigned int __stdcall
    timeGetDevCaps(Win32TimerCaps*, unsigned int);

// 0x0043A750..0x0043A903. The private constructor receives this in ESI,
// returns the same pointer in EAX, and returns without popping arguments.
#pragma code_seg(".text$01construct")
DerivedTimerState::DerivedTimerState() {
    // Preserve the base timer's dispatch table while querying its capabilities.
    vtable = &g_base_timer_vtable;
    timeGetDevCaps(&caps, sizeof caps);
    vtable = &g_derived_timer_vtable;

    timer_id = 0;
    value13c = 0;
    value140 = 0;
    value138 = 0;
    value120 = 0;
    value124 = 0;
    value118 = 0;
    flag2c4 = 0;
    for (unsigned int index = 0; index < 7; ++index) {
        tail_values[index] = 0;
    }
    second_values.Initialize();
    first_values.Initialize();
    first_tail = 0;
    sentinel = -1;
}
#pragma code_seg()
