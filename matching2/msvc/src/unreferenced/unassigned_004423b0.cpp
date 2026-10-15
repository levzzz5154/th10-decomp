// 0x004423B0..0x004423BB: out-of-line copy of "signed random value times scale".
//
// The generator state arrives in ECX, the scale on the stack: the body forwards
// ECX straight to Rng_NextFloatSigned and multiplies the result, so the wrapper
// is the __fastcall form of the same helper.
#include "th10/math/rng.hpp"

float __fastcall Rng_NextFloatSignedScaled(RngState* state, float scale) {
    return Rng_NextFloatSigned(state) * scale;
}
