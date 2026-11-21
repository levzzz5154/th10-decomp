#include "th10/math/scaled_polar.hpp"

// 0x4501b0: x87 polar-vector setter.
struct EclPolarVector {
    float x, y;
    __attribute__((thiscall, noinline))
    EclPolarVector* SetPolar(float angle, float radius);
};

EclPolarVector* EclPolarVector::SetPolar(float angle, float radius) {
    return SetScaledPolar(this, angle, radius, radius);
}
