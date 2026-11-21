// Compiler context only; never selected as recovered game code.
#include "../../../src/core/zunlib/scheduler_task_destruct.cpp"

#pragma code_seg(".text$03context")
void __stdcall D3DResourceListClearCompilerContext(SchedulerTask** items, int count) {
    while (count--)
        (*items++)->ClearPending();
}
#pragma code_seg()
