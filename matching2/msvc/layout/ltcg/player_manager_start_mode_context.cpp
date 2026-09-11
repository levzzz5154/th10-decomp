// Compiler context only; never selected as recovered game code.
#include "../../src/game/player_manager_start_mode_004045b0.cpp"

#pragma code_seg(".text$03context")
int __stdcall PlayerManagerStartModeCompilerContext(PlayerManagerState** states, int count) {
    PlayerManagerState** cursor = states;
    while (count--) {
        PlayerManagerState* state = *cursor++;
        state->StartMode();
        state->StartMode();
    }
    return 0;
}
#pragma code_seg()
