// Real body of the animation restart 0x00449250 the difficulty selection
// screen 0x00430320 calls, unselected here, seen through the lookup types of
// this link so that it shares the one lookup at 0x004491C0; and 0x0042C750,
// which restarts one animation slot of the room at frame 3 (the maintained
// free-function form is src/game/title/title_dispatch_animation_slot_secondary.cpp).
#define SprtCtrl RecoveryLookup
#define AnimationLookupContext RecoveryLookupContext
#define AnimationScriptId RecoveryScriptId
#define code_seg(name) code_seg(".text$00449250_fn")
#include "../../../../src/core/sprtlib/animation_manager_set_stop_frame_and_run.cpp"
#undef code_seg
struct TitleAnimationSlotView {
    unsigned char reserved_000[0x2C4];
    AnimationScriptId slots[195];
    __declspec(noinline) void RestartSlot(int slot);
};
#pragma code_seg(".text$0042c750_fn")
void TitleAnimationSlotView::RestartSlot(int slot) {
    AnimationManager_SetStopFrameAndRun(3, g_sprt_ctrl, slots[slot]);
}
#pragma code_seg()
