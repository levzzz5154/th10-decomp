// 0x0040AF00..0x0040AF88: remove both scheduler tasks of the bullet manager's
// task pair and clear the global bullet-manager pointer at 0x004776FC.
// Compiled in the scheduler's native-LTCG cluster so that its calls to
// 0x00449F60 load the task register first.
#include "th10/game/scheduler_remove_locked.hpp"

extern "C" void* data_004776fc;

#pragma code_seg(".text$00b_mbulletrelease")
extern "C" __declspec(noinline) void __stdcall BulletManager_Release(SchedulerTaskPair* pair) {
    RemoveScheduledTaskPair(pair);
    data_004776fc = 0;
}
#pragma code_seg()
