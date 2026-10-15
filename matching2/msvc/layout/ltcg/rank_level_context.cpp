// Compiler context only; never selected as recovered game code.
#include "../../src/game/front/rank_level.cpp"

#pragma code_seg(".text$03context")
int __stdcall RankLevelCompilerContext(RankState** states, int count) {
    RankState** cursor = states;
    while (count--) {
        RankState* state = *cursor++;
        state->AdvanceLevel();
        state->AdvanceLevel();
    }
    return 0;
}
#pragma code_seg()
