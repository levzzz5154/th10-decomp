// Compiler context only; never selected as recovered game code.
#include "../../src/game/score_set_mode_00412ed0.cpp"

#pragma code_seg(".text$03context")
int __stdcall ScoreModeCompilerContext(ScoreModeState** states, int count,
                                       int new_mode) {
    while (count--) {
        Score_SetMode(*states++, new_mode);
    }
    return 0;
}
#pragma code_seg()
