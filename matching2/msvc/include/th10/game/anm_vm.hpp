#pragma once
#include <string.h>

// The game timer vtable at 0x004703E4.
extern "C" const void* const data_004703e4[];

// A game timer: its vtable and four counters, all cleared on construction.
struct GameTimer {
    const void* const* vtable;
    int previous;
    int current;
    float current_f;
    int control;

    __forceinline GameTimer() {
        vtable = data_004703e4;
        previous = 0;
        current = 0;
        current_f = 0;
        control = 0;
    }
};
typedef char GameTimer_size_check[sizeof(GameTimer) == 0x14 ? 1 : -1];

// An interpolator whose last word holds its active bit; constructing one
// clears that bit.
template <int Size>
struct AnmInterpolator {
    unsigned char state[Size - 4];
    unsigned int active : 1;
    unsigned int other_flags : 31;

    __forceinline AnmInterpolator() { active = 0; }
};

// An animation VM (0x3AC bytes). Its interpolators clear their active bits,
// then the constructor zeroes the whole VM and marks the script id unset.
struct AnmVm {
    unsigned char unknown_000[0x30];
    AnmInterpolator<0x40> interp_030;
    AnmInterpolator<0x44> interp_070;
    AnmInterpolator<0x4C> interp_0b4;
    AnmInterpolator<0x2C> interp_100;
    AnmInterpolator<0x4C> interp_12c;
    AnmInterpolator<0x3C> interp_178;
    AnmInterpolator<0x4C> interp_1b4;
    AnmInterpolator<0x2C> interp_200;
    AnmInterpolator<0x150> interp_22c;
    unsigned char unknown_37c[8];
    short script_id;
    unsigned char unknown_386[0x26];

    __forceinline AnmVm() {
        memset(this, 0, sizeof(*this));
        script_id = -1;
    }
};
typedef char AnmVm_size_check[sizeof(AnmVm) == 0x3AC ? 1 : -1];
