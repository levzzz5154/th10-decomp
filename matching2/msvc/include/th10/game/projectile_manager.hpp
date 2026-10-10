#ifndef TH10_GAME_PROJECTILE_MANAGER_HPP
#define TH10_GAME_PROJECTILE_MANAGER_HPP

#include <stddef.h>
#include "th10/math/vector.hpp"

// The sprite a projectile is drawn with, as far as scoring needs it.
struct ProjectileSprite {
    unsigned char reserved_00[0x34];
    float size;                          // +0x34
};

struct ProjectileRecord {
    unsigned int flags;                  // +0x000: 8 = cleared by a region sweep
    unsigned char reserved_004[0x39C - 4];
    ProjectileSprite* sprite;            // +0x39C
    unsigned char reserved_3a0[0x14];
    Vec3 position;                       // +0x3B4
    unsigned char reserved_3c0[0x30];
    Vec3 size;                           // +0x3F0: width, height
    unsigned char reserved_3fc[0x4A];
    unsigned short state;                // +0x446: 0 free, 3 leaving
    unsigned char reserved_448[8];
    int lifetime;                        // +0x450
    unsigned char reserved_454[0x7EC - 0x454];
    short colour;                        // +0x7EC
    unsigned char reserved_7ee[2];
};

struct ProjectileManager {
    unsigned char reserved_00[0x44];
    Vec3 region_center;                  // +0x44
    Vec3 region_size;                    // +0x50
    unsigned char reserved_5c[4];
    ProjectileRecord records[2000];      // +0x60
    unsigned char reserved_3e0360[0x3E0B50 - 0x3E0360];
    void* animations;                    // +0x3E0B50

    // 0x004084A0: weigh the projectiles that have a corner within `radius`
    // of `point`. Retail never calls it.
    __declspec(noinline) int CountNearPoint(const Vec3* point, float radius);
};

// 0x00408210: clear the projectiles overlapping the manager's region, leaving
// a burst animation (and an item, when asked) in place of each.
__declspec(noinline) int __stdcall ProjectileManager_ClearRegion(ProjectileManager* manager,
                                                               int spawn_items);

typedef char ProjectileRecord_size[sizeof(ProjectileRecord) == 0x7F0 ? 1 : -1];
typedef char ProjectileRecord_width[offsetof(ProjectileRecord, size) == 0x3F0 ? 1 : -1];
typedef char ProjectileRecord_state[offsetof(ProjectileRecord, state) == 0x446 ? 1 : -1];
typedef char ProjectileRecord_lifetime[offsetof(ProjectileRecord, lifetime) == 0x450 ? 1 : -1];
typedef char ProjectileManager_animations[offsetof(ProjectileManager, animations) == 0x3E0B50 ? 1 : -1];

#endif
