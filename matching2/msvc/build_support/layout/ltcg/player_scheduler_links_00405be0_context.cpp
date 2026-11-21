// Compiler context only; never selected as recovered game code.
#include "../../../src/game/bomb/bullet_reset_timers.cpp"

#pragma code_seg(".text$03context")
extern "C" __declspec(noinline) int __stdcall PlayerResetSchedulerLinksContext(
        BulletTimerResetView** players, int count) {
    while (count--) {
        (*players++)->ResetTimers();
    }
    return 0;
}
#pragma code_seg()
