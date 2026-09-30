// Compiler context only; never selected as recovered game code.
#include "../../src/unidentified/effect_pool_install_tasks_0042bbd0.cpp"
#include "scheduler_register_anchors.cpp"

#pragma code_seg(".text$30context")
int __stdcall EffectPoolContext_0042bbd0(EffectPool_0042bbd0** pools, int count) {
    int result = 0;
    while (count--)
        result += (*pools++)->InstallTasks();
    return result;
}
#pragma code_seg()
