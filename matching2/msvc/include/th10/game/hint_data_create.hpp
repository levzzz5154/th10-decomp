#pragma once

#include "th10/game/hint_data.hpp"

// The lists the tips live in: sixteen list heads from +0x18. New tips go to
// one of the second eight, chosen by the game state.
struct Hint {
    unsigned char reserved_000[0x18];
    HintDataNode lists[16];
};

// Part of the global game state; other code writes it through pointers.
struct HintGameState {
    unsigned char reserved_00[0x14];
    int list;                            // 0x00474C7C: which list new tips join
    int unknown_18;
    int display_mode;                    // 0x00474C84
    int display_value;                   // 0x00474C88: used when display_mode is zero
    int display_value_alternate;         // 0x00474C8C
};

extern "C" HintGameState data_00474c68;

// The game state is always reached through its address, so the compiler
// re-reads a field after any store that could alias it, as retail does.
inline HintGameState* GameState() { return &data_00474c68; }

HintData* __stdcall HintData_Create_0041a120(Hint* manager, const char* text,
                                             const HintDataPosition* position);
HintData* __stdcall HintData_CreateUrgent_00424650(Hint* manager, const char* text,
                                                   const HintDataPosition* position);
