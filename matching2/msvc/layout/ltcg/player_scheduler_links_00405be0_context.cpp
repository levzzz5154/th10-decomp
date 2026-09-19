// Compiler context only; never selected as recovered game code.
#include "../../src/game/player_scheduler.cpp"

#pragma code_seg(".text$03context")
extern "C" __declspec(noinline) int __stdcall PlayerResetSchedulerLinksContext(
        Player_00405be0** players, int count) {
    while (count--) {
        (*players++)->ResetSchedulerLinks();
    }
    return 0;
}
#pragma code_seg()
