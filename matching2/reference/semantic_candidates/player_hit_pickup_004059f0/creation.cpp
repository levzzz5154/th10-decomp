// Complete genuine creation graph in a second translation unit. The shared
// animation headers describe the same manager/entity storage used by the
// collision sweep's named views. No ABI wrapper or synthetic caller is used.
#include "th10/render/animation_public_callers.hpp"
__declspec(noinline) void __stdcall Entity_Init(Entity* entity);
#include "entity_initialize.cpp"
#include "dependencies.cpp"
#include "preserve.cpp"
#include "initialize.cpp"

struct PickupHandle;
#pragma code_seg(".text$126primary")
__declspec(noinline) PickupHandle* __stdcall Pickup_CreatePrimaryBack(
        void* resource,PickupHandle* output,int script,int layer) {
    Entity* object=static_cast<AnimationPool*>(data_00491c10)->Allocate();
    unsigned int flags=object->flags_35C;
    object->render_bucket=layer;
    object->flags_35C=flags|0x40000000u;
    static_cast<AnimationResource_00449870*>(resource)->InitializeObject(object,script);
    asm_AnimationManager_RegisterPrimaryBack_004489d0(data_00491c10,
        reinterpret_cast<void**>(output),object);
    return output;
}
#pragma code_seg()
