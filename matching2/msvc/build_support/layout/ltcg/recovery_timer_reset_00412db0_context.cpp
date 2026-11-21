// Compiler context only; never selected as recovered game code.
#include "../../../src/game/enemy/enemy_timer_reset.cpp"

#pragma code_seg(".text$03context")
int __stdcall RecoveryTimerResetCompilerContext(
    EnemyTimerView** timers, int count) {
    EnemyTimerView** cursor = timers;
    while (count--) {
        EnemyTimerView* timer = *cursor++;
        timer->Reset();
        timer->Reset();
    }
    return 0;
}
#pragma code_seg()
