// Compiler context only; never selected as recovered game code.
#include "../../../src/core/sprtlib/anm_manager_update.cpp"

#pragma code_seg(".text$00init")
#include "../../contexts/legacy/game/entity_initialize.cpp"
#pragma code_seg()

typedef int (__fastcall* AnmManagerTask)(AnmManager* manager);

#pragma code_seg(".text$03context")
int __stdcall AnmManagerUpdateContext(AnmManagerTask* tasks) {
    // The passes are only reached through their scheduler callbacks.
    tasks[0] = AnmManager_UpdatePrimaryTask2;
    tasks[1] = AnmManager_UpdateSecondaryTask2;
    return 0;
}
#pragma code_seg()
