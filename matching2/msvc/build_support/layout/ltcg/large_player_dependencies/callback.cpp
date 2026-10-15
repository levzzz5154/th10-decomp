#include "th10/core/func_ctrl.hpp"
extern "C" void _ReadWriteBarrier();
#pragma intrinsic(_ReadWriteBarrier)
void* __cdecl operator new(unsigned int);
#pragma code_seg(".text$a19body")
extern "C" __declspec(noinline) SchedulerTask* __stdcall LargePlayerCallbackCreate(TaskRoutine routine) {
    SchedulerTask* task=(SchedulerTask*)::operator new(sizeof(SchedulerTask));
    if (task) {
        unsigned int old=*(unsigned int*)((char*)task+4);
        task->on_tick=0;task->on_register=0;task->on_remove=0;task->priority=0;
        _ReadWriteBarrier(); *(unsigned int*)((char*)task+4)=old&~1u;
        task->link.task=task;task->link.next=0;task->link.previous=0;
    } else { task=0; }
    task->on_register=0;task->on_remove=0;
    unsigned int flags=*(unsigned int*)((char*)task+4)|1u;
    task->on_tick=routine;*(unsigned int*)((char*)task+4)=flags;
    return task;
}
#pragma code_seg()
