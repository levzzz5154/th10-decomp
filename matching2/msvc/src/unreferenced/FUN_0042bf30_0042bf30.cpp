// Complete effect-pool allocation/initialization/registration factory.
#include "th10/game/effect_pool_state_0042bb30.hpp"
#include "th10/game/effect_pool_tasks_0042bbd0.hpp"
void* __cdecl operator new(unsigned int);
extern "C" EffectPoolState* __fastcall FUN_0042bb30(int, EffectPoolState*);
extern "C" void __stdcall asm_FUN_0042bc30_0042bc30(EffectPoolState*);
extern "C" void __cdecl entry_free_004524a1(void*);

#pragma code_seg(".text$02factory")
extern "C" __declspec(noinline) EffectPoolState* __cdecl
asm_FUN_0042bf30_0042bf30() {
    EffectPoolState* state = new EffectPoolState;
    if (state)
        state = FUN_0042bb30(0, state);
    else
        state = 0;
    if (reinterpret_cast<EffectPool_0042bbd0*>(state)->InstallTasks()) {
        if (state) {
            asm_FUN_0042bc30_0042bc30(state);
            entry_free_004524a1(state);
        }
        return 0;
    }
    return state;
}
#pragma code_seg()
