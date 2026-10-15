#ifndef TH10_GAME_ENEMY_DEATH_RELEASE_0040E5F0_HPP
#define TH10_GAME_ENEMY_DEATH_RELEASE_0040E5F0_HPP

#include "th10/game/item_scatter_flush.hpp"
#include "th10/game/score.hpp"
#include "th10/platform/sound_queue.hpp"

// The enemy manager at 0x00477704, as far as a dying enemy reads it.
struct EnemyCtrlDeathView {
    unsigned char reserved_00[0x30];
    void* animation_files[4];                 // +0x30
    FrameTimer clock;                         // +0x40
    int reserved_54;
    struct EnemyNode_0040e6a0* first;         // +0x58
};

// An enemy, as far as its death touches it.
struct Enemy_0040e5f0 {
    unsigned char reserved_0000[0x1068];
    DropSource_0040c9a0 position;             // +0x1068
    unsigned char reserved_1074[0x2408 - 0x1074];
    ItemDrops_0040c9a0 drops;                 // +0x2408
    int death_sound;                          // +0x2444: negative for none
    int death_script;                         // +0x2448: negative for none
    int death_file;                           // +0x244C
    unsigned char reserved_2450[0x2480 - 0x2450];
    unsigned int flags;                       // +0x2480
};

// A link of the manager's enemy list.
struct EnemyNode_0040e6a0 {
    Enemy_0040e5f0* enemy;
    EnemyNode_0040e6a0* next;
};

extern "C" EnemyCtrlDeathView* g_enemy_ctrl;
extern "C" ScoreState g_globals;

// 0x0040E5F0: sound, burst, drops and gauge hold of a dying enemy.
int __stdcall Enemy_ReleaseOnDeath_0040e5f0(Enemy_0040e5f0* enemy);

// 0x0040E6A0: start the bursts of the enemies that just died and tick the clock.
void __stdcall EnemyCtrl_SweepDeaths_0040e6a0(EnemyCtrlDeathView* manager);

#endif
