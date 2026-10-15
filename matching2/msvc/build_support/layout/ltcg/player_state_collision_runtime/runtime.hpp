#pragma once
#include <stddef.h>
#include "registration.hpp"
#include <math.h>
#include "timer.hpp"
#include "th10/game/player.hpp"
#include "th10/game/bomb.hpp"

typedef Vector3 Vec3;
inline void Vector3::SnapToHundredths() {
    x = (float)floor(x * 100.0f) * 0.01f;
    y = (float)floor(y * 100.0f) * 0.01f;
}
typedef Vec3 PickupPosition;
struct PickupAnimation;
struct SpriteResource {
    unsigned char reserved_00[0x30];
    float width, height;
};
struct PickupAnimationNode {
    PickupAnimation* object;
    PickupAnimationNode* next;
    PickupAnimationNode* previous;
};
struct PickupAnimation {
    unsigned int id;
    PickupAnimation* manager_node_animation;
    unsigned char reserved_008[0x0c];
    PickupAnimationNode* child_next;
    PickupAnimationNode* child_previous;
    unsigned char reserved_01c[0x10];
    float angle;  // Entity::rotation.z at +0x2C
    unsigned char reserved_030[0x0c];
    float scale_x, scale_y;
    unsigned char reserved_044[0x304-0x44];
    unsigned short stop_frame;
    unsigned char reserved_306[0x340-0x306];
    PickupPosition position;
    unsigned char reserved_34c[0x35c-0x34c];
    unsigned int flags;
    unsigned char reserved_360[0x394-0x360];
    SpriteResource* sprite;
    unsigned char reserved_398[0x3ac-0x398];
};
struct PickupAnimationLists {
    unsigned char reserved_000000[0x72dad4];
    PickupAnimationNode* primary;
    PickupAnimationNode* primary_tail;
    PickupAnimationNode* secondary;
    __forceinline PickupAnimation* FindInBuckets(AnimationRef handle) {
        if (!handle.value) return 0;
        for (PickupAnimationNode* node=primary; node; node=node->next)
            if (node->object->id==handle.value) return node->object;
        for (PickupAnimationNode* node=secondary; node; node=node->next)
            if (node->object->id==handle.value) return node->object;
        return 0;
    }
    __declspec(noinline) PickupAnimation* Find(AnimationRef handle);
    __declspec(noinline) void* MarkForRemoval(AnimationRef handle);
};
struct PickupGameState { unsigned char reserved_0000[0x378c]; unsigned char flags; };
struct PickupConfig { unsigned char reserved_00[0x10]; int alternate_mode;
    unsigned char reserved_14[0x60-0x14]; int enabled; };
// Retail takes an optional output word in ECX and the three inputs on the
// stack. MSVC 7.1 supports the observed null receiver at this boundary.
struct PlayerDamage {
    int value;
    // 0x00428630: the damage the player's bullets and damage sources deal to
    // an enemy box this frame.
    __declspec(noinline) int Sweep(Player*, const PickupPoint*, const PickupPoint*);
};
extern "C" {
extern PickupGameState* g_card;
extern PickupConfig* g_enemy_ctrl;
extern int data_00474c68, data_00474c44;
extern void* g_sprt_ctrl;
extern float g_game_speed;
}
__declspec(noinline) AnimationRef __stdcall Pickup_CreatePrimaryBack(
    void* resource, int script, int layer);
// 0x00427B50: start a damage source at `position`.
extern "C" __declspec(noinline) PlayerDamageSource* __fastcall Player_AddDamageSource(
    unsigned int unused, Player*, const PickupPosition* volatile position,
    unsigned int radius_bits, unsigned int speed_bits, int countdown, unsigned int value);

#define PICKUP_CHECK(name, expression) typedef char name[(expression) ? 1 : -1]
PICKUP_CHECK(animation_reference_size, sizeof(AnimationRef)==4);
PICKUP_CHECK(animation_angle, offsetof(PickupAnimation,angle)==0x2c);
PICKUP_CHECK(animation_child_previous, offsetof(PickupAnimation,child_previous)==0x18);
PICKUP_CHECK(animation_size, sizeof(PickupAnimation)==0x3ac);
PICKUP_CHECK(animation_position, offsetof(PickupAnimation,position)==0x340);
PICKUP_CHECK(animation_sprite, offsetof(PickupAnimation,sprite)==0x394);
PICKUP_CHECK(animation_stop, offsetof(PickupAnimation,stop_frame)==0x304);
PICKUP_CHECK(animation_flags, offsetof(PickupAnimation,flags)==0x35c);
PICKUP_CHECK(animation_node_size, sizeof(PickupAnimationNode)==0x0c);

#undef PICKUP_CHECK
