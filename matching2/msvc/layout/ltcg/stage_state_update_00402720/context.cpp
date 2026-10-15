// Compiler context only; never selected as recovered game code. It publishes
// the update callback the way the stage initializer at 0x00402230 does.
#include "../../../src/game/background/anm_script_table_sweep.cpp"
#include "../../../src/game/background/stage_state_update_00402720.cpp"
#include "th10/game/scheduler.hpp"

#pragma code_seg(".text$03context")
SchedulerTask* __stdcall StageUpdateCompilerContext(SchedulerTask* task, StageState_00402720* stage) {
    task->on_tick = reinterpret_cast<TaskRoutine>(StageState_UpdateTask_00403050);
    task->context = stage;
    return task;
}
#pragma code_seg()
