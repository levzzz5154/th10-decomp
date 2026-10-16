// Compiler context only; never selected as recovered game code.
#include "../../../src/game/front/recovery_linked_cleanup.cpp"

extern "C" ScoreChain* g_laser_manager;

#pragma code_seg(".text$03context")
int __stdcall RecoveryLinkedCleanupCompilerContext() {
    ScoreChain* manager = g_laser_manager;
    manager->ReleaseChain();
    return 0;
}
#pragma code_seg()
