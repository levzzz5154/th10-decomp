// Compiler-only ABI context. None of these anchors is exported as game code.
// Models of 0x4220E0/0x422150 establish the private EDX/EBX call agreement.
#include "../../src/game/recovery_create_timer_state_00422360.cpp"
#include <string.h>

// 0x004220E0: initialise a freshly allocated recovery state in place.
//
// The factory at 0x00422360 calls this with the object in EDX and keeps the
// result from EAX, so the object pointer is the second __fastcall parameter.
extern "C" void* data_00477830;

struct TimerState_00422360 {
    unsigned flags;              // +0x000
    char pad_004[0x1C];
    unsigned field_20;           // +0x020
    int field_24;                // +0x024
    char pad_028[0x04];
    int field_2C;                // +0x02C
    char pad_030[0x80];
    int field_B0;                // +0x0B0
    char pad_0B4[0x40];
    int field_F4;                // +0x0F4
    int field_F8;                // +0x0F8
    int field_FC;                // +0x0FC
    char pad_100[0x04];
    int field_104;               // +0x104
    char pad_108[0x80];
    int field_188;               // +0x188
    char pad_18C[0x40];
    int field_1CC;               // +0x1CC
    int field_1D0;               // +0x1D0
    char pad_1D4[0xF4];
};

#pragma code_seg(".text$10construct")
void* __fastcall InitializeTimerState_004220e0(int unused, TimerState_00422360* state) {
    state->field_20 &= ~1u;
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
    data_00477830 = state;
    return state;
}
#pragma code_seg()

#include "th10/game/scheduler.hpp"
extern "C" unsigned char data_00491be4;
extern "C" int* __stdcall SchedulerCallback_Create_00449ed0(int);
struct TimerState_00422360;
#pragma code_seg(".text$20runtime")
__declspec(noinline) int __cdecl RegisterTimerState_00422150(TimerState_00422360* owner) {
    unsigned char* bytes = (unsigned char*)owner;
    SchedulerTask* first = (SchedulerTask*)SchedulerCallback_Create_00449ed0(0x422a90);
    unsigned int* first_flag_word =
        (unsigned int*)((unsigned char*)first + 4);
    unsigned int first_flags = *first_flag_word;
    Scheduler* scheduler = *(Scheduler**)&data_00491be4;
    first_flags &= ~2u;
    *first_flag_word = first_flags;
    first->context = owner;
    Scheduler_RegisterPrimary(scheduler, first, 9);
    *(SchedulerTask**)(bytes + 8) = first;
    void* created = (void*)SchedulerCallback_Create_00449ed0(0x422aa0);
    SchedulerTask* second = (SchedulerTask*)created;
    unsigned int* second_flag_word =
        (unsigned int*)((unsigned char*)second + 4);
    unsigned int second_flags = *second_flag_word;
    scheduler = *(Scheduler**)&data_00491be4;
    second->context = owner;
    second_flags &= ~2u;
    *second_flag_word = second_flags;
    Scheduler_RegisterSecondary(scheduler, second, 0x2e);
    *(SchedulerTask**)(bytes + 0xc) = second;
    unsigned int flags = *(unsigned int*)(bytes + 0x20);
    if (!(flags & 1)) {
        *(int*)(bytes + 0x14) = 0;
        *(int*)(bytes + 0x10) = -999999;
        *(int*)(bytes + 0x18) = 0;
        *(unsigned int*)(bytes + 0x1c) = 0x476f78;
        *(unsigned int*)(bytes + 0x20) = flags | 1;
    }
    *(int*)(bytes + 0x14) = 0;
    *(int*)(bytes + 0x18) = 0;
    *(int*)(bytes + 0x10) = -1;
    return 0;
}
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
int __stdcall TimerFactoryCompilerContext() { return CreateTimerState_00422360() != 0; }
#pragma code_seg()
