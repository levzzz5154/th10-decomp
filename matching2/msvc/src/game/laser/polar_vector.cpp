#include "th10/math/scaled_polar.hpp"

// 0x41f800: x87 polar-vector setter.
struct PathPolarVector {
    float x, y;
    __attribute__((thiscall, noinline))
    PathPolarVector* SetPathPolar(float angle, float radius);
};

PathPolarVector* PathPolarVector::SetPathPolar(float angle, float radius) {
    return SetScaledPolar(this, angle, radius, radius);
}
