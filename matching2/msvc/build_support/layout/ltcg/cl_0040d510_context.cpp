// Compiler context only; never selected as recovered game code.
#include "../../../src/game/enemy/enemy_ctrl_suspend.cpp"
#pragma code_seg(".text$03context")
int __stdcall SetContext_0040d510(EnemyCtrl** items, int count) {
    while (count--) {
        EnemyCtrl_SuspendTasks(*items++);
    }
    return 0;
}
#pragma code_seg()
