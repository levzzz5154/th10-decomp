// Genuine 0x004491C0 lookup body; compiler ABI anchor, not selected code.
#include "th10/render/animation_validate_handle_00449450.hpp"

struct AnimationLookupEntry_00449450 {
    AnimationLookupEntry_00449450* object;
    AnimationLookupEntry_00449450* next;
};
struct AnimationLookupContext {
    unsigned char reserved[0x72DAD4];
    AnimationLookupEntry_00449450* primary_bucket;
    int reserved_72dad8;
    AnimationLookupEntry_00449450* secondary_bucket;
};

#pragma code_seg(".text$01find")
void* __fastcall AnimationManager_00449450::Find(
        AnimationLookupContext* context, AnimationScriptId_00449450 id) {
    if (!id.value)
        return 0;
    for (AnimationLookupEntry_00449450* node = context->primary_bucket;
         node != 0; node = node->next)
        if (*(int*)node->object == id.value)
            return node->object;
    for (AnimationLookupEntry_00449450* node = context->secondary_bucket;
         node != 0; node = node->next)
        if (*(int*)node->object == id.value)
            return node->object;
    return 0;
}
#pragma code_seg()
