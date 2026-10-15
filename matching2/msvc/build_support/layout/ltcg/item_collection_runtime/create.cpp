// Complete semantic candidate for retail 0x00448DB0..0x00448E25 (118 bytes).
// This file is an unselected ABI anchor candidate, not a byte-match claim.
// Native LTCG must earn position in EDI with resource/out/index on the stack.
#include "types/animation_public.hpp"

extern "C" __declspec(noinline) void* __stdcall LoadScript_0043e710(
    AnimationResource_0043e710* resource, AnimationObject_0043e710* object, int index);

// Retail reads these existing single-precision data cells; do not substitute
// immediates because the x87 memory operands are part of the complete body.
extern "C" float data_00470b4c;
extern "C" float data_00470b48;

#pragma code_seg(".text$f00448db0F")
__declspec(noinline) void** __stdcall ItemAnimation_CreateOffset_00448db0(
    void* resource, void** out, int index, const Vector3* position) {
    Entity* object = static_cast<AnimationPool*>(g_sprt_ctrl)->Allocate();
    object->flags_35C |= 0x40000000u;
    object->render_bucket = 0;
    object->position.x = position->x + data_00470b4c;
    object->position.y = position->y + data_00470b48;
    object->position.z = position->z;
    LoadScript_0043e710(static_cast<AnimationResource_0043e710*>(resource),
        reinterpret_cast<AnimationObject_0043e710*>(object),index);
    asm_AnimationManager_RegisterPrimaryBack_004489d0(g_sprt_ctrl, out, object);
    return out;
}
#pragma code_seg()
