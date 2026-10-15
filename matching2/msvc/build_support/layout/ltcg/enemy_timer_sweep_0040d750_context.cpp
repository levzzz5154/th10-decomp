// Compiler context only; never selected as recovered game code. It publishes
// the sweep callback the way the manager initializer at 0x0040D280 does.
#include "../../../src/game/enemy/enemy_ctrl_update.cpp"
#include "th10/core/func_ctrl.hpp"

#pragma code_seg(".text$03context")
SchedulerTask* __stdcall EnemyTimerSweepCompilerContext(SchedulerTask* task, EnemyCtrlSweepView* manager) {
    task->on_tick = reinterpret_cast<TaskRoutine>(EnemyCtrl_OnUpdate);
    task->context = manager;
    return task;
}
#pragma code_seg()
