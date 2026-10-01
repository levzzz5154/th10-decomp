// Compiler context only; never selected as recovered game code.
#include "../../../src/game/player_manager_teardown_00408af0.cpp"
#include "../animation_lookup_anchors.cpp"
#define TH10_SCHEDULER_REMOVE_ONLY
#include "../manager_teardown_native_0041adf0/scheduler.cpp"

#pragma code_seg(".text$01b_context")
void __stdcall PlayerManagerTeardownCompilerContext(PlayerManager_00408af0* manager) {
    delete manager;
}
#pragma code_seg()
