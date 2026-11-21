// 0x00408750: PolarVector2::SetPolar
#include "th10/math/scaled_polar.hpp"

// 0x408750: x87 polar-vector setter.
struct PolarVector2 {
    float x, y;
    __attribute__((thiscall, noinline))
    PolarVector2* SetPolar(float angle, float radius);
};

PolarVector2* PolarVector2::SetPolar(float angle, float radius) {
    return SetScaledPolar(this, angle, radius, radius);
}
