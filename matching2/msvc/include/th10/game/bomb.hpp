#pragma once
// The bomb: one 0x48-byte object, reached through g_bomb (0x004776EC).
// It exists for the whole stage; `active` says whether a bomb is running.
#include <stddef.h>
#include "th10/game/player.hpp"
#include "th10/math/timer.hpp"

struct Bomb {
    unsigned int flags;                      // +0x00, bit 1 = published
    unsigned int unknown_04;
    SchedulerTask* update_task;              // +0x08
    SchedulerTask* draw_task;                // +0x0C
    unsigned int unknown_10;
    FrameTimer timer;                        // +0x14, frames since the bomb started
    int active;                              // +0x28
    int animation;                           // +0x2C, animation handle
    Vector3 position;                        // +0x30, where the bomb went off
    float radius;                            // +0x3C, area that clears bullets
    float unknown_40;                        // +0x40, 4 at start
    int mode;                                // +0x44
    // 0x004059F0: what a point inside (or near) the bomb's area is hit by.
    __declspec(noinline) int HitTest(const PickupPoint* point);
};

#define BOMB_CHECK(name, expression) typedef char bomb_check_##name[(expression) ? 1 : -1]
BOMB_CHECK(timer, offsetof(Bomb, timer) == 0x14);
BOMB_CHECK(active, offsetof(Bomb, active) == 0x28);
BOMB_CHECK(position, offsetof(Bomb, position) == 0x30);
BOMB_CHECK(mode, offsetof(Bomb, mode) == 0x44);
BOMB_CHECK(size, sizeof(Bomb) == 0x48);
#undef BOMB_CHECK

extern "C" {
extern Bomb* g_bomb;  // 0x004776EC
// 0x00405860: start a bomb at the player: its animation, sound and the power
// display. Returns -1 when one is already running.
__declspec(noinline) int __stdcall Bomb_Start(Bomb* bomb);
}
