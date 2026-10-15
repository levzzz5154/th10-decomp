// Compiler context only; never selected as recovered game code.
#include "../../src/game/spttest/spt_test_register_tasks.cpp"
#include "scheduler_register_anchors.cpp"

struct SptTestState;
extern "C" SptTestState *__cdecl asm_FUN_0042bf30_0042bf30();

#pragma code_seg(".text$30context")
int __stdcall EffectPoolContext_0042bbd0(SptTestTaskView** pools, int count) {
    int result = 0;
    while (count--)
        result += (*pools++)->InstallTasks();
    result += asm_FUN_0042bf30_0042bf30() != 0;
    return result;
}
#pragma code_seg()
