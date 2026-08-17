#pragma once

#include <cstdint>

// 0x0041BA50 - Sweep the 0x96 enemy slots (0x3F0-byte stride starting
// at manager+0x3C0) for finished pickup effects: a slot whose active
// word (+0x30) is set and whose kind word (+0x34) is 1 or 4 is
// deactivated, spawns drop kind 9 with id -1, angle -pi/2, and speed
// 2.2 (retail 0x0041BB00), and triggers the pickup sound (retail
// 0x00448DB0 on the sample handle at DAT_004776F0+0x3E0B50). The
// decompiled 10/11 -> kind 5 branch is unreachable and dropped. Both
// edges are injected. Always returns 0.
uint32_t Enemy_SweepPendingDrops(
    uint8_t* manager,
    void (*spawn_drop)(uint8_t* slot, int32_t kind, int32_t id, float angle,
                       float speed),
    void (*play_drop_sound)());
