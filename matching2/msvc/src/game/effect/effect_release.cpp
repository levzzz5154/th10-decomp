// 0x0040AF00..0x0040AF88: remove both scheduler tasks of the effect manager's
// task pair and clear g_effect at 0x004776FC.
// Compiled in the scheduler's native-LTCG cluster so that its calls to
// 0x00449F60 load the task register first.
#include "th10/game/scheduler_remove_locked.hpp"

extern "C" void* g_effect;

#pragma code_seg(".text$00b_mbulletrelease")
extern "C" __declspec(noinline) void __stdcall Effect_Release(SchedulerTaskPair* pair) {
    RemoveScheduledTaskPair(pair);
    g_effect = 0;
}
#pragma code_seg()
