#ifndef TH10_BULLET_RUNTIME_ACTIONS_HPP
#define TH10_BULLET_RUNTIME_ACTIONS_HPP

#include "th10/game/player_motion_helpers_004074b0_004076a0.hpp"
#include "th10/game/player_homing_00407ef0.hpp"

struct EffectVector3_00407560 {
    float x;
    float y;
    float z;

    EffectVector3_00407560(float x_value, float y_value, float z_value)
        : x(x_value), y(y_value), z(z_value) {}

    EffectVector3_00407560 operator*(float scale) const {
        return EffectVector3_00407560(x * scale, y * scale, z * scale);
    }

    EffectVector3_00407560& operator+=(const EffectVector3_00407560& value) {
        x += value.x;
        y += value.y;
        z += value.z;
        return *this;
    }
};

// 0x00407560..0x00407690: accelerate the enemy's velocity and auxiliary
// motion until the duration expires, then advance the frame timer.
struct EffectAccel_00407560 {
    unsigned char reserved_000[0x3C0];
    EffectVector3_00407560 velocity; // +0x3C0
    unsigned char reserved_3cc[0x0C];
    float auxiliary; // +0x3D8
    unsigned char reserved_3dc[8];
    float angle; // +0x3E4
    unsigned char reserved_3e8[0x43C - 0x3E8];
    unsigned int flags; // +0x43C
    unsigned char reserved_440[0x648 - 0x440];
    int previous;                 // +0x648
    int current;                  // +0x64C
    float elapsed;                // +0x650
    float* time_scale;            // +0x654
    unsigned int timer_flags;     // +0x658
    float auxiliary_acceleration; // +0x65C
    unsigned char reserved_660[4];
    EffectVector3_00407560 acceleration; // +0x664
    int duration;                        // +0x670

    __declspec(noinline) void Update();
};

#endif
