#pragma once

// Rain-drop effect pool update (retail 0x0042B6F0).
#include "th10/util/scalars.hpp"

// One weather droplet slot; the retail pool packs 0x2D3 of these with a
// 0x40-byte stride.
struct RainDrop {
    float position;           // retail +0x00: gravity-driven coordinate
    float unused_04;          // retail +0x04
    float unused_08;          // retail +0x08
    float previous_frame;     // retail +0x0C: frame value from the last tick
    float frame;              // retail +0x10: whole-number frame counter
    float timer;              // retail +0x14: accumulated control time
    const float* control;     // retail +0x18: shared playback-speed word
    float unused_1c[3];       // retail +0x1C..0x27
    Byte active;        // retail +0x28: slot-live flag
    Byte padding[23];   // fill to the 0x40-byte retail stride
};

int EffectPool_UpdateDrops(RainDrop* drops, int count, float gravity,
                           float gravity_scale, float span_low,
                           float span_high, float frame_step,
                           long long (*float_to_long)(float value));
