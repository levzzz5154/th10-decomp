// Compiler context only; never selected as recovered game code.
#include "../../src/game/score_timer_leaves.cpp"

#pragma code_seg(".text$03context")
int __stdcall TimerOwner0042c5c0CompilerContext(
        GameStateTimer_0042c5c0** states, int* owners, int count) {
    int total = 0;
    while (count--) {
        int owner = *owners++;
        (*states++)->DisableTimerWithOwner(owner);
        total += owner;
    }
    return total;
}
#pragma code_seg()
