// Compiler context only; this caller is never selected as recovered game
// code. Retail's result screen hands the submenu dispatch one record at a
// time (state pointer on the stack, RET 4); this direct caller gives the
// native LTCG link the call edge from which the dispatch keeps the register
// homes retail chose, and compiles the scoped private-ABI dependency bodies
// (anchored at their retail addresses by the cluster layout) together with it.
#include "../../../src/game/pause/replay_submenu_update.cpp"

#pragma code_seg(".text$02i")
extern "C" __declspec(noinline) int __stdcall ReplaySubmenuContext_004236f0(
        SubmenuState** records, int count) {
    for (int index = 0; index < count; ++index)
        SubmenuUpdate(records[index]);
    return count;
}
#pragma code_seg()
