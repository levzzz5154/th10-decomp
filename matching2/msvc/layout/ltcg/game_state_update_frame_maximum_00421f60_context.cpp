// Compiler context only; never selected as recovered game code.
#include "../../src/game/game_state_update_frame_maximum_00421f60.cpp"

extern "C" GameStateFrameState* data_004776f4;

#pragma code_seg(".text$03context")
int __stdcall GameStateFrameMaximumCompilerContext(int count) {
    int total = 0;
    while (count--)
        total += GameState_UpdateFrameMaximum(data_004776f4);
    return total;
}
#pragma code_seg()
