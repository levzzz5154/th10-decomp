#pragma once
#include "th10/core/func_ctrl.hpp"
// The retail list prefix has three genuine pending-resource words at +8/+C/+10.
// Native Release reads its stack owner on each locked iteration; volatility is
// confined to that callee read, so callers need no volatile aggregate spill.
struct ResourceList_DestroyABI_00449e50 {
    unsigned int reserved_000[2];
    unsigned int pending[3];
    unsigned int reserved_014;
    TaskLink* first;
    __declspec(noinline) void Release(FuncCtrl* owner);
};
