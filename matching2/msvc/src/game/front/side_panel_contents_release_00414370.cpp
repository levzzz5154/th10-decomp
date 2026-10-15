// 0x00414370..0x0041454C: release everything the side panel holds.
//
// While either of two run flags (mask 9) is set the stage is being kept for
// its next use: the stage animation file is only retired from the animations
// that play it, and the stage buffer is handed over through 0x00491BE8.
// Otherwise both are freed. The stage slot, the three fixed animations, the
// counters and the eight effect animations always go.
#include "th10/game/side_panel_contents_release_00414370.hpp"

#pragma code_seg(".text$00414370_fn")
void __stdcall SidePanel_ReleaseContents_00414370(SidePanel_00414370* panel) {
    if (!(data_00474c40.flags & 9)) {
        PanelResource_00414370** resource = &g_sprt_ctrl->stage_resource;
        if (*resource) {
            (*resource)->Release();
            operator delete(*resource);
            *resource = 0;
        }
    } else {
        g_sprt_ctrl->MarkResourceForRemoval(panel->stage_file);
    }
    panel->stage_file = 0;

    PanelSlot_00414370* slot = panel->stage_slot;
    if (slot) {
        slot->Release();
        operator delete(slot);
        panel->stage_slot = 0;
    }

    if (!(data_00474c40.flags & 9)) {
        if (panel->stage_buffer) {
            entry_free_00452422(panel->stage_buffer);
            panel->stage_buffer = 0;
        }
        panel->stage_buffer = 0;
        data_00491be8 = 0;
    } else {
        data_00491be8 = panel->stage_buffer;
    }

    if (panel->update_task)
        panel->update_task->flags &= ~2u;

    panel->frame.Release(g_sprt_ctrl);
    PanelAnimationManager_00414370* animations = g_sprt_ctrl;
    panel->caption.Release(animations);
    panel->gauge.Release(animations);
    int* counter = panel->counters;
    for (int index = 10; index != 0; --index)
        *counter++ = 0;

    PanelAnimation_00414370* effect = panel->effects;
    int remaining = 8;
    do {
        effect->ReleaseInPlace(animations);
        ++effect;
    } while (--remaining);
    panel->stage_ready = 0;
}
#pragma code_seg()
