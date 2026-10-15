// Compiler context only; never selected as recovered game code.
#include "../../src/game/smollscore/effect_pool_initialize_0042b4d0.cpp"

#pragma code_seg(".text$00h_init")
#include "../../src/game/entity_initialize_00401de0.cpp"
#pragma code_seg()

#include "scheduler_register_anchors.cpp"

void* __cdecl operator new(unsigned int size);

struct EffectManager_0042b430;
extern "C" EffectManager_0042b430* __cdecl asm_Recovery_CreateHugeResourceState_0042b660();

#pragma code_seg(".text$30context")
int __stdcall EffectPoolContext_0042b4d0(unsigned int size, SchedulerTask* task) {
    // Keeps the full registration anchors in the link.
    int result = Scheduler_RegisterPrimary(data_00491be4, task, size);
    EffectPool_0042b6f0* pool = static_cast<EffectPool_0042b6f0*>(operator new(size));
    if (pool->Initialize())
        return result;
    return (int)asm_Recovery_CreateHugeResourceState_0042b660();
}
#pragma code_seg()
