#include "th10/math/vector2_polar.hpp"

#include <cmath>

// 0x0044C5D0 - Build a 2D vector from an angle and a radius: x is
// cos(angle) * radius and y is sin(angle) * radius, computed with the
// x87 fcos/fsin pair in retail.
void Vector2_FromAngle(float* out, float angle, float radius) {
    out[0] = cosf(angle) * radius;
    out[1] = sinf(angle) * radius;
}
