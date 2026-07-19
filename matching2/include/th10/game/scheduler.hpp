// =============================================================================
// scheduler.hpp - Typed callback scheduler recovered from 0x00449AE0..0x00449F17
// =============================================================================
#pragma once

typedef int (__fastcall *SchedulerFunction)(void* owner);

struct SchedulerCallback;

struct SchedulerNode {
    SchedulerCallback* owner;       // +0x00
    SchedulerNode* next;            // +0x04
    SchedulerNode* previous;        // +0x08
};

struct SchedulerCallback {
    int priority;                    // +0x00
    unsigned int flags;              // +0x04
    SchedulerFunction function;      // +0x08
    SchedulerFunction onReplace;     // +0x0C
    // Optional callback invoked after the primary callback returns 7.
    SchedulerFunction onResultSeven; // +0x10
    SchedulerNode node;              // +0x14
    void* owner;                     // +0x20
};

SchedulerCallback* SchedulerCallback_Create(SchedulerFunction function);
int Scheduler_RegisterPrimary(
    SchedulerCallback* callback, int priority, void* device);
int Scheduler_RegisterSecondary(
    SchedulerCallback* callback, int priority, void* device);
void Scheduler_Remove(SchedulerCallback* callback, void* device);
SchedulerCallback* Scheduler_CreateAndRegister(
    SchedulerFunction function, int priority, void* device);
SchedulerCallback* Scheduler_CreateAndRegisterSecondary(
    SchedulerFunction function, void* owner, void* device);
int Scheduler_RunPrimary(void* device);
int Scheduler_RunSecondary(void* device);
int GameState_DispatchDummy(void* target, unsigned int state_flags,
                            int (*configure)(void*, const char*, int, int));
void GameState_UpdateFrameMaximum(int current_value, int* object_value,
                                  int* maximum_value);
void GameState_Unpause(unsigned int* state_flags, void* target,
                       int* animation_handle, int saved_frame,
                       int* current_frame,
                       int (*configure)(void*, const char*, int, int),
                       void (*remove_animation)(void*, int));
void GameState_DispatchAnimationSlot(void* state, int index, void* manager,
                                     void (*dispatch)(int, void*, int));
void GameState_DispatchAnimationSlotSecondary(void* state, int index,
                                              void* manager,
                                              void (*dispatch)(int, void*, int));
