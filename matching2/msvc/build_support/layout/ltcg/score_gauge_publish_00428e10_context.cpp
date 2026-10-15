// Compiler context only; never selected as recovered game code.
#include "../../../src/game/player/fun_00428e10_00428e10.cpp"

#pragma code_seg(".text$03context")
extern "C" __declspec(noinline) int __stdcall ScoreGaugeContext00428e10(
        Player** players, const FixedPoint** sources, int count) {
    int last = 0;
    while (count--) {
        last = (*players++)->SetFixedPosition(*sources++) != 0;
    }
    return last;
}
#pragma code_seg()
