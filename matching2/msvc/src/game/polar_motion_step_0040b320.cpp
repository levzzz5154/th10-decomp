// 0x0040B320: refresh a polar motion record's velocity or orbit, then move it.
//
// Retail keeps this out-of-line copy without a remaining caller; the record
// arrives in EAX and is handed to the advance at 0x0044C2A0 in ESI.
#include "th10/game/polar_motion.hpp"

#pragma code_seg(".text$01step")
void PolarMotion::Step() {
    Update();
    Advance();
}
#pragma code_seg()
