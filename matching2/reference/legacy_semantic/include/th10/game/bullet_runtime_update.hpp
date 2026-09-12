#pragma once

#include <cstdint>

struct BulletRuntimeState {
    uint32_t flags;
    int lifetime;
    float position[3];
    float velocity[3];
    int mode;
    uint32_t behavior_flags;
    int delayed_behavior_count;
    int collision_delay;
    int collision_enabled;
    void* collision_target;
    int animation_state;
};

struct BulletRuntimeHooks {
    void* context;
    float frame_speed;
    float slow_scale;
    void (*destroy)(void* context, BulletRuntimeState* bullet);
    void (*prepare)(void* context, BulletRuntimeState* bullet);
    void (*run_behavior)(void* context, BulletRuntimeState* bullet,
                         uint32_t behavior_bit);
    void (*run_delayed_behavior)(void* context, BulletRuntimeState* bullet);
    int (*collide_player)(void* context, BulletRuntimeState* bullet);
    void (*cancel_animation)(void* context, BulletRuntimeState* bullet);
    void (*play_cancel_sound)(void* context);
    void (*run_target_behavior)(void* context, BulletRuntimeState* bullet,
                                uint32_t behavior_bit);
    bool (*target_outside)(void* context, BulletRuntimeState* bullet);
    int (*tick_animation)(void* context, BulletRuntimeState* bullet);
};

// 0x00406240 - Advance one live bullet/entity record.
int BulletRuntime_Update(BulletRuntimeState* bullet,
                         const BulletRuntimeHooks* hooks);
