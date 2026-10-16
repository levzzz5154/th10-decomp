// Compiler context only; never selected as recovered game code.
#include "../../../src/game/enemy/score_set_mode.cpp"

#pragma code_seg(".text$03context")
int __stdcall ScoreModeCompilerContext(ScoreModeState** states, int count,
                                       int new_mode) {
    while (count--) {
        Score_SetMode(*states++, new_mode);
    }
    return 0;
}
#pragma code_seg()
