// Compiler-only ABI context. None of these anchors is exported as game code.
// Models of 0x4220E0/0x422150 establish the private EDX/EBX call agreement.
#include "../../src/game/pause/pause_create.cpp"
#include <string.h>

// 0x004220E0: initialise a freshly allocated recovery state in place.
//
// The factory at 0x00422360 calls this with the object in EDX and keeps the
// result from EAX, so the object pointer is the second __fastcall parameter.
extern "C" void* g_pause;

#include "th10/game/timer_state_00422360.hpp"

#pragma code_seg(".text$10construct")
void* __fastcall Pause_Construct_004220e0(int unused, Pause* state) {
    state->timer.flags &= ~1u;
    state->field_B0 = 0;
    state->field_24 = 0;
    state->field_F8 = 0;
    state->field_F4 = 1;
    // The two maxima are written through a raw pointer: retail materialises the
    // constant beside the stores and only schedules it there for an indirect
    // store, while a member store lets the optimiser sink it past the callee
    // save.
    unsigned* maximum = (unsigned*)((char*)state + 0x2C);
    *maximum = 999;
    maximum = (unsigned*)((char*)state + 0x104);
    *maximum = 999;
    state->field_188 = 0;
    state->field_FC = 0;
    state->field_1D0 = 0;
    state->field_1CC = 1;
    memset(state, 0, sizeof(*state));
    state->flags |= 2u;
    g_pause = state;
    return state;
}
#pragma code_seg()

#pragma code_seg(".text$20runtime")
#include "../../src/game/pause/pause_register_tasks.cpp"
#pragma code_seg()

#include "th10/game/scheduler.hpp"
#include "th10/platform/thread_sync.hpp"

#pragma code_seg(".text$50primary")
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

#pragma code_seg(".text$70secondary")
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

#pragma code_seg(".text$90context")
int __stdcall TimerFactoryCompilerContext() { return Pause_Create() != 0; }
#pragma code_seg()
