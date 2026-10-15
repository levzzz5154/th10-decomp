#ifndef TH10_BULLET_RUNTIME_STATE_HPP
#define TH10_BULLET_RUNTIME_STATE_HPP
#include "th10/game/player.hpp"
#include <stddef.h>
#include "th10/game/field_contact_004266b0.hpp"
#include "th10/game/player_wrap.hpp"
#include "th10/game/bullet_runtime_deceleration.hpp"
struct MotionVector3 {
    float x, y, z;
    MotionVector3(float px, float py, float pz) : x(px), y(py), z(pz) {}
    MotionVector3 operator*(float scale) const {
        return MotionVector3(x * scale, y * scale, z * scale);
    }
    MotionVector3& operator+=(const MotionVector3& other) {
        x += other.x;
        y += other.y;
        z += other.z;
        return *this;
    }
};
struct BulletRuntimeState {
    unsigned int flags;
    int countdown;
    unsigned char animation[0x304];
    unsigned short stop_frame; // animation+304, absolute30C
    unsigned char reserved_30e[6];
    int animation_progress; // 314
    unsigned char reserved_318[0x84];
    PlayerWrapBounds_00407DA0* bounds;
    unsigned char reserved_3a0[0x14];
    MotionVector3 position;
    MotionVector3 velocity;
    unsigned char reserved_3cc[0x24];
    float collision_width, collision_height;
    unsigned char reserved_3f8[0x3c];
    int bounds_grace;
    int death_animation;
    unsigned int motion_flags;
    unsigned char reserved_440[6];
    unsigned short mode;
    unsigned char reserved_448[0x2d0];
    FrameTimer immunity_timer;
};
typedef char RuntimePositionOffset[(offsetof(BulletRuntimeState, position) == 0x3b4) ? 1 : -1];
typedef char RuntimeVelocityOffset[(offsetof(BulletRuntimeState, velocity) == 0x3c0) ? 1 : -1];
typedef char RuntimeFlagsOffset[(offsetof(BulletRuntimeState, motion_flags) == 0x43c) ? 1 : -1];
typedef char RuntimeModeOffset[(offsetof(BulletRuntimeState, mode) == 0x446) ? 1 : -1];
typedef char
    RuntimeImmunityOffset[(offsetof(BulletRuntimeState, immunity_timer) == 0x718) ? 1 : -1];
extern "C" float g_game_speed;
struct BulletAnimationResourceSource {
    unsigned char reserved_000[0x3e0b50];
    void* resource;
};
extern "C" BulletAnimationResourceSource* g_bullet_manager;
struct ProjectileCommandRuntime {
    __declspec(noinline) void Tick();
};
struct AnimationPosition_00448db0 {
    float x, y, z;
};
__declspec(noinline) void** __stdcall
AnimationManager_CreateScreenPositionedPrimary_00448db0(void*, void**, int,
                                                        const AnimationPosition_00448db0*);
extern "C" int __stdcall RunAnimationVm(void*);
extern "C" __declspec(noinline) int __stdcall BulletRuntimeTick(BulletRuntimeState*);
#endif
