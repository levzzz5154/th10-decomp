// Synthetic forwarding caller only; never selected as recovered game code.
#include "../../src/game/replay/linked_pool_release.cpp"
#pragma code_seg(".text$50context")
extern "C" int __stdcall ReplayPoolReleaseCompilerContext_0042ab20(int stage, ReplayPoolLists_0042aa50* lists) {
    ReplayPool_Clear_0042ab20(lists, stage);
    return 0;
}
#pragma code_seg()
