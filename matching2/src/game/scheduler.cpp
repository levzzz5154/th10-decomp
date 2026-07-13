// =============================================================================
// scheduler.cpp - Callback construction and priority-list insertion
// Functions: 0x00449ED0 (Create), 0x00449AE0 (primary list),
//            0x00449B70 (secondary list)
// =============================================================================
#include "th10/game/scheduler.hpp"

extern "C" void* operator_new(unsigned int size);
extern "C" void __stdcall EnterCriticalSection(void* criticalSection);
extern "C" void __stdcall LeaveCriticalSection(void* criticalSection);
extern unsigned int DAT_00492274;
extern unsigned char DAT_0049231c;

SchedulerCallback* SchedulerCallback_Create(SchedulerFunction function) {
    SchedulerCallback* callback =
        (SchedulerCallback*)operator_new(sizeof(SchedulerCallback));
    if (callback == 0) {
        return 0;
    }

    callback->priority = 0;
    callback->flags &= ~1u;
    callback->function = function;
    callback->onReplace = 0;
    callback->reserved = 0;
    callback->node.owner = callback;
    callback->node.next = 0;
    callback->node.previous = 0;
    callback->owner = 0;
    callback->flags |= 1;
    return callback;
}

static int Scheduler_Register(
    SchedulerCallback* callback, int priority, void* device,
    unsigned int listOffset) {
    int replaceResult = 0;
    if (callback->onReplace != 0) {
        replaceResult = callback->onReplace(callback->owner);
        callback->onReplace = 0;
    }

    EnterCriticalSection(&DAT_00492274);
    ++DAT_0049231c;

    callback->priority = priority;
    SchedulerNode* cursor = (SchedulerNode*)((unsigned char*)device + listOffset);
    while (cursor->next != 0 && cursor->next->owner->priority < priority) {
        cursor = cursor->next;
    }

    callback->node.next = cursor->next;
    if (cursor->next != 0) {
        cursor->next->previous = &callback->node;
    }
    cursor->next = &callback->node;
    callback->node.previous = cursor;

    LeaveCriticalSection(&DAT_00492274);
    --DAT_0049231c;
    return replaceResult;
}

int Scheduler_RegisterPrimary(
    SchedulerCallback* callback, int priority, void* device) {
    return Scheduler_Register(callback, priority, device, 0x14);
}

int Scheduler_RegisterSecondary(
    SchedulerCallback* callback, int priority, void* device) {
    return Scheduler_Register(callback, priority, device, 0x38);
}
