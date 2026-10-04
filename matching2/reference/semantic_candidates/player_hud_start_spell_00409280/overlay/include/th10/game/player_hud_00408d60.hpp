#pragma once
#include <stddef.h>
#include "th10/math/timer.hpp"
#include "th10/math/vector.hpp"
#include "th10/render/animation_object_0043e5a0.hpp"
#include "th10/render/animation_stop_frame_handle.hpp"
#include "th10/render/position_setter_pair.hpp"

// One sprite of the in-game side panel.
struct HudSprite_00408d60 {
    unsigned char reserved_000[0x304];
    unsigned short stop_frame;                     // +0x304
    unsigned char reserved_306[0x3AC - 0x306];
};

// The in-game side panel: the two fixed sprites, the bonus digits and the
// two two-digit counters, driven by the scheduler callback at 0x00409220.
struct PlayerHud_00408d60 {
    unsigned char reserved_0000[0x10];
    HudSprite_00408d60 frame_sprite;               // +0x0010
    HudSprite_00408d60 label_sprite;               // +0x03BC
    AnimationHandle_00449470 panel_handles[3];     // +0x0768
    PositionScriptId_004492f0 marker_handle;       // +0x0774
    HudSprite_00408d60 bonus_digits[8];            // +0x0778
    HudSprite_00408d60 counter_digits[5];          // +0x24D8
    FrameTimer timer;                              // +0x3734
    char spell_name[0x3788 - 0x3748];              // +0x3748
    int record_index;                              // +0x3788
    unsigned int flags;                            // +0x378C
    int bonus;                                     // +0x3790
    int bonus_start;                               // +0x3794
    int bonus_duration;                            // +0x3798
    Vec3 marker_position;                          // +0x379C

    __declspec(noinline) int Update();
    __declspec(noinline) void StartSpell(int index, const char* name, int duration);
};

typedef char PlayerHud_digits[offsetof(PlayerHud_00408d60, bonus_digits) == 0x778 ? 1 : -1];
typedef char PlayerHud_counters[offsetof(PlayerHud_00408d60, counter_digits) == 0x24D8 ? 1 : -1];
typedef char PlayerHud_timer[offsetof(PlayerHud_00408d60, timer) == 0x3734 ? 1 : -1];
typedef char PlayerHud_position[offsetof(PlayerHud_00408d60, marker_position) == 0x379C ? 1 : -1];

extern "C" int __fastcall PlayerManagerPrimary_00409220(PlayerHud_00408d60* hud);
