#include "th10/game/score_hud_00417040.hpp"
// Compiler-only ABI anchors for the animation lookup (0x004491C0) and the
// flag setter (0x004492A0), placed by clusters whose recovered code precedes
// 0x004491C0. The setter forwards no receiver, so the pass drops ECX from
// every call. Never selected as recovered game code.
//
// The including source declares ResultAnimationId and the setter.
struct ResultAnimationEntry {
    ResultAnimationEntry* object;
    ResultAnimationEntry* next;
    unsigned char reserved_08[0x0C];
    ResultAnimationEntry* children;
    int children_flagged;
    unsigned char reserved_1c[0x340];
    unsigned int flags;
};

struct ResultAnimationLookup {
    unsigned char reserved[0x72DAD4];
    ResultAnimationEntry* primary_bucket;
    int reserved_2;
    ResultAnimationEntry* secondary_bucket;
};

#pragma code_seg(".text$004491c0_fn")
__declspec(noinline) void* __fastcall ResultAnimation_Find(
        ResultAnimationLookup* context, ResultAnimationId id) {
    if (!id.value)
        return 0;
    for (ResultAnimationEntry* node = context->primary_bucket; node != 0; node = node->next)
        if (*(int*)node->object == id.value)
            return node->object;
    for (ResultAnimationEntry* node = context->secondary_bucket; node != 0; node = node->next)
        if (*(int*)node->object == id.value)
            return node->object;
    return 0;
}
#pragma code_seg()

#pragma code_seg(".text$004492a0_fn")
__declspec(noinline) void* __fastcall ResultAnimation_Retire(
        ResultAnimationLookup* context, ResultAnimationId id) {
    ResultAnimationEntry* entry =
        (ResultAnimationEntry*)ResultAnimation_Find(context, id);
    if (entry) {
        entry->flags |= 0x4000000;
        if (!entry->children_flagged)
            for (entry = entry->children; entry != 0; entry = entry->next)
                entry->object->flags |= 0x4000000;
    }
    return entry;
}
#pragma code_seg()

