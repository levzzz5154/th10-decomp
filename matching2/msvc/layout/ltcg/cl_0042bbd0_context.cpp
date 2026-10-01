// Compiler context only; never selected as recovered game code.
#include "../../src/unidentified/effect_pool_install_tasks_0042bbd0.cpp"
#include "scheduler_register_anchors.cpp"

struct EffectPoolState;
extern "C" EffectPoolState *__cdecl asm_FUN_0042bf30_0042bf30();

#pragma code_seg(".text$30context")
int __stdcall EffectPoolContext_0042bbd0(EffectPool_0042bbd0** pools, int count) {
    int result = 0;
    while (count--)
        result += (*pools++)->InstallTasks();
    result += asm_FUN_0042bf30_0042bf30() != 0;
    return result;
}
#pragma code_seg()
