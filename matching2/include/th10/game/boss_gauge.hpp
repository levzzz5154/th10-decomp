#pragma once

#include <cstdint>

// Anchor record referenced from a gauge sprite (retail sprite +0x58).
struct GaugeAnchor {
    uint32_t reserved_00;  // +0x00
    float x;               // +0x04
    float y;               // +0x08
    uint8_t reserved_0c[0x1C - 0x0C];
    int8_t cell_index;     // +0x1C, grid cell selector
};

// Fragment of the gauge sprite state. Retail offsets: position at
// +0x14/+0x18, flags at +0x1C, origin at +0x20/+0x24, anchor pointer at
// +0x58 (a 32-bit slot in retail; the host layout pads it to the next
// pointer boundary).
struct GaugeSprite {
    uint8_t reserved_00[0x14];
    float x;                    // +0x14
    float y;                    // +0x18
    uint32_t flags;             // +0x1C, cleared by the recompute
    float origin_x;             // +0x20
    float origin_y;             // +0x24
    uint8_t reserved_28[0x58 - 0x28];
    const GaugeAnchor* anchor;  // +0x58
};

// 0x00428C20 - Recompute a gauge sprite's position from the owner's
// grid-cell table: cell integers at owner + 0x3244/0x3248 (0x98-byte
// stride selected by the anchor's cell index) scaled by the pixel-scale
// global, then offset by the anchor position relative to the sprite
// origin. Always returns 0.
int32_t BossGauge_ComputeSpritePosition(const uint8_t* owner,
                                        GaugeSprite* sprite);

// 0x00428E10 - Store a boss's grid cell pair at +0x3CC/+0x3D0, refresh
// the scaled position floats at +0x3C0/+0x3C4, and raise the refresh
// word of all four gauge channels (+0x332C onward, 0x98-byte stride).
void Boss_SetGridCell(uint8_t* boss, const int32_t cell[2]);
