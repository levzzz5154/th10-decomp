// Compiler context only; never selected as recovered game code.
#include "../../src/core/sprtlib/anm_manager_update.cpp"

#pragma code_seg(".text$00init")
#include "../../src/game/entity_initialize_00401de0.cpp"
#pragma code_seg()

typedef int (__fastcall* AnmManagerTask)(AnmManager* manager);

#pragma code_seg(".text$03context")
int __stdcall AnmManagerUpdateContext(AnmManagerTask* tasks) {
    // The passes are only reached through their scheduler callbacks.
    tasks[0] = AnmManager_UpdatePrimaryTask_004485d0;
    tasks[1] = AnmManager_UpdateSecondaryTask_004485e0;
    return 0;
}
#pragma code_seg()
