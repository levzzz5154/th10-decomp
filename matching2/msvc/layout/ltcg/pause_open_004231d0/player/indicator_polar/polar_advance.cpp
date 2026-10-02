#include "th10/game/pause_result_open_004231d0/player/indicator_polar/indicator_contract.hpp"

// 0044C2A0: one motion receiver, plain RET. ESI is the private register
// selected by the complete real caller graph. SetPolar and floor retain
// their genuine public call boundaries.
#pragma code_seg(".text$0044c2a0_fn")
void PolarMotion::Advance() {
    PolarVec3 offset;
    if (!(flags & 1)) {
        position.x += velocity.x;
        position.y += velocity.y;
        position.z += velocity.z;
    } else {
        offset.SetPolar(angle, radius);
        offset.z = 0.0f;
        position = offset + velocity;
    }
    // Keep the floor result at its public double precision until the final
    // coordinate assignment, as the retail x87 FMUL/FSTP sequence does.
    position.x = (float)(floor((double)(position.x * data_00470b44))
        * data_00470b00);
    position.y = (float)(floor((double)(position.y * data_00470b44))
        * data_00470b00);
}
#pragma code_seg()
