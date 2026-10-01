// Select the state's animation ID at +0x2C4 + slot*4 and run its tree.
#include "th10/render/animation_stop_run.hpp"

#pragma code_seg(".text$47dispatch")
__declspec(noinline) void __fastcall DispatchAnimationSlotSecondary(int slot, GameAnimationSlots* state) {
    AnimationManager_SetStopFrameAndRun(3, data_00491c10, AnimationSlots(state)[slot]);
}
#pragma code_seg()
