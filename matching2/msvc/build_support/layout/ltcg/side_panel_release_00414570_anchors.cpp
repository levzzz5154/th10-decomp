// Compiler context only: stand-ins for the two release routines. Each keeps
// its receiver across opaque calls the way the real body does, so the pass
// hands the slot over in ESI and the file in EDI.
#include "th10/game/side_panel_release.hpp"

extern "C" void __cdecl SidePanelReleaseBarrier(void* value);

#pragma code_seg(".text$004136c0_fn")
void PanelSlot::Release() {
    SidePanelReleaseBarrier(this);
    SidePanelReleaseBarrier(this);
}
#pragma code_seg(".text$00447810_fn")
void PanelResource2::Release() {
    void** entry = reinterpret_cast<void**>(this);
    do {
        SidePanelReleaseBarrier(*entry);
        ++entry;
    } while (*entry);
    SidePanelReleaseBarrier(this);
}
#pragma code_seg()
