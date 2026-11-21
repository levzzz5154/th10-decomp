// Compiler context only; never selected as recovered game code.
#include "../../../src/game/enemy/trajectory_interp_restart.cpp"

#pragma code_seg(".text$03context")
int __stdcall RecoveryTimerResetCompilerContext(
    TrajectoryInterpView** timers, int count) {
    TrajectoryInterpView** cursor = timers;
    while (count--) {
        TrajectoryInterpView* timer = *cursor++;
        timer->Restart();
        timer->Restart();
    }
    return 0;
}
#pragma code_seg()
