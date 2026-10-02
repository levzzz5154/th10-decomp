// Unpromoted candidate for 0x00449ED0: 74 compiled bytes, one remaining
// constructor scheduling difference. See the 2026-10-02 recovery note.
#include "th10/game/scheduler.hpp"

void* __cdecl operator new(unsigned int size);

// The task constructor resets callbacks, clears heap ownership, and starts an
// unlinked list node. The callback context remains untouched until its owner
// publishes it after creation.
struct SchedulerCallbackTask_00449ed0 {
    int priority;                         // +0x00
    unsigned int heap_owned : 1;          // +0x04
    unsigned int reserved_flags : 31;
    TaskRoutine on_tick;                  // +0x08
    TaskRoutine on_register;              // +0x0C
    TaskRoutine on_remove;                // +0x10
    TaskLink link;                        // +0x14
    void* context;                        // +0x20

    SchedulerCallbackTask_00449ed0() {
        on_tick = 0;
        on_register = 0;
        on_remove = 0;
        heap_owned = priority = 0;
        link.task = reinterpret_cast<SchedulerTask*>(this);
        link.next = 0;
        link.previous = 0;
    }
};
typedef char SchedulerCallbackTaskSize_00449ed0[
    sizeof(SchedulerCallbackTask_00449ed0) == 0x24 ? 1 : -1];

extern "C" SchedulerTask* __stdcall SchedulerCallback_Create_00449ed0(
        TaskRoutine callback) {
    SchedulerCallbackTask_00449ed0* task = new SchedulerCallbackTask_00449ed0;
    // Retail executes these writes after either allocation branch.
    task->on_tick = callback;
    task->on_register = 0;
    task->on_remove = 0;
    task->heap_owned = 1;
    return reinterpret_cast<SchedulerTask*>(task);
}
