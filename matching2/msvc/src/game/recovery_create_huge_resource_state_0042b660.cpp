// Complete 71-byte effect-pool factory with actual constructor and initializer.
#include "th10/game/effect_manager_0042b430.hpp"
#include "th10/game/effect_pool_0042b6f0.hpp"
void* __cdecl operator new(unsigned int);
extern "C" void __stdcall asm_FUN_0042b570_0042b570(EffectManager_0042b430*);
extern "C" void __cdecl entry_free_004524a1(void*);
#pragma code_seg(".text$00zbfactory")
extern "C" __declspec(noinline) EffectManager_0042b430* __cdecl
asm_Recovery_CreateHugeResourceState_0042b660() {
    EffectManager_0042b430* state = new EffectManager_0042b430;
    if (reinterpret_cast<EffectPool_0042b6f0*>(state)->Initialize()) {
        if (state) {
            asm_FUN_0042b570_0042b570(state);
            entry_free_004524a1(state);
        }
        return 0;
    }
    return state;
}
#pragma code_seg()
