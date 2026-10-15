// Position wrappers forward their handle ID and inherited ESI position.
#include "th10/render/position_setter_pair.hpp"
#pragma code_seg(".text$80positionwrap")
void AnimationPositionHandle::SetPosition(const PositionVector_004492f0* position) {
    SetAnimationPosition_004492f0(g_sprt_ctrl, position, value);
}
#pragma code_seg()
#pragma code_seg(".text$90translatedwrap")
void AnimationPositionHandle::SetTranslatedPosition(const PositionVector_004492f0* position) {
    SetAnimationTranslatedPosition_00449350(position, g_sprt_ctrl, value);
}
#pragma code_seg()
