// Compiler context only; never selected as recovered game code.
#pragma code_seg(".text$00fn")
#include "../../src/game/timer_state_register_tasks_00422150.cpp"
#pragma code_seg()
#include "scheduler_register_anchors.cpp"

#pragma code_seg(".text$30context")
int __stdcall TimerStateContext_00422150(TimerState_00422360** states, int count) {
    int result = 0;
    while (count--)
        result += RegisterTimerState_00422150(*states++);
    return result;
}
#pragma code_seg()
