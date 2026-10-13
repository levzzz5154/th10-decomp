#include "th10/game/replay_submenu_004236f0/state.hpp"
// 0x00421F60 (28 bytes): snapshot the current frame value and update the
// largest frame value seen by the game state.
extern "C" int data_00474c40;
#pragma code_seg(".text$02d")
int __stdcall SubUpdateFrameMaximum_004236f0(GameStateFrameState* state) {
    state->frame_value = data_00474c44.score;
    if (data_00474c40 < state->frame_value)
        data_00474c40 = state->frame_value;
    return state->frame_value;
}
#pragma code_seg()
