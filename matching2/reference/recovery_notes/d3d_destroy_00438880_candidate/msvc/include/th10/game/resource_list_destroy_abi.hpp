#pragma once
#include "th10/game/scheduler.hpp"
// Address-qualified adapter: pointer argument is volatile only within the callee.
// This preserves retail's per-iteration stack reload without requiring volatile
// temporary owner objects in callers.
struct ResourceList_DestroyABI_00449e50 {
    unsigned char reserved[0x18];
    TaskLink* first;
    __declspec(noinline) void Release(Scheduler* owner);
};
