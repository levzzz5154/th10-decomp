// 0x00413270: EllipticPolarVector::SetEllipticPolar
#include "th10/math/scaled_polar.hpp"

// 0x00413270: independent horizontal and vertical scales; callee pops 12 bytes.
struct EllipticPolarVector {
    float x, y;
    __attribute__((thiscall, noinline))
    EllipticPolarVector* SetEllipticPolar(float angle, float horizontal, float vertical);
};

EllipticPolarVector* EllipticPolarVector::SetEllipticPolar(float angle, float horizontal, float vertical) {
    return SetScaledPolar(this, angle, horizontal, vertical);
}
