// Complete 0x004491C0 lookup, actual context and id only.
#include "th10/game/pause_result_open/open_animation.hpp"
struct AnimationLookupEntryOpen { Entity* object; AnimationLookupEntryOpen* next; };
struct AnimationLookupContext {
    unsigned char reserved[0x72DAD4];
    AnimationLookupEntryOpen* primary_bucket;
    int reserved_72dad8;
    AnimationLookupEntryOpen* secondary_bucket;
};
#pragma code_seg(".text$004491c0_fn")
void* __fastcall AnimationManager_Find(AnimationLookupContext* context, AnimationScriptId id) {
    if (!id.value) return 0;
    for (AnimationLookupEntryOpen* node = context->primary_bucket; node != 0; node = node->next)
        if (node->object->animation_handle == id.value) return node->object;
    for (AnimationLookupEntryOpen* node = context->secondary_bucket; node != 0; node = node->next)
        if (node->object->animation_handle == id.value) return node->object;
    return 0;
}
#pragma code_seg()
