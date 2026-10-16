// Compiler context only; never selected as recovered game code.
#include "../../../../src/game/replay/replay_manager_teardown.cpp"
#include "../../../../src/game/replay/linked_pool_release.cpp"
#define TH10_SCHEDULER_REMOVE_ONLY
#include "../manager_teardown_native/scheduler.cpp"

#pragma code_seg(".text$01b_context")
void __stdcall ReplayManagerTeardownCompilerContext(ReplayManager* manager) {
    delete manager;
}
#pragma code_seg()
