// 0x004494C0..0x004494CE: forward a handle ID and the inherited DI frame.
#include "th10/render/animation_stop_run.hpp"

#pragma code_seg(".text$77stoprunhandle")
void AnimationRunHandle::SetStopFrameAndRun(unsigned short frame) {
    AnimationManager_SetStopFrameAndRun(frame, data_00491c10, value);
}
#pragma code_seg()
