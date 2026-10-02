// Compiler context only; never selected as recovered game code.
#include "th10/game/side_panel_release_00414570.hpp"
#include "../../src/game/side_panel_release_00414570.cpp"

extern "C" SidePanel_00414570* data_0047770c;
extern "C" void __cdecl SidePanelReleaseBarrier(void* value);

#pragma inline_depth(0)
#pragma code_seg(".text$0040a000_context")
extern "C" int __stdcall SidePanelReleaseContext(int count) {
    // The run state is reachable through pointers in the real program.
    SidePanelReleaseBarrier(&data_00474c40);
    for (int index = 0; index < count; ++index)
        data_0047770c->ReleaseStageParts();
    return count;
}
#pragma code_seg()
#pragma inline_depth()
