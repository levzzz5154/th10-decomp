// Compiler context only; never selected as recovered game code.
#include "../../../src/game/front/path_state_reset_00417800.cpp"

#pragma code_seg(".text$03context")
int __stdcall PathStateReset00417800CompilerContext(
    PathState** states, int count) {
    PathState** cursor = states;
    while (count--) {
        PathState* state = *cursor++;
        state->Reset();
    }
    return 0;
}
#pragma code_seg()
