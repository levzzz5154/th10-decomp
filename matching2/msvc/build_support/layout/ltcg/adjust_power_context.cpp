#include "../../../src/game/bomb/player_adjustpower_00405b60.cpp"

#pragma code_seg(".text$03context")
// Compiler context only; never selected as recovered game code.
extern "C" PlayerPowerState data_00474c40;

int __stdcall AdjustPowerCompilerContext(int* deltas, int count) {
    while (count--)
        data_00474c40.AdjustPower(*deltas++);
    return 0;
}
#pragma code_seg()
