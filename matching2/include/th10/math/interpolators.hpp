// =============================================================================
// interpolators.hpp - Embedded interpolator state blocks
// Retail functions: 0x00404610, 0x00441AD0, 0x00441600, 0x00441950
// =============================================================================
#ifndef TH10_MATH_INTERPOLATORS_HPP
#define TH10_MATH_INTERPOLATORS_HPP

enum { INTERP_INT_SENTINEL = -999999 };

// Typed adapter for the retail start, target, two tangent rows and timer.
// velocity/acceleration are also the mutable integration rows in mode 17.
struct Interp3F {
    float position[3];
    float velocity[3];
    float start[3];
    float acceleration[3];
    float target[3];
    float elapsed_fraction;
    int elapsed;
    int duration;
    int mode;
    float speed; // global speed multiplier (DAT_00476F78 dereference)
};

struct Interp2F {
    float value[2];
    float start[2];
    float target[2];
    float velocity[2];
    float acceleration[2];
    float elapsed_fraction;
    int elapsed;
    int duration;
    int mode;
    float speed;
};

struct Interp3I {
    int value[3];
    int start[3];
    int target[3];
    int velocity[3];
    int acceleration[3];
    float elapsed_fraction;
    int elapsed;
    int duration;
    int mode;
    float speed;
};

struct Interp1I {
    int value;
    int start;
    int target;
    int velocity;
    int acceleration;
    float elapsed_fraction;
    int elapsed;
    int duration;
    int mode;
    float speed;
};

int Interp3F_Tick(Interp3F* state);
int Interp2F_Tick(Interp2F* state);
int Interp3I_Tick(Interp3I* state);
int Interp1I_Tick(Interp1I* state);

#endif // TH10_MATH_INTERPOLATORS_HPP
