// Compiler context only; never selected as recovered game code.
#include "../../src/game/enemy/enemy_manager_suspend.cpp"
#pragma code_seg(".text$03context")
int __stdcall SetContext_0040d510(EnemyManagerTasks** items, int count) {
    while (count--) {
        EnemyManager_SuspendTasks(*items++);
    }
    return 0;
}
#pragma code_seg()
