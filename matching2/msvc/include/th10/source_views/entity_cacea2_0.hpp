#pragma once
#include <string.h>
#include "../../../build_support/include/asm_encoding.hpp"
#include "../../../build_support/include/asm_symbols.hpp"


// Recovered semantic C++ definitions.
#include "th10/game/entity.hpp"

extern "C" void __cdecl entry_free_00452422(void*);
extern "C" void* __cdecl operator_new(uint32_t);


// 0x00406160 / 0x004061D0 - Playfield culling tests. The retail ABI keeps the
// tested screen position in ECX and pushes the queried extents, so both are
// members of that position. Each returns 1 while a box of `width` x `height`
// centred on the position stays clear of the playfield rectangle; the
// inclusive variant tests the playfield proper (y from 0) instead of the band
// that starts 64 pixels above it.
//
// The rectangle and the half-size scale are the shared .rdata constants the
// renderer uses, so they are read through their retail addresses.
// Playfield rectangle and frame constants shared with the renderer.
extern float g_playfield_min_x;   // 0x00470B40, -192.0
extern float g_playfield_max_x;   // 0x00470B3C,  192.0
extern float g_playfield_min_y;   // 0x00470B04,    0.0
extern float g_playfield_max_y;   // 0x00470B38,  448.0

struct PlayfieldPoint {
    float x;
    float y;
    int32_t OutsidePlayfield(float width, float height) const;
    int32_t OutsidePlayfieldInclusive(float width, float height) const;
};

