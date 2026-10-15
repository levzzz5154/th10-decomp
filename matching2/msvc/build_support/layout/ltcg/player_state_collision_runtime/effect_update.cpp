#include "effect_update.hpp"

#pragma code_seg(".text$f00409e50F")
void PlayerAnimationHandle::StopAtFrame1() {
    AnimationRef id(value);
    AnimationObject *object = static_cast<AnimationContext*>(g_sprt_ctrl)->Find(id);
    if (object) {
        object->stop_frame = 1;
        if (!object->child_previous)
            for (AnimationNode *child = object->child_next; child; child = child->next)
                child->object->stop_frame = 1;
    }
}
#pragma code_seg()
#pragma code_seg(".text$f0040c4d0F")
void PlayerAnimationHandle::StopAtFrame3() {
    AnimationRef id(value);
    AnimationObject *object = static_cast<AnimationContext*>(g_sprt_ctrl)->Find(id);
    if (object) {
        object->stop_frame = 3;
        if (!object->child_previous)
            for (AnimationNode *child = object->child_next; child; child = child->next)
                child->object->stop_frame = 3;
    }
}
#pragma code_seg()
#pragma code_seg(".text$f0044c2a0F")
void Motion::Advance() {
    Vec3 offset;
    if (!(flags & 1)) {
        position += velocity;
        position.SnapToHundredths();
        return;
    }
    offset.SetPolar(angle, radius);
    offset.z = 0.0f;
    position = offset + velocity;
    position.SnapToHundredths();
}
#pragma code_seg()

extern "C" const float flt_neg192, flt_192, flt_0, flt_448;
#pragma code_seg(".text$f00428d70F")
int Vector3::OutsideViewport(float horizontal_margin, float vertical_margin) const {
    if (!(x + horizontal_margin <= flt_neg192) && !(x - horizontal_margin >= flt_192) &&
        !(y + vertical_margin <= flt_0) && !(y - vertical_margin >= flt_448))
        return 0;
    return 1;
}
#pragma code_seg()
