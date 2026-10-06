#include "runtime.hpp"
extern "C" float data_00470b4c, data_00470b48;
#pragma code_seg(".text$f00448db0F")
AnimationRef AnimationResource_0043e710::CreateOffset(
        int index, const Vector3* position) {
    Entity* object=static_cast<AnimationPool*>(data_00491c10)->Allocate();
    unsigned int flags=object->flags_35C;
    object->render_bucket=0;
    object->flags_35C=flags|0x40000000u;
    object->position.x=position->x+data_00470b4c;
    object->position.y=position->y+data_00470b48;
    object->position.z=position->z;
    LoadScript(object,index);
    return static_cast<AnimationLists*>(data_00491c10)->RegisterPrimaryBack(object);
}
#pragma code_seg()
