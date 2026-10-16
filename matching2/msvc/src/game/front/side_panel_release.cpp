// 0x00414570: give back everything the side panel loaded for the stage.
//
// The stage slot always goes. The stage animation file and the stage buffer
// stay while either of two run flags (mask 9) is set. The panel arrives in EBX.
#include "th10/game/side_panel_release.hpp"

#pragma code_seg(".text$00414570_fn")
void FrontStagePartsView::ReleaseStageParts() {
    PanelSlot* slot = stage_slot;
    if (slot) {
        slot->Release();
        operator delete(slot);
        stage_slot = 0;
    }
    if (g_globals.flags & 9)
        return;
    PanelResource2** resource = &g_sprt_ctrl->stage_resource;
    if (*resource) {
        (*resource)->Release();
        operator delete(*resource);
        *resource = 0;
    }
    stage_state = 0;
    if (stage_buffer) {
        crt_free(stage_buffer);
        stage_buffer = 0;
    }
    stage_buffer = 0;
}
#pragma code_seg()
