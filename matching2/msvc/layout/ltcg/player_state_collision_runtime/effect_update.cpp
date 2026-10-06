#include "effect_update.hpp"

#pragma code_seg(".text$f00409e50F")
void PickupHandle::StopAtFrame1() {
    AnimationRef id(value);
    AnimationObject *object = static_cast<AnimationContext*>(data_00491c10)->Find(id);
    if (object) {
        object->stop_frame = 1;
        if (!object->child_previous)
            for (AnimationNode *child = object->child_next; child; child = child->next)
                child->object->stop_frame = 1;
    }
}
#pragma code_seg()
#pragma code_seg(".text$f0040c4d0F")
void PickupHandle::StopAtFrame3() {
    AnimationRef id(value);
    AnimationObject *object = static_cast<AnimationContext*>(data_00491c10)->Find(id);
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

extern "C" const float data_00470b40, data_00470b3c, data_00470b04, data_00470b38;
#pragma code_seg(".text$f00428d70F")
int Vec3::OutsideViewport(float horizontal_margin, float vertical_margin) const {
    if (!(x + horizontal_margin <= data_00470b40) && !(x - horizontal_margin >= data_00470b3c) &&
        !(y + vertical_margin <= data_00470b04) && !(y - vertical_margin >= data_00470b38))
        return 0;
    return 1;
}
#pragma code_seg()
