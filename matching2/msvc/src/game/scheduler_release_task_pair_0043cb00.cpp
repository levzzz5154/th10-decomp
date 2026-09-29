// 0x0043CB00..0x0043CB7E: remove both scheduler tasks of a task pair, each
// under the scheduler lock.  Compiled in the scheduler's native-LTCG cluster so
// that its calls to 0x00449F60 load the task register first, as retail does.
#include "th10/game/scheduler_remove_locked.hpp"

#pragma code_seg(".text$00hcpairrelease")
extern "C" __declspec(noinline) void __stdcall Recovery_ReleaseRawPair(SchedulerTaskPair* pair) {
    RemoveScheduledTaskPair(pair);
}
#pragma code_seg()
