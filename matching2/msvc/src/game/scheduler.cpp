#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00420C00: recovered in src/game/music_requests_00420a90.cpp.

// 0x00421F60: recovered in src/game/game_state_update_frame_maximum_00421f60.cpp.

// 0x00422C30: recovered in src/game/game_state_unpause_00422c30.cpp.

// 0x0042C730: maintained in src/game/game_state_dispatch_animation_slot_0042c730.cpp.

// 0x0042C750: maintained in src/game/game_state_dispatch_animation_slot_secondary_0042c750.cpp.


#include "th10/game/scheduler.hpp"
#include "th10/platform/thread_sync.hpp"

struct SchedulerTaskRaw_00449c00 {
    int priority;
    unsigned int flags;
    TaskRoutine on_tick;
    TaskRoutine on_register;
    TaskRoutine on_remove;
    TaskLink link;
    void* context;
};

static SchedulerTaskRaw_00449c00* raw_task_00449c00(TaskLink* link) {
    return (SchedulerTaskRaw_00449c00*)link->task;
}

// 0x00449C00..0x00449D33: primary task pass and compiler switch table.
extern "C" __declspec(noinline) int __stdcall Scheduler_RunPrimary_00449c00(
        Scheduler* scheduler) {
    EnterCriticalSection(&g_thread_synchronization.critical_sections[0]);
    ++g_thread_synchronization.scheduler_lock_depth;
restart_primary:
    int processed = 0;
    TaskLink* node = scheduler->primary.link.next;
    while (node) {
        TaskLink* next = node->next;
        SchedulerTaskRaw_00449c00* task = raw_task_00449c00(node);
        if (task->on_tick) {
            if (task->flags & 2) {
repeat_primary:
                LeaveCriticalSection(&g_thread_synchronization.critical_sections[0]);
                --g_thread_synchronization.scheduler_lock_depth;
                int result = task->on_tick(task->context);
                EnterCriticalSection(&g_thread_synchronization.critical_sections[0]);
                ++g_thread_synchronization.scheduler_lock_depth;
                switch (result) {
                case 0:
                    Scheduler_RemoveTask((SchedulerTask*)task, scheduler);
                    break;
                case 1:
                    break;
                case 2:
                    if (task->flags & 2) goto repeat_primary;
                    break;
                case 4:
                    processed = 0;
                    goto done_primary;
                case 3:
                    processed = 1;
                    goto done_primary;
                case 5:
                    processed = -1;
                    goto done_primary;
                case 6:
                    goto restart_primary;
                case 7:
                    if (task->on_remove) task->on_remove(task->context);
                    break;
                }
            }
            ++processed;
        }
        node = next;
    }
done_primary:
    LeaveCriticalSection(&g_thread_synchronization.critical_sections[0]);
    --g_thread_synchronization.scheduler_lock_depth;
    return processed;
}

// 0x00449D40..0x00449E4B: Scheduler_RunSecondary and compiler-local switch table
extern "C" __declspec(noinline) int __stdcall Scheduler_RunSecondary_00449d40(
        Scheduler* scheduler) {
    EnterCriticalSection(&g_thread_synchronization.critical_sections[0]);
    ++g_thread_synchronization.scheduler_lock_depth;
    int processed = 0;
    TaskLink* node = scheduler->secondary.link.next;
    while (node) {
        TaskLink* next = node->next;
        SchedulerTaskRaw_00449c00* task = raw_task_00449c00(node);
        if (task->on_tick) {
repeat_secondary:
            if (task->flags & 2) {
                LeaveCriticalSection(&g_thread_synchronization.critical_sections[0]);
                --g_thread_synchronization.scheduler_lock_depth;
                int result = task->on_tick(task->context);
                EnterCriticalSection(&g_thread_synchronization.critical_sections[0]);
                ++g_thread_synchronization.scheduler_lock_depth;
                switch (result) {
                case 0:
                    Scheduler_RemoveTask((SchedulerTask*)task, scheduler);
                    break;
                case 1:
                    break;
                case 2:
                    if (task->flags & 2) goto repeat_secondary;
                    break;
                case 4:
                    processed = 0;
                    goto done_secondary;
                case 3:
                    processed = 1;
                    goto done_secondary;
                case 5:
                    processed = -1;
                    goto done_secondary;
                }
            }
            ++processed;
        }
        node = next;
    }
done_secondary:
    LeaveCriticalSection(&g_thread_synchronization.critical_sections[0]);
    --g_thread_synchronization.scheduler_lock_depth;
    return processed;
}

// 0x00449ED0..0x00449F19: ?SchedulerCallback_Create@@
// The retail allocator is the project's recovered global operator new.
void* __cdecl operator new(unsigned int size);

extern "C" int* __stdcall SchedulerCallback_Create_00449ed0(
    int callback) {
    int* result;
    int final_flags;
    result = (int*)
        ::operator new(0x24);
    if (result) {
        __asm {
            mov edx, dword ptr [eax+4]
        }
        *(volatile int*)&result[2] = 0;
        *(volatile int*)&result[3] = 0;
        *(volatile int*)&result[4] = 0;
        *(volatile int*)&result[0] = 0;
        __asm {
            and edx, 0FFFFFFFEh
            mov dword ptr [eax+4], edx
        }
        result[5] = (int)result;
        result[6] = 0;
        result[7] = 0;
    } else {
        result = 0;
    }
    result[3] = 0;
    result[4] = 0;
    final_flags = *(volatile int*)&result[1] | 1;
    result[2] = callback;
    result[1] = final_flags;
    return result;
}

// 0x0044A000: recovered in src/game/scheduler_create_and_register_0044a000.cpp.

// 0x0044A030: recovered in src/game/scheduler_create_and_register_secondary_0044a030.cpp.
