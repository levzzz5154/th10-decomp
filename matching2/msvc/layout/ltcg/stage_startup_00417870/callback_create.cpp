#include "callback_task.hpp"
void* __cdecl operator new(unsigned int size);
#pragma code_seg(".text$00449ed0_fn")
extern "C" __declspec(noinline) int* __stdcall SchedulerCallback_Create_00449ed0(int callback) {
    CallbackTask* task = new CallbackTask;
    task->on_register = 0;
    task->on_remove = 0;
    // Read the initialized flags before publishing the callback and owned bit.
    unsigned int final_flags = *(volatile unsigned int*)&task->flags | 1u;
    task->on_tick = (TaskRoutine)callback;
    task->flags = final_flags;
    return reinterpret_cast<int*>(task);
}


#pragma code_seg()
