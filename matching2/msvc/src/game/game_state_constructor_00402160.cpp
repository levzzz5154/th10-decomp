// 0x00402160: GameState constructor. The members construct themselves (the
// stage timers and both entity arrays); the body clears the whole state.
#include "th10/game/game_state.hpp"

#pragma code_seg(".text$01ctor")
GameState_00402230::GameState_00402230() {
    memset(this, 0, sizeof(*this));
    flags |= 2;
}
#pragma code_seg()
