#include "th10/math/vector.hpp"

extern "C" double __cdecl cos(double value);
extern "C" double __cdecl sin(double value);

// 0x0041F800 - Convert a polar direction and length to Cartesian coordinates.
void Vector2::SetPolar(float angle, float length) {
    float cosine = (float)cos(angle);
    float sine = (float)sin(angle);
    x = cosine * length;
    y = sine * length;
}
