#ifndef TH10_GAME_ITEM_SCATTER_FLUSH_HPP
#define TH10_GAME_ITEM_SCATTER_FLUSH_HPP

#include "th10/math/rng.hpp"

extern "C" RngState data_004918b0;
extern "C" float __stdcall Angle_Normalize_0044bc70(float value);

// The gameplay code draws from the shared generator inline: two steps through
// a 32-bit read of the seed, with the final word filling both halves.
__forceinline unsigned int ItemScatter_NextU32() {
    unsigned int value = *(unsigned int*)&data_004918b0.seed;
    value ^= 0x9630;
    value -= 0x6553;
    unsigned int high = ((unsigned short)value) >> 14;
    data_004918b0.seed = (unsigned short)(high + (value << 2));
    ++data_004918b0.generation;
    value = *(unsigned int*)&data_004918b0.seed;
    value ^= 0x9630;
    value -= 0x6553;
    high = ((unsigned short)value) >> 14;
    data_004918b0.seed = (unsigned short)(high + (value << 2));
    ++data_004918b0.generation;
    unsigned int word = data_004918b0.seed;
    return (word << 16) | word;
}

// 0x00413270: an offset on an ellipse.
struct ScatterOffset_0040c9d0 {
    float x;
    float y;
    float z;

    ScatterOffset_0040c9d0* SetEllipticPolar(float angle, float horizontal, float vertical);
};

// Pending item drops of an enemy.
struct ItemDrops_0040c9a0 {
    int main_item;                       // +0x00: 0 when there is none
    int counts[12];                      // +0x04: per item kind, kinds 1..11 used
    float spread_x;                      // +0x34
    float spread_y;                      // +0x38
};

// The part of an enemy that starts with its position.
struct DropSource_0040c9a0 {
    float position[3];

    // 0x0040C9D0: scatter the counted drops around the position.
    __declspec(noinline) void ScatterDrops(ItemDrops_0040c9a0* drops);
    // 0x0040C9A0: release every pending drop at the position.
    __declspec(noinline) void FlushDrops(ItemDrops_0040c9a0* drops);
};

#endif
