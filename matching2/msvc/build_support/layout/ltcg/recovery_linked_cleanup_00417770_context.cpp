// Compiler context only; never selected as recovered game code.
#include "../../../src/game/front/front_linked_cleanup.cpp"

extern "C" LaserManagerListView* g_laser_manager;

#pragma code_seg(".text$03context")
int __stdcall RecoveryLinkedCleanupCompilerContext() {
    LaserManagerListView* manager = g_laser_manager;
    manager->ReleaseAll();
    return 0;
}
#pragma code_seg()
