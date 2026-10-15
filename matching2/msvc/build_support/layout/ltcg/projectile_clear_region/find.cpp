// Compiler context only: the animation lookup at 0x004491C0.
#include "lookup.hpp"
#pragma code_seg(".text$f004491c0F")
Entity* __fastcall AnimationLookup::Find(AnimationLookupContext* context, CutAnimationId id) {
    if (!id.value)
        return 0;
    for (AnimationEntry* node = context->primary_bucket; node != 0; node = node->next)
        if (*(unsigned int*)node->object == id.value)
            return (Entity*)node->object;
    for (AnimationEntry* node = context->secondary_bucket; node != 0; node = node->next)
        if (*(unsigned int*)node->object == id.value)
            return (Entity*)node->object;
    return 0;
}
#pragma code_seg()
