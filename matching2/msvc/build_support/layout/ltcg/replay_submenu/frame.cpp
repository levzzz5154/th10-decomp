#include "th10/game/replay_submenu/state.hpp"
// 0x00421F60 (28 bytes): snapshot the current frame value and update the
// largest frame value seen by the game state.
extern "C" int g_globals;
#pragma code_seg(".text$02d")
int __stdcall SubUpdateFrameMaximum(FrontScoreState* state) {
    state->displayed_score = g_globals_score.score;
    if (g_globals < state->displayed_score)
        g_globals = state->displayed_score;
    return state->displayed_score;
}
#pragma code_seg()
