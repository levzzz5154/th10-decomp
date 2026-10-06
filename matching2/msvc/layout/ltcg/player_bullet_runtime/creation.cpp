// Complete genuine creation graph in a second translation unit. The shared
// animation headers describe the same manager/entity storage used by the
// collision sweep's named views. No ABI wrapper or synthetic caller is used.
#include "animation_public_callers.hpp"
__declspec(noinline) void __stdcall Entity_Init(Entity* entity);
#include "entity_initialize.cpp"
#include "dependencies.cpp"
#include "preserve.cpp"
#include "initialize.cpp"

struct PickupHandle;
#pragma code_seg(".text$f00448d00F")
__declspec(noinline) AnimationRef __stdcall Pickup_CreatePrimaryBack(
        void* resource,int script,int layer) {
    Entity* object=static_cast<AnimationPool*>(data_00491c10)->Allocate();
    unsigned int flags=object->flags_35C;
    object->render_bucket=layer;
    object->flags_35C=flags|0x40000000u;
    static_cast<AnimationResource_00449870*>(resource)->InitializeObject(object,script);
    return static_cast<AnimationLists*>(data_00491c10)->RegisterPrimaryBack(object);
}
#pragma code_seg()

#include "collision_loader.cpp"
#include "collision_create.cpp"

#include "item_start_script.cpp"
