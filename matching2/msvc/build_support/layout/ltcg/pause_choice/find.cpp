// Complete 0x004491C0 lookup with its two actual inputs.
#include "th10/game/pause_choice/animation.hpp"
struct AnimationLookupEntry {
    AnimationLookupEntry* object;
    AnimationLookupEntry* next;
    unsigned char reserved_08[0x0C];
    AnimationLookupEntry* children;
    int children_flagged;
    unsigned char reserved_1c[0x340];
    unsigned int flags;
};
struct AnimationLookupContext {
    unsigned char reserved[0x72DAD4];
    AnimationLookupEntry* primary_bucket;
    int reserved_2;
    AnimationLookupEntry* secondary_bucket;
};
#pragma code_seg(".text$50find")
void* __fastcall AnimationManager_Find(
        AnimationLookupContext* context, AnimationScriptId id) {
    if (!id.value)
        return 0;
    for (AnimationLookupEntry* node = context->primary_bucket; node != 0; node = node->next)
        if (*(int*)node->object == id.value)
            return node->object;
    for (AnimationLookupEntry* node = context->secondary_bucket; node != 0; node = node->next)
        if (*(int*)node->object == id.value)
            return node->object;
    return 0;
}
#pragma code_seg()
