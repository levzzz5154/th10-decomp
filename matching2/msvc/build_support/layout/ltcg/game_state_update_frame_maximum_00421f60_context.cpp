// Compiler context only; never selected as recovered game code.
#include "../../../src/game/mother/game_state_update_frame_maximum.cpp"

extern "C" GameStateFrameState* g_card;

#pragma code_seg(".text$03context")
int __stdcall GameStateFrameMaximumCompilerContext(int count) {
    int total = 0;
    while (count--)
        total += GameState_UpdateFrameMaximum(g_card);
    return total;
}
#pragma code_seg()
