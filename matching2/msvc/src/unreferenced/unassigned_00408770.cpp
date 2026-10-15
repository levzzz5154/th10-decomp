// 0x00408770: scale the next random float by a factor.
#include "th10/math/rng.hpp"

struct RngScaler_00408770 {
    __declspec(noinline) float Scale(float factor) const;
};

float RngScaler_00408770::Scale(float factor) const {
    return Rng_NextFloat((RngState*)this) * factor;
}
