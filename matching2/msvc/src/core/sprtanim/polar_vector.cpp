// 0x00441EF0: AnimationLeafPolarVector::SetAnimationPolar
#include "th10/math/scaled_polar.hpp"

// 0x441ef0: x87 polar-vector setter.
struct AnimationLeafPolarVector {
    float x, y;
    __attribute__((thiscall, noinline))
    AnimationLeafPolarVector* SetAnimationPolar(float angle, float radius);
};

AnimationLeafPolarVector* AnimationLeafPolarVector::SetAnimationPolar(float angle, float radius) {
    return SetScaledPolar(this, angle, radius, radius);
}
