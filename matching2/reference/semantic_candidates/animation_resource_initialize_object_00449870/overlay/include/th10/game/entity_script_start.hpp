#pragma once
#include "th10/game/entity.hpp"

// D3DX-style constructed vector. Assigning a temporary of it is what leaves
// retail's component-by-component copy through the stack in the routines that
// reset an entity's position vectors.
struct Vector3Value : Vector3 {
    Vector3Value(float x_, float y_, float z_) {
        x = x_;
        y = y_;
        z = z_;
    }
};

// The two layer bytes at the end of the animation object.
struct AnimationObjectTail {
    unsigned char reserved_000[0x3A0];
    unsigned char layer_3a0;                           // +0x3A0
    unsigned char layer_3a1;                           // +0x3A1
};

inline AnimationObjectTail* EntityTail(Entity* entity) {
    return reinterpret_cast<AnimationObjectTail*>(entity);
}
