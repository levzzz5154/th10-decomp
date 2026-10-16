// Compiler context only; never selected as recovered game code.
#include "../../../src/game/enemy/recovery_timer_reset.cpp"

#pragma code_seg(".text$03context")
int __stdcall RecoveryTimerResetCompilerContext(
    RecoveryTimer3** timers, int count) {
    RecoveryTimer3** cursor = timers;
    while (count--) {
        RecoveryTimer3* timer = *cursor++;
        timer->Reset();
        timer->Reset();
    }
    return 0;
}
#pragma code_seg()
