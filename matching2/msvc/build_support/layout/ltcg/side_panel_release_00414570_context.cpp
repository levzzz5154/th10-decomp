// Compiler context only; never selected as recovered game code.
#include "th10/game/side_panel_release.hpp"
#include "../../../src/game/front/side_panel_release.cpp"

extern "C" FrontStagePartsView* g_front;
extern "C" void __cdecl SidePanelReleaseBarrier(void* value);

#pragma inline_depth(0)
#pragma code_seg(".text$0040a000_context")
extern "C" int __stdcall SidePanelReleaseContext(int count) {
    // The run state is reachable through pointers in the real program.
    SidePanelReleaseBarrier(&g_globals);
    for (int index = 0; index < count; ++index)
        g_front->ReleaseStageParts();
    return count;
}
#pragma code_seg()
#pragma inline_depth()
