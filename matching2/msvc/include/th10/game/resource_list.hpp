#pragma once
#include "th10/core/func_ctrl.hpp"

// Retail reloads this argument inside each locked iteration.
struct ResourceListOwner { FuncCtrl* volatile scheduler; };
struct ResourceList {
    unsigned char reserved[0x18];
    TaskLink* first;
    __declspec(noinline) void Release(ResourceListOwner owner);
};
