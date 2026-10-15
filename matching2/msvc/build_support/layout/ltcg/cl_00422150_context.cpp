// Compiler context only; never selected as recovered game code.
#pragma code_seg(".text$00fn")
#include "../../../src/game/pause/pause_register_tasks.cpp"
#pragma code_seg()
#include "scheduler_register_anchors.cpp"

#pragma code_seg(".text$30context")
int __stdcall PauseContext_00422150(Pause** states, int count) {
    int result = 0;
    while (count--)
        result += Pause_RegisterTasks(*states++);
    return result;
}
#pragma code_seg()
