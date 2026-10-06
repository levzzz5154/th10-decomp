#pragma once

// 32-bit storage used by the complete player-effect update and its helpers.
// Sparse padding covers members this routine does not read.
#include "th10/math/timer.hpp"
#include <math.h>
#include <stddef.h>

struct Vec3 {
    float x, y, z;
    __declspec(noinline) int OutsideViewport(float horizontal_margin, float vertical_margin) const;
    Vec3 *SetPolar(float angle, float radius);
    Vec3 &operator+=(const Vec3 &other) {
        x += other.x;
        y += other.y;
        z += other.z;
        return *this;
    }
    void SnapToHundredths() {
        x = (float)floor(x * 100.0f) * 0.01f;
        y = (float)floor(y * 100.0f) * 0.01f;
    }
    Vec3 operator+(const Vec3 &other) const {
        Vec3 sum;
        sum.x = x + other.x;
        sum.y = y + other.y;
        sum.z = z + other.z;
        return sum;
    }
};
struct Motion {
    Vec3 position, velocity;
    // speed is also the orbit turn rate when flags bit 0 is set.
    float speed, angle, radius, radius_step;
    unsigned char flags;
    __declspec(noinline) void Advance();
    void Update();
};
struct SpriteResource {
    unsigned char reserved_00[0x30];
    float width, height;
};
struct AnimationNode;
struct AnimationObject {
    int id;
    AnimationObject *manager_node_animation;
    unsigned char reserved_08[0x0c];
    AnimationNode *child_next;
    AnimationNode *child_previous;
    unsigned char reserved_1c[0x10];
    float angle;
    unsigned char reserved_30[0x0c];
    float scale_x, scale_y;
    unsigned char reserved_44[0x304 - 0x44];
    unsigned short stop_frame;
    unsigned char reserved_306[0x340 - 0x306];
    Vec3 position;
    unsigned char reserved_34c[0x35c - 0x34c];
    unsigned flags;
    unsigned char reserved_360[0x394 - 0x360];
    SpriteResource *sprite;
    unsigned char reserved_398[0x3AC - 0x398];
};
struct AnimationNode {
    AnimationObject *object;
    AnimationNode *next;
};
struct AnimationContext {
    unsigned char reserved[0x72dad4];
    AnimationNode *primary;
    unsigned reserved_2;
    AnimationNode *secondary;
};
struct AnimationId {
    int value;
};
struct Handle {
    // Preserve the observed handle reloads and repeated retirement clears.
    volatile int value;
    __declspec(noinline) void StopAtFrame1();
    __declspec(noinline) void StopAtFrame3();
};

struct PlayerState;
struct EffectEntry;
struct EffectDescriptor {
    unsigned char reserved_00[0x1c];
    signed char ordinal;
    unsigned char kind;
    unsigned char reserved_1e[10];
    void(__fastcall *callback)(PlayerState *, EffectEntry *);
};
struct EffectEntry {
    FrameTimer timer;
    Motion motion;
    // The owner snapshots the initial state and preserves later access order.
    volatile int state;
    Handle primary, secondary;
    unsigned reserved_4c;
    int touched, started;
    EffectDescriptor *descriptor;
};
struct PlayerState {
    unsigned char reserved_000[0x458];
    int phase;
    void *stage_schedule;
    FrameTimer stage_timer;
    FrameTimer state_timer;
    FrameTimer auxiliary_timer;
    EffectEntry effects[128];
    unsigned char reserved_329c[0x3500 - 0x329c];
    int familiar_level;
    unsigned char reserved_3504[0x42f4 - 0x3504];
    int active_by_ordinal[6];
    FrameTimer invulnerability_timer;
    unsigned int reserved_4320;
    Vec3 secondary_half_min, secondary_half_max;
    Vec3 secondary_min, secondary_max;
    Vec3 size_min, size_max;
    struct HistoryPoint {
        int x, y;
    } history[33];
    int alternate;
};
struct FrontScript {
    unsigned char reserved[0x9eb8];
    void *script;
};
extern "C" {
extern AnimationContext *data_00491c10;
extern FrontScript *data_0047770c;
extern void *data_00477704;
float __stdcall NormalizeAngle(float value);
}
typedef char PlayerPhaseOffset[offsetof(PlayerState, phase) == 0x458 ? 1 : -1];
typedef char PlayerStageTimerOffset[offsetof(PlayerState, stage_timer) == 0x460 ? 1 : -1];
typedef char PlayerStageCurrentOffset
    [offsetof(PlayerState, stage_timer) + offsetof(FrameTimer, current) == 0x464 ? 1 : -1];
typedef char PlayerExtent[sizeof(PlayerState) == 0x4478 ? 1 : -1];
typedef char EntryExtent[sizeof(EffectEntry) == 0x5c ? 1 : -1];
typedef char MotionOffset[offsetof(EffectEntry, motion) == 0x14 ? 1 : -1];
typedef char DescriptorOffset[offsetof(EffectEntry, descriptor) == 0x58 ? 1 : -1];
typedef char EffectsOffset[offsetof(PlayerState, effects) == 0x49c ? 1 : -1];
typedef char FamiliarOffset[offsetof(PlayerState, familiar_level) == 0x3500 ? 1 : -1];
typedef char ActiveOffset[offsetof(PlayerState, active_by_ordinal) == 0x42f4 ? 1 : -1];
typedef char ChildNextOffset[offsetof(AnimationObject, child_next) == 0x14 ? 1 : -1];
typedef char ChildPreviousOffset[offsetof(AnimationObject, child_previous) == 0x18 ? 1 : -1];
typedef char AnimationExtent[sizeof(AnimationObject) == 0x3AC ? 1 : -1];
typedef char SpriteOffset[offsetof(AnimationObject, sprite) == 0x394 ? 1 : -1];

typedef char MotionExtent[sizeof(Motion) == 0x2C ? 1 : -1];
typedef char VelocityOffset[offsetof(Motion, velocity) == 0x0C ? 1 : -1];
typedef char MotionFlagsOffset[offsetof(Motion, flags) == 0x28 ? 1 : -1];
typedef char EntryStateOffset[offsetof(EffectEntry, state) == 0x40 ? 1 : -1];
typedef char PrimaryHandleOffset[offsetof(EffectEntry, primary) == 0x44 ? 1 : -1];
typedef char SecondaryHandleOffset[offsetof(EffectEntry, secondary) == 0x48 ? 1 : -1];
typedef char DescriptorCallbackOffset[offsetof(EffectDescriptor, callback) == 0x28 ? 1 : -1];
