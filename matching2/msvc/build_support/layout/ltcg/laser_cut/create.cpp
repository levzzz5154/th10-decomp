// Complete semantic candidate for retail 0x00448DB0..0x00448E25 (118 bytes).
// This file is an unselected ABI anchor candidate, not a byte-match claim.
// Native LTCG must earn position in EDI with resource/out/index on the stack.
#include "th10/render/animation_public_callers.hpp"
#include "animation_ids.hpp"

struct AnimationResourceFile;
struct AnimationObjectFile;
extern "C" __declspec(noinline) void* __stdcall LoadScript2(
    AnimationResourceFile* resource, AnimationObjectFile* object, int index);

// Retail reads these existing single-precision data cells; do not substitute
// immediates because the x87 memory operands are part of the complete body.
extern "C" float flt_224;
extern "C" float flt_16;

#pragma code_seg(".text$f00448db0F")
CutAnimationId CutAnimationResource::CreateOffset(int index,const Vector3* position) {
 Entity* object=static_cast<AnimationPool*>(g_sprt_ctrl)->Allocate();
 unsigned int flags=object->flags_35C;
 object->render_bucket=0;
 object->flags_35C=flags|0x40000000u;
 object->position.x=position->x+224.0f;
 object->position.y=position->y+16.0f;
 object->position.z=position->z;
 LoadScript2(reinterpret_cast<AnimationResourceFile*>(this),
   reinterpret_cast<AnimationObjectFile*>(object),index);
 return static_cast<CutAnimationLists*>(g_sprt_ctrl)->RegisterPrimaryBack(object);
}
#pragma code_seg()
