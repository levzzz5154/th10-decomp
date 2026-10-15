// 0x0044C2A0: move a polar motion record by its velocity, or place it on its
// orbit around the velocity, and snap the result to hundredths.
//
// The record arrives in ESI. Both paths end with their own snap and return;
// the compiler merges the two tails.
#include "th10/game/polar_motion.hpp"

#pragma code_seg(".text$0044c2a0_fn")
void PolarMotion::Advance() {
    PolarVec3 offset;
    if ((flags & 1) == 0) {
        position += velocity;
        position.SnapToHundredths();
        return;
    }
    offset.SetPolar(angle, radius);
    offset.z = 0.0f;
    position = offset + velocity;
    position.SnapToHundredths();
}
#pragma code_seg()
