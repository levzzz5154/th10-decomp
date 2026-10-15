#pragma once
#include <stddef.h>
#include <string.h>
#include "th10/core/func_ctrl.hpp"
#include "th10/math/timer.hpp"
struct Screen {
    unsigned int flags;
    unsigned int reserved04;
    SchedulerTask* primary; // update task +08
    SchedulerTask* secondary; // draw task +0C
    int mode;
    unsigned int reserved14;
    int opacity; // current overlay alpha +18
    int duration_or_strength; // duration, or envelope shake strength +1C
    int parameter20; // interpreted according to the selected effect
    int parameter24;
    int parameter28;
    unsigned int release_phase; // two-phase fade release trigger +2C
    FrameTimer timer;
    Screen() {
        // Retail accesses the timer flag word before clearing the entire state.
        // Keep both accesses even though the wipe replaces the cleared flag.
        timer.flags &= ~1u;
        memset(this, 0, sizeof(*this));
        flags |= 2u;
    }

    __declspec(noinline) void Configure(int priority, int mode, int duration_or_strength,
        int parameter20, int parameter24, int parameter28);
    __declspec(noinline) int UpdateEnvelopeShake();
};
typedef char RuntimeSelectorOwner_size[sizeof(Screen)==0x44 ? 1:-1];
typedef char RuntimeSelectorOwner_timer_offset[offsetof(Screen,timer)==0x30 ? 1:-1];
__declspec(noinline) Screen* __stdcall Screen_Create(
    int priority, int mode, int duration_or_strength, int parameter20, int parameter24, int parameter28);

typedef char Screen_primary_offset[offsetof(Screen,primary) == 8 ? 1 : -1];
typedef char Screen_secondary_offset[offsetof(Screen,secondary) == 12 ? 1 : -1];
typedef char Screen_mode_offset[offsetof(Screen,mode) == 16 ? 1 : -1];
typedef char Screen_opacity_offset[offsetof(Screen,opacity) == 24 ? 1 : -1];
typedef char Screen_duration_or_strength_offset[offsetof(Screen,duration_or_strength) == 28 ? 1 : -1];
typedef char Screen_parameter20_offset[offsetof(Screen,parameter20) == 32 ? 1 : -1];
typedef char Screen_parameter24_offset[offsetof(Screen,parameter24) == 36 ? 1 : -1];
typedef char Screen_parameter28_offset[offsetof(Screen,parameter28) == 40 ? 1 : -1];
typedef char Screen_release_phase_offset[offsetof(Screen,release_phase) == 44 ? 1 : -1];
