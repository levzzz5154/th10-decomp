// Complete 69-byte state factory with its actual constructors/worker closure.
#include "th10/game/state_table_0041f850.hpp"
#include "th10/game/title_worker_owner_0041fac0.hpp"
void* __cdecl operator new(unsigned int);
extern "C" void __stdcall asm_FUN_0041fb50_0041fb50(StateTable_0041f850*);
extern "C" void __cdecl entry_free_004524a1(void*);
#pragma code_seg(".text$04factory")
extern "C" __declspec(noinline) StateTable_0041f850* __cdecl
asm_EnemySlot_CreateAndInitRetail_0041fd00() {
    StateTable_0041f850* state = new StateTable_0041f850;
    if (reinterpret_cast<TitleWorkerOwner*>(state)->StartWorker()) {
        if (state) {
            asm_FUN_0041fb50_0041fb50(state);
            entry_free_004524a1(state);
        }
        return 0;
    }
    return state;
}
#pragma code_seg()
