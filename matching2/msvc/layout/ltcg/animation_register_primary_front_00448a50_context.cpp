// Synthetic single-object creation context, never selected as recovered code.
#include "th10/game/card_animations.hpp"
extern "C" AnimationLists* data_00491c10;
#pragma code_seg(".text$0044e100_context")
void __stdcall SecondaryRegistrationContext(AnimationPool* pool,
        AnimationResource_00449870* resource, AnimationRef* out, int index) {
    Entity* object = pool->Allocate();
    object->render_bucket = 15;
    object->flags_35C |= 0x40000000u;
    resource->InitializeObject(object, index);
    *out = data_00491c10->RegisterPrimaryFront(object);
}
#pragma code_seg()
