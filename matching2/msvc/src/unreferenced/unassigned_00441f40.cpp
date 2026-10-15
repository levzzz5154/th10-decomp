#include <math.h>

// Two stack floats are passed to the CRT's fmod intrinsic helper.
extern "C" float __stdcall fmod_wrapper_00441f40(float numerator, float denominator) {
    return fmodf(numerator, denominator);
}
