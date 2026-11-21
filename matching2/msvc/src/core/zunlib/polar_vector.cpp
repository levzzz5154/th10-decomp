// 0x0044C5D0: ZunPolarVector::SetPolar
#include "th10/math/scaled_polar.hpp"

// 0x44c5d0: x87 polar-vector setter.
struct ZunPolarVector {
    float x, y;
    __attribute__((thiscall, noinline))
    ZunPolarVector* SetPolar(float angle, float radius);
};

ZunPolarVector* ZunPolarVector::SetPolar(float angle, float radius) {
    return SetScaledPolar(this, angle, radius, radius);
}
