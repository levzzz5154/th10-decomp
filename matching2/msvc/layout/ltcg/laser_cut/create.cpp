// Complete semantic candidate for retail 0x00448DB0..0x00448E25 (118 bytes).
// This file is an unselected ABI anchor candidate, not a byte-match claim.
// Native LTCG must earn position in EDI with resource/out/index on the stack.
#include "th10/render/animation_public_callers.hpp"
#include "animation_ids.hpp"

struct AnimationResource_0043e710;
struct AnimationObject_0043e710;
extern "C" __declspec(noinline) void* __stdcall LoadScript_0043e710(
    AnimationResource_0043e710* resource, AnimationObject_0043e710* object, int index);

// Retail reads these existing single-precision data cells; do not substitute
// immediates because the x87 memory operands are part of the complete body.
extern "C" float data_00470b4c;
extern "C" float data_00470b48;

#pragma code_seg(".text$f00448db0F")
CutAnimationId CutAnimationResource::CreateOffset(int index,const Vector3* position) {
 Entity* object=static_cast<AnimationPool*>(data_00491c10)->Allocate();
 object->flags_35C|=0x40000000u;
 object->render_bucket=0;
 object->position.x=position->x+data_00470b4c;
 object->position.y=position->y+data_00470b48;
 object->position.z=position->z;
 LoadScript_0043e710(reinterpret_cast<AnimationResource_0043e710*>(this),
   reinterpret_cast<AnimationObject_0043e710*>(object),index);
 return static_cast<CutAnimationLists*>(data_00491c10)->RegisterPrimaryBack(object);
}
#pragma code_seg()
