// Compiler context only; never selected as recovered game code.
#include "../../../src/game/front/recovery_linked_cleanup_00417770.cpp"

extern "C" ScoreChain_00417770* g_laser_manager;

#pragma code_seg(".text$03context")
int __stdcall RecoveryLinkedCleanupCompilerContext() {
    ScoreChain_00417770* manager = g_laser_manager;
    manager->ReleaseChain();
    return 0;
}
#pragma code_seg()
