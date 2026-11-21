#include "../../../src/game/bomb/globals_adjust_rank.cpp"

#pragma code_seg(".text$03context")
// Compiler context only; never selected as recovered game code.
extern "C" DifficultyRankState g_globals;

int __stdcall AdjustPowerCompilerContext(int* deltas, int count) {
    while (count--)
        g_globals.AdjustRank(*deltas++);
    return 0;
}
#pragma code_seg()
