// Synthetic caller context only, never selected as recovered game code.
#include "th10/game/card_animations.hpp"
extern "C" AnimationLists* g_sprt_ctrl;
#pragma code_seg(".text$0044e100_context")
void __stdcall SecondaryRegistrationContext(AnimationPool* pool,
        AnimationBank* resource, AnimationRef* out, int count) {
    for (int i = 0; i < count; ++i) {
        Entity* object = pool->Allocate();
        object->render_bucket = 15;
        object->flags_35C |= 0x40000000u;
        resource->InitializeObject(object, i);
        out[i] = g_sprt_ctrl->RegisterSecondaryBack(object);
    }
}
#pragma code_seg()
