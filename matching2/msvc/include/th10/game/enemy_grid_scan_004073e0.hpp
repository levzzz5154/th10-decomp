#ifndef TH10_GAME_ENEMY_GRID_SCAN_004073E0_HPP
#define TH10_GAME_ENEMY_GRID_SCAN_004073E0_HPP

#include "th10/game/player.hpp"

// A projectile pattern request: an origin, a grid of columns by rows, and an
// optional sound.
struct ProjectilePattern {
    int reserved_000;
    float x;                             // +0x004
    float y;                             // +0x008
    unsigned char reserved_00c[0x1E8];
    short columns;                       // +0x1F4
    short rows;                          // +0x1F6
    int layout;                          // +0x1F8
    unsigned int flags;                  // +0x1FC: 0x200 plays `sound`
    int sound;                           // +0x200
};

struct ProjectileRecord_004073e0 {
    unsigned char reserved_000[0x446];
    short active;                        // +0x446
    unsigned char reserved_448[0x7F0 - 0x448];
};

struct ProjectileManager_004073e0 {
    unsigned char reserved_00[0x10];
    ProjectileRecord_004073e0* current;  // +0x10
    unsigned char reserved_14[0x4C];
    ProjectileRecord_004073e0 records[1];  // +0x60
};

// 0x004067D0: spawn the projectile of one grid cell; nonzero when the pool is
// full. The pattern travels in EBX, everything else on the stack.
int __stdcall SpawnPatternCell_004067d0(ProjectilePattern* pattern,
                                        ProjectileManager_004073e0* manager,
                                        int column, int row, float aim);

// 0x004073E0: spawn every cell of a pattern, aimed at the player.
int __stdcall EnemyGrid_ScanCells_004073e0(ProjectilePattern* pattern,
                                           ProjectileManager_004073e0* manager);

#endif
