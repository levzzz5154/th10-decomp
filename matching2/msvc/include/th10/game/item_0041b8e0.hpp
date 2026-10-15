#pragma once

#include "th10/render/animation_object_0043e5a0.hpp"

struct ItemVec3_0041b8e0 {
    float x;
    float y;
    float z;
};

// The playfield origin sits at (224, 16) on screen; the out-of-line copy of
// this helper is 0x004187F0.
inline void PlayfieldToScreen_0041b8e0(const ItemVec3_0041b8e0* playfield,
                                       ItemVec3_0041b8e0* screen) {
    screen->x = playfield->x + 224.0f;
    screen->y = playfield->y + 16.0f;
    screen->z = playfield->z;
}

// One pooled item. The record begins with its animation object, which the
// drawing code hands to the animation routines unchanged.
struct Item_0041b8e0 {
    unsigned char reserved_000[0x2FF];
    unsigned char sprite_alpha;                        // +0x2FF
    unsigned char reserved_300[0x334 - 0x300];
    ItemVec3_0041b8e0 sprite_position;                 // +0x334
    unsigned char reserved_340[0x384 - 0x340];
    short sprite_index;                                // +0x384
    unsigned char reserved_386[0x3AC - 0x386];
    ItemVec3_0041b8e0 position;                        // +0x3AC
    unsigned char reserved_3b8[0x3DC - 0x3B8];
    int state;                                         // +0x3DC
    int variant;                                       // +0x3E0
    int type;                                          // +0x3E4
    unsigned char reserved_3e8[0x3F0 - 0x3E8];

    // 0x0041BE40
    __declspec(noinline) int EnterState2();

    AnimationObject_0043e5a0* Sprite() {
        return reinterpret_cast<AnimationObject_0043e5a0*>(this);
    }
};

struct ItemStage_0041b8e0 {
    unsigned char reserved_000000[0x3E0B50];
    Resource_0043e5a0* item_sprites;                   // +0x3E0B50
};

extern "C" ItemStage_0041b8e0* g_bullet_manager;
