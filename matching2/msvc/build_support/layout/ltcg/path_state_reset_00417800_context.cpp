// Compiler context only; never selected as recovered game code.
#include "../../../src/game/front/enemy_ctrl_reset_timer.cpp"

#pragma code_seg(".text$03context")
int __stdcall PathStateReset00417800CompilerContext(
    EnemyCtrlTimerView** states, int count) {
    EnemyCtrlTimerView** cursor = states;
    while (count--) {
        EnemyCtrlTimerView* state = *cursor++;
        state->ResetTimer();
    }
    return 0;
}
#pragma code_seg()
