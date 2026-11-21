#include "th10/math/scaled_polar.hpp"

// 0x44c5d0: x87 polar-vector setter.
struct RecoveryPolarVector {
    float x, y;
    __attribute__((thiscall, noinline))
    RecoveryPolarVector* SetPolar(float angle, float radius);
};

RecoveryPolarVector* RecoveryPolarVector::SetPolar(float angle, float radius) {
    return SetScaledPolar(this, angle, radius, radius);
}
