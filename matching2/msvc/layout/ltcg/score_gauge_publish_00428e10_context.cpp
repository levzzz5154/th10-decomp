// Compiler context only; never selected as recovered game code.
#include "../../src/game/fun_00428e10_00428e10.cpp"

#pragma code_seg(".text$03context")
extern "C" __declspec(noinline) int __stdcall ScoreGaugeContext00428e10(
        ScoreState_00428e10** states, const ScoreCounters_00428e10** sources, int count) {
    int last = 0;
    while (count--) {
        last = (*states++)->SetBossGauge(*sources++) != 0;
    }
    return last;
}
#pragma code_seg()
