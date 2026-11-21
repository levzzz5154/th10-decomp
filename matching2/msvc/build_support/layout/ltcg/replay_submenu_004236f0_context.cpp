// Compiler context only; this caller is never selected as recovered game
// code. Retail's result screen hands the submenu dispatch one record at a
// time (state pointer on the stack, RET 4); this direct caller gives the
// native LTCG link the call edge from which the dispatch keeps the register
// homes retail chose, and compiles the scoped private-ABI dependency bodies
// (anchored at their retail addresses by the cluster layout) together with it.
#include "../../../src/game/pause/replay_submenu_update.cpp"

// The private-ABI dependency bodies, co-compiled into this cluster and
// anchored at their retail addresses.
#include "replay_submenu/find.cpp"
#include "replay_submenu/setstop.cpp"
#include "replay_submenu/child.cpp"
#include "replay_submenu/mark6.cpp"
#include "replay_submenu/stop3.cpp"
#include "replay_submenu/stop1.cpp"
#include "replay_submenu/nodeflag.cpp"
#include "replay_submenu/inputmode.cpp"
#include "replay_submenu/timer.cpp"
#include "replay_submenu/queue.cpp"
#include "replay_submenu/cursor.cpp"
#include "replay_submenu/frame.cpp"
#include "replay_submenu/timed.cpp"
#include "replay_submenu/destroy.cpp"
#include "replay_submenu/mask.cpp"

#pragma code_seg(".text$02i")
extern "C" __declspec(noinline) int __stdcall ReplaySubmenuContext_004236f0(
        SubmenuState** records, int count) {
    for (int index = 0; index < count; ++index)
        SubmenuUpdate(records[index]);
    return count;
}
#pragma code_seg()
