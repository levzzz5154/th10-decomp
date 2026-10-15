#pragma once
#include <stddef.h>

// Callback context is passed in ECX by the original scheduler.
struct SchedulerTask;
typedef int (__fastcall *TaskRoutine)(void*);
struct TaskLink {
    SchedulerTask* task;
    TaskLink* next;
    TaskLink* previous;
    void InsertAfter(TaskLink* position) {
        if (position->next) {
            next = position->next;
            position->next->previous = this;
        }
        position->next = this;
        previous = position;
    }
    void Unlink() {
        if (next) next->previous = previous;
        if (previous) previous->next = next;
        next = 0;
        previous = 0;
    }
};
struct SchedulerTask {
    int priority;
    unsigned int heap_owned : 1;
    unsigned int reserved_flags : 31;
    TaskRoutine on_tick;
    TaskRoutine on_register;
    TaskRoutine on_remove;
    TaskLink link;
    void* context;
    ~SchedulerTask() {
        on_tick = 0;
        on_register = 0;
        on_remove = 0;
    }
};
struct FuncCtrl {
    SchedulerTask primary;
    SchedulerTask secondary;
};

extern "C" {
__declspec(noinline) int __stdcall FuncCtrl_RegisterPrimary(FuncCtrl*, SchedulerTask*, int priority);
__declspec(noinline) int __stdcall FuncCtrl_RegisterSecondary(FuncCtrl*, SchedulerTask*, int priority);
__declspec(noinline) void __stdcall FuncCtrl_RemoveLocked(FuncCtrl*, SchedulerTask*);
// 0x00449F60 is compiled inside its native-LTCG link with a private
// convention: the pass keeps the task in ECX and the scheduler in EDX (it gives
// the first declared parameter the second register) and loads ECX first at
// every call in that link, which is what retail's inlined lock-and-remove
// sequences do.
__declspec(noinline) void __stdcall FuncCtrl_Remove(FuncCtrl*, SchedulerTask*);
// The same entry as code compiled outside that link reaches it.
__declspec(noinline) void __fastcall FuncCtrl_RemoveTask(SchedulerTask*, FuncCtrl*);
}

typedef char SchedulerTask_size_must_be_36[sizeof(SchedulerTask) == 36 ? 1 : -1];
typedef char SchedulerTask_link_offset_must_be_20[offsetof(SchedulerTask, link) == 20 ? 1 : -1];
typedef char SchedulerTask_context_offset_must_be_32[offsetof(SchedulerTask, context) == 32 ? 1 : -1];
