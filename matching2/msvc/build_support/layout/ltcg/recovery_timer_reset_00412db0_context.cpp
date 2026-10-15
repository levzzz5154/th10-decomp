// Compiler context only; never selected as recovered game code.
#include "../../../src/game/enemy/recovery_timer_reset_00412db0.cpp"

#pragma code_seg(".text$03context")
int __stdcall RecoveryTimerResetCompilerContext(
    RecoveryTimer_00412db0** timers, int count) {
    RecoveryTimer_00412db0** cursor = timers;
    while (count--) {
        RecoveryTimer_00412db0* timer = *cursor++;
        timer->Reset();
        timer->Reset();
    }
    return 0;
}
#pragma code_seg()
