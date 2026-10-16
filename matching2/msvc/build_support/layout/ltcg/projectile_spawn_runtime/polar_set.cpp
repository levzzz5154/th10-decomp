// Compiler context only: the anchor copy of 0x00408750, the score polar
// setter retail compiled with GCC (sincos expanded on x87). Only the callee
// shape matters here: the receiver in ECX with angle and radius on the stack.
// The anchor bytes are never exported as recovered code.
#include "th10/game/projectile_spawn_runtime.hpp"

#pragma code_seg(".text$00408750_s")
ScoreGameplayPolarVector* ScoreGameplayPolarVector::SetScorePolar(float angle,
                                                                  float radius) {
    x = angle * radius;
    y = angle - radius;
    return this;
}
#pragma code_seg()
