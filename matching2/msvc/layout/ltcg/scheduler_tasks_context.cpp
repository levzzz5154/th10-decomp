// Compiler context only; this caller is not recovered application code.
#pragma code_seg(".text$90context")
#include "../../src/core/zunlib/scheduler_tasks.cpp"

#pragma code_seg(".text$90context")
void __stdcall SchedulerContext(Scheduler* scheduler, SchedulerTask** tasks, int count, int priority) {
    for (int index=0;index<count;++index) {
        SchedulerTask* task=tasks[index];
        Scheduler_RegisterPrimary(scheduler,task,priority);
        Scheduler_RegisterSecondary(scheduler,task,priority);
        Scheduler_RemoveLocked(scheduler,task);
    }
    void (__fastcall *volatile remove)(SchedulerTask*,Scheduler*)=&Scheduler_Remove;
    remove(tasks[0],scheduler);
}
#pragma code_seg()
