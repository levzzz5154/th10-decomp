// 0x004458B0: AnimationPolarVector::SetAnimationPolar
#include "th10/math/scaled_polar.hpp"

// 0x4458b0: x87 polar-vector setter.
struct AnimationPolarVector {
    float x, y;
    __attribute__((thiscall, noinline))
    AnimationPolarVector* SetAnimationPolar(float angle, float radius);
};

AnimationPolarVector* AnimationPolarVector::SetAnimationPolar(float angle, float radius) {
    return SetScaledPolar(this, angle, radius, radius);
}
