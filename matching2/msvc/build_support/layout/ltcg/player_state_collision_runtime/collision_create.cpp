#include "runtime.hpp"
extern "C" float flt_224, flt_16;
#pragma code_seg(".text$f00448db0F")
AnimationRef AnimationResourceFile::CreateOffset(
        int index, const Vector3* position) {
    Entity* object=static_cast<AnimationPool*>(g_sprt_ctrl)->Allocate();
    unsigned int flags=object->flags_35C;
    object->render_bucket=0;
    object->flags_35C=flags|0x40000000u;
    object->position.x=position->x+flt_224;
    object->position.y=position->y+flt_16;
    object->position.z=position->z;
    LoadScript(object,index);
    return static_cast<AnimationLists*>(g_sprt_ctrl)->RegisterPrimaryBack(object);
}
#pragma code_seg()
