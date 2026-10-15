// Compiler context only; never selected as recovered game code.
#include "../../src/game/background/background_start_mode.cpp"

#pragma code_seg(".text$03context")
int __stdcall PlayerManagerStartModeCompilerContext(BackGround** states, int count) {
    BackGround** cursor = states;
    while (count--) {
        BackGround* state = *cursor++;
        state->StartMode();
        state->StartMode();
    }
    return 0;
}
#pragma code_seg()
