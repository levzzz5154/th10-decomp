// Compiler context only; never selected as recovered game code.
#include "../../src/game/player_set_scheduler_value_00405410.cpp"

#pragma code_seg(".text$03context")
int __stdcall PlayerSetSchedulerValueCompilerContext(PlayerSchedulerRecord** records, int* values, int count) {
    int total = 0;
    while (count--) {
        int value = *values++;
        (*records++)->SetSchedulerValue(value);
        total += value;
    }
    return total;
}
#pragma code_seg()
