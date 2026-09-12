// Compiler context only; never selected as recovered game code.
#include "../../src/game/path_state_reset_00417800.cpp"

#pragma code_seg(".text$03context")
int __stdcall PathStateReset00417800CompilerContext(
    PathState_00417800** states, int count) {
    PathState_00417800** cursor = states;
    while (count--) {
        PathState_00417800* state = *cursor++;
        state->Reset();
    }
    return 0;
}
#pragma code_seg()
