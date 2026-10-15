// 0x00402160: BackGround constructor. The members construct themselves (the
// stage timers and both entity arrays); the body clears the whole state.
#include "th10/game/background.hpp"

#pragma code_seg(".text$01ctor")
BackGround::BackGround() {
    memset(this, 0, sizeof(*this));
    flags |= 2;
}
#pragma code_seg()
