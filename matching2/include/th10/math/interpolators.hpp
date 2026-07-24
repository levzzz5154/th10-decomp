// =============================================================================
// interpolators.hpp - Embedded interpolator state blocks
// Retail functions: 0x00404610, 0x00441AD0, 0x00441600, 0x00441950
// =============================================================================
#ifndef TH10_MATH_INTERPOLATORS_HPP
#define TH10_MATH_INTERPOLATORS_HPP

enum { INTERP_INT_SENTINEL = -999999 };

// Retail layout: [0..2] position, [3..5] velocity/control-B, [9..B]
// acceleration/control-A, [C] elapsed, [D] duration, [12] mode.
struct Interp3F {
    float position[3];
    float velocity[3];
    float start[3];
    float acceleration[3];
    float target[3];
    int elapsed;
    int duration;
    int mode;
    float speed; // global speed multiplier (DAT_00476F78 dereference)
};

struct Interp2F {
    float value[2];
    float start[2];
    float target[2];
    int elapsed;
    int duration;
    int mode;
};

struct Interp3I {
    int value[3];
    int start[3];
    int target[3];
    int elapsed;
    int duration;
    int mode;
};

struct Interp1I {
    int value;
    int start;
    int target;
    int elapsed;
    int duration;
    int mode;
};

int Interp3F_Tick(Interp3F* state);
int Interp2F_Tick(Interp2F* state);
int Interp3I_Tick(Interp3I* state);
int Interp1I_Tick(Interp1I* state);

#endif // TH10_MATH_INTERPOLATORS_HPP
