// Compiler context only; never selected as recovered game code. It publishes
// the sweep callback the way the manager initializer at 0x0040D280 does.
#include "../../src/game/enemy/enemy_timer_sweep_retail_0040d750.cpp"
#include "th10/game/scheduler.hpp"

#pragma code_seg(".text$03context")
SchedulerTask* __stdcall EnemyTimerSweepCompilerContext(SchedulerTask* task, EnemyTimerSweepManager_0040d750* manager) {
    task->on_tick = reinterpret_cast<TaskRoutine>(EnemyTimerSweep_Task_0040d810);
    task->context = manager;
    return task;
}
#pragma code_seg()
