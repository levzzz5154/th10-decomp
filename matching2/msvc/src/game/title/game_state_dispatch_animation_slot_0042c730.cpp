// Select the state's animation ID at +0x2C4 + slot*4 and run its tree.
#include "th10/render/animation_stop_run.hpp"

#pragma code_seg(".text$46dispatch")
__declspec(noinline) void __fastcall DispatchAnimationSlot(int slot, GameAnimationSlots* state) {
    AnimationManager_SetStopFrameAndRun(2, data_00491c10, AnimationSlots(state)[slot]);
}
#pragma code_seg()
