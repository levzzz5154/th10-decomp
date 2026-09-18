// Compiler context only; never selected as recovered game code.
#include "../../src/game/recovery_linked_cleanup_00417770.cpp"

extern "C" ScoreChain_00417770* data_0047781c;

#pragma code_seg(".text$03context")
int __stdcall RecoveryLinkedCleanupCompilerContext() {
    ScoreChain_00417770* manager = data_0047781c;
    manager->ReleaseChain();
    return 0;
}
#pragma code_seg()
