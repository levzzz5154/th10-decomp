#include "../../src/core/screen/configure.cpp"
#include "runtime_selector_0043c970_scheduler_create.cpp"
#include "th10/game/scheduler.hpp"
#include "th10/platform/thread_sync.hpp"

#pragma code_seg(".text$10primary")
extern "C" __declspec(noinline) int __stdcall Scheduler_RegisterPrimary(
        Scheduler* scheduler, SchedulerTask* task, int priority) {
    int result = 0;
    if (task->on_register) {
        result = task->on_register(task->context);
        task->on_register = 0;
    }
    EnterCriticalSection(&g_thread_synchronization.critical_sections[0]);
    ++g_thread_synchronization.scheduler_lock_depth;
    task->priority = priority;
    TaskLink* position = &scheduler->primary.link;
    while (position->next && position->next->task->priority < priority)
        position = position->next;
    task->link.InsertAfter(position);
    LeaveCriticalSection(&g_thread_synchronization.critical_sections[0]);
    --g_thread_synchronization.scheduler_lock_depth;
    return result;
}

#pragma code_seg(".text$30secondary")
extern "C" __declspec(noinline) int __stdcall Scheduler_RegisterSecondary(
        Scheduler* scheduler, SchedulerTask* task, int priority) {
    int result = 0;
    if (task->on_register) {
        result = task->on_register(task->context);
        task->on_register = 0;
    }
    EnterCriticalSection(&g_thread_synchronization.critical_sections[0]);
    ++g_thread_synchronization.scheduler_lock_depth;
    task->priority = priority;
    TaskLink* position = &scheduler->secondary.link;
    while (position->next && position->next->task->priority < priority)
        position = position->next;
    task->link.InsertAfter(position);
    LeaveCriticalSection(&g_thread_synchronization.critical_sections[0]);
    --g_thread_synchronization.scheduler_lock_depth;
    return result;
}
#pragma code_seg()



#include "th10/render/screen_effect_controller.hpp"
#include <string.h>
void* __cdecl operator new(unsigned int);
#pragma code_seg(".text$01factory")
ScreenEffectController* __stdcall CreateScreenEffect_0043c8b0(
        int priority, int mode, int first, int second, int third, int fourth) {
    ScreenEffectController* owner =
        static_cast<ScreenEffectController*>(operator new(0x44));
    if (owner) {
        owner->timer.flags &= ~1u;
        memset(owner,0,sizeof(*owner));
        owner->flags |= 2u;
        owner->Configure(priority,mode,first,second,third,fourth);
    }
    return owner;
}
#pragma code_seg(".text$90context")
extern "C" int __stdcall RuntimeSelectorCompilerContext(int priority, int* modes, int count) {
    int created=0;
    for (int index=0;index<count;++index) {
        if (CreateScreenEffect_0043c8b0(priority,modes[index],index,count,index,priority))
            ++created;
    }
    return created;
}
#pragma code_seg()
