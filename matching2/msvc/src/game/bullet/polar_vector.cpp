// 0x00408750: ScoreGameplayPolarVector::SetScorePolar
#include "th10/math/scaled_polar.hpp"

// 0x408750: x87 polar-vector setter.
struct ScoreGameplayPolarVector {
    float x, y;
    __attribute__((thiscall, noinline))
    ScoreGameplayPolarVector* SetScorePolar(float angle, float radius);
};

ScoreGameplayPolarVector* ScoreGameplayPolarVector::SetScorePolar(float angle, float radius) {
    return SetScaledPolar(this, angle, radius, radius);
}
