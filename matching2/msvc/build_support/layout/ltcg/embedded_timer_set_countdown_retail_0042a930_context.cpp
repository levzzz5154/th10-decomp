// Compiler context only; never selected as recovered game code.
#include "../../../src/game/replay/embedded_timer_set_countdown_retail_0042a930.cpp"

#pragma code_seg(".text$03context")
int __stdcall EmbeddedTimerSetCountdownRetailCompilerContext(
    EmbeddedTimerState** timers, int* values, int count) {
    int total = 0;
    while (count--) {
        int value = *values++;
        (*timers++)->SetCountdown(value);
        total += value;
    }
    return total;
}
#pragma code_seg()
