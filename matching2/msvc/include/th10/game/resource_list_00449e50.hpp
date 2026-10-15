#pragma once
#include "th10/core/func_ctrl.hpp"

// Retail reloads this argument inside each locked iteration.
struct ResourceListOwner_00449e50 { FuncCtrl* volatile scheduler; };
struct ResourceList_00449e50 {
    unsigned char reserved[0x18];
    TaskLink* first;
    __declspec(noinline) void Release(ResourceListOwner_00449e50 owner);
};
