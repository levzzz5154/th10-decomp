#pragma once
#include <stddef.h>
#include <string.h>
#include "th10/game/scheduler.hpp"
#include "th10/math/timer.hpp"
struct ScreenEffectController_0043c970 {
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
    ScreenEffectController_0043c970() {
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
typedef char RuntimeSelectorOwner_size[sizeof(ScreenEffectController_0043c970)==0x44 ? 1:-1];
typedef char RuntimeSelectorOwner_timer_offset[offsetof(ScreenEffectController_0043c970,timer)==0x30 ? 1:-1];
__declspec(noinline) ScreenEffectController_0043c970* __stdcall CreateScreenEffect_0043c8b0(
    int priority, int mode, int duration_or_strength, int parameter20, int parameter24, int parameter28);

typedef char ScreenEffectController_primary_offset[offsetof(ScreenEffectController_0043c970,primary) == 8 ? 1 : -1];
typedef char ScreenEffectController_secondary_offset[offsetof(ScreenEffectController_0043c970,secondary) == 12 ? 1 : -1];
typedef char ScreenEffectController_mode_offset[offsetof(ScreenEffectController_0043c970,mode) == 16 ? 1 : -1];
typedef char ScreenEffectController_opacity_offset[offsetof(ScreenEffectController_0043c970,opacity) == 24 ? 1 : -1];
typedef char ScreenEffectController_duration_or_strength_offset[offsetof(ScreenEffectController_0043c970,duration_or_strength) == 28 ? 1 : -1];
typedef char ScreenEffectController_parameter20_offset[offsetof(ScreenEffectController_0043c970,parameter20) == 32 ? 1 : -1];
typedef char ScreenEffectController_parameter24_offset[offsetof(ScreenEffectController_0043c970,parameter24) == 36 ? 1 : -1];
typedef char ScreenEffectController_parameter28_offset[offsetof(ScreenEffectController_0043c970,parameter28) == 40 ? 1 : -1];
typedef char ScreenEffectController_release_phase_offset[offsetof(ScreenEffectController_0043c970,release_phase) == 44 ? 1 : -1];
