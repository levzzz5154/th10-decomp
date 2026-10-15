// 0x00414570: give back everything the side panel loaded for the stage.
//
// The stage slot always goes. The stage animation file and the stage buffer
// stay while either of two run flags (mask 9) is set. The panel arrives in EBX.
#include "th10/game/side_panel_release_00414570.hpp"

#pragma code_seg(".text$00414570_fn")
void SidePanel_00414570::ReleaseStageParts() {
    PanelSlot_004136c0* slot = stage_slot;
    if (slot) {
        slot->Release();
        operator delete(slot);
        stage_slot = 0;
    }
    if (data_00474c40.flags & 9)
        return;
    PanelResource_00447810** resource = &data_00491c10->stage_resource;
    if (*resource) {
        (*resource)->Release();
        operator delete(*resource);
        *resource = 0;
    }
    stage_state = 0;
    if (stage_buffer) {
        entry_free_00452422(stage_buffer);
        stage_buffer = 0;
    }
    stage_buffer = 0;
}
#pragma code_seg()
