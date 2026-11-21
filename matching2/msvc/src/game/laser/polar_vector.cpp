// 0x0041F800: LaserPolarVector::SetPolar
#include "th10/math/scaled_polar.hpp"

// 0x41f800: x87 polar-vector setter.
struct LaserPolarVector {
    float x, y;
    __attribute__((thiscall, noinline))
    LaserPolarVector* SetPolar(float angle, float radius);
};

LaserPolarVector* LaserPolarVector::SetPolar(float angle, float radius) {
    return SetScaledPolar(this, angle, radius, radius);
}
