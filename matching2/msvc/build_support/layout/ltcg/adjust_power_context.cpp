#include "../../../src/game/bomb/player_adjustpower_00405b60.cpp"

#pragma code_seg(".text$03context")
// Compiler context only; never selected as recovered game code.
extern "C" PlayerPowerState g_globals;

int __stdcall AdjustPowerCompilerContext(int* deltas, int count) {
    while (count--)
        g_globals.AdjustPower(*deltas++);
    return 0;
}
#pragma code_seg()
