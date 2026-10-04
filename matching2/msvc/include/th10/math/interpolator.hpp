#ifndef TH10_MATH_INTERPOLATOR_HPP
#define TH10_MATH_INTERPOLATOR_HPP

#include "th10/math/timer.hpp"

// 0x0044C350: the easing table shared by every interpolator.
__declspec(noinline) float __stdcall EvaluateCurve_0044c350(
    unsigned int mode, float numerator, float denominator);

// A value driven from a start to a target over a number of frames. Retail
// instantiates it for int (0x00441950), Vec2 (0x00441AD0), Vec3 (0x00404610)
// and a three-int colour (0x00441600).
template <class T>
struct Interpolator {
    T value;           // start value; the running value in modes 7 and 17
    T target;          // end value; the step in modes 7 and 17
    T control;         // Hermite start tangent
    T velocity;        // Hermite end tangent; the running step in mode 17
    FrameTimer timer;
    int duration;      // frames left to run, 0 once finished
    int mode;          // 7 add, 17 accelerate, 8 Hermite, else easing

    // Eased progress through the run, 0 to 1.
    float Rate() { return EvaluateCurve_0044c350(mode, timer.elapsed, (float)duration); }

    // Advance one frame and return the current value. Defined in
    // interpolator_step.hpp, which only the instantiating sources include.
    __declspec(noinline) T Step();
};

#endif
