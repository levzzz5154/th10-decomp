// 0x00405620..0x004056A8: Bomb_Release - remove both of the bomb's scheduler
// tasks and clear g_bomb (0x004776EC).
// Compiled in the scheduler's native-LTCG
#include "th10/game/scheduler_remove_locked.hpp"

extern "C" void* g_bomb;

#pragma code_seg(".text$00_wmpairreset")
extern "C" __declspec(noinline) void __stdcall Bomb_Release(SchedulerTaskPair* pair) {
    RemoveScheduledTaskPair(pair);
    g_bomb = 0;
}
#pragma code_seg()
