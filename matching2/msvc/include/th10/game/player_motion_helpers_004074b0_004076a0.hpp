#pragma once
#include <stddef.h>
#include "th10/math/timer.hpp"
#include "th10/math/angle.hpp"
struct PolarVector2_00408750 {
    float x;
    float y;
    __declspec(noinline) PolarVector2_00408750* SetPolar(float angle, float scale);
};

// Offset model for the animation-clock leaf. The player arrives in ESI at the
// retail call edge; the whole-cluster LTCG route must bind that private entry.
struct PlayerAnimationState_004074B0 {
    unsigned char reserved_000[0x3C0];
    PolarVector2_00408750 velocity;
    float velocity_z;
    unsigned char reserved_3CC[0x0C];
    float speed_3D8;
    unsigned char reserved_3DC[8];
    float angle_3E4;
    unsigned char reserved_3E8[0x54];
    unsigned int flags_43C;
    unsigned char reserved_440[0x1D4];
    FrameTimer animation_timer;

    __declspec(noinline) void AdvanceAnimationFrame();
};

struct PlayerDeathShrinkState_004076A0 {
    unsigned char reserved_000[0x3C0];
    PolarVector2_00408750 velocity;
    unsigned char reserved_3C8[0x10];
    float scalar_3D8;
    unsigned char reserved_3DC[8];
    float angle_3E4;
    unsigned char reserved_3E8[0x54];
    unsigned int flags_43C;
    unsigned char reserved_440[0x23C];
    FrameTimer death_timer;
    float fall_rate_690;
    float angle_rate_694;
    unsigned char reserved_698[0x0C];
    int death_deadline_6A4;

    __declspec(noinline) void AdvanceDeathShrink();
};


typedef char AnimationTimerOffset[offsetof(PlayerAnimationState_004074B0,animation_timer)==0x614 ? 1 : -1];
typedef char DeathTimerOffset[offsetof(PlayerDeathShrinkState_004076A0,death_timer)==0x67c ? 1 : -1];
typedef char DeathDeadlineOffset[offsetof(PlayerDeathShrinkState_004076A0,death_deadline_6A4)==0x6a4 ? 1 : -1];
