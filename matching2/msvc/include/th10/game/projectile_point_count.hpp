#ifndef TH10_GAME_PROJECTILE_POINT_COUNT_HPP
#define TH10_GAME_PROJECTILE_POINT_COUNT_HPP

#include <stddef.h>
#include "th10/math/vector.hpp"

// The sprite a projectile is drawn with, as far as scoring needs it.
struct ProjectileSprite {
    unsigned char reserved_00[0x34];
    float size;                          // +0x34
};

struct ProjectileRecord {
    unsigned char reserved_000[0x39C];
    ProjectileSprite* sprite;            // +0x39C
    unsigned char reserved_3a0[0x14];
    Vec3 position;                       // +0x3B4
    unsigned char reserved_3c0[0x30];
    float width;                         // +0x3F0
    float height;                        // +0x3F4
    unsigned char reserved_3f8[0x4E];
    unsigned short state;                // +0x446: 0 free, 3 leaving
    unsigned char reserved_448[0x7F0 - 0x448];
};

struct ProjectileManager {
    unsigned char reserved_00[0x60];
    ProjectileRecord records[2000];      // +0x60

    // 0x004084A0: weigh the projectiles that have a corner within `radius`
    // of `point`. Retail never calls it.
    __declspec(noinline) int CountNearPoint(const Vec3* point, float radius);
};

typedef char ProjectileRecord_size[sizeof(ProjectileRecord) == 0x7F0 ? 1 : -1];
typedef char ProjectileRecord_width[offsetof(ProjectileRecord, width) == 0x3F0 ? 1 : -1];
typedef char ProjectileRecord_state[offsetof(ProjectileRecord, state) == 0x446 ? 1 : -1];

#endif
