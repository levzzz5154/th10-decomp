// Compiler context only; never selected as recovered game code. It publishes
// the update callback the way the stage initializer at 0x00402230 does.
#include "../../../../src/game/background/anm_script_table_sweep.cpp"
#include "../../../../src/game/background/background_update.cpp"
#include "th10/core/func_ctrl.hpp"

#pragma code_seg(".text$03context")
SchedulerTask* __stdcall Game_UpdateCompilerContext(SchedulerTask* task, BackGround* stage) {
    task->on_tick = reinterpret_cast<TaskRoutine>(BackGround_OnUpdate);
    task->context = stage;
    return task;
}
#pragma code_seg()
