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
    void* reserved;                  // +0x10
    SchedulerNode node;              // +0x14
    void* owner;                     // +0x20
};

SchedulerCallback* SchedulerCallback_Create(SchedulerFunction function);
int Scheduler_RegisterPrimary(
    SchedulerCallback* callback, int priority, void* device);
int Scheduler_RegisterSecondary(
    SchedulerCallback* callback, int priority, void* device);
