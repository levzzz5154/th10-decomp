#pragma once
#include "th10/core/func_ctrl.hpp"

// Retail reloads this argument inside each locked iteration.
struct FuncCtrlTaskListOwner { FuncCtrl* volatile scheduler; };
struct FuncCtrlTaskList {
    unsigned char reserved[0x18];
    TaskLink* first;
    __declspec(noinline) void ReleaseTaskList(FuncCtrlTaskListOwner owner);
};
