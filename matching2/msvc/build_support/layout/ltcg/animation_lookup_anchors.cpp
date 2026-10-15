// Compiler-only ABI anchors for the animation lookup (0x004491C0) and the
// flag setter (0x004492A0), placed by clusters whose recovered code precedes
// 0x004491C0. The setter forwards no receiver, so the pass drops ECX from
// every call. Never selected as recovered game code.
//
// The including source declares AnimationScriptId and the setter.
struct AnimationLookupAnchorEntry {
    AnimationLookupAnchorEntry* object;
    AnimationLookupAnchorEntry* next;
    unsigned char reserved_08[0x0C];
    AnimationLookupAnchorEntry* children;
    int children_flagged;
    unsigned char reserved_1c[0x340];
    unsigned int flags;
};

struct AnimationLookupContext {
    unsigned char reserved[0x72DAD4];
    AnimationLookupAnchorEntry* primary_bucket;
    int reserved_2;
    AnimationLookupAnchorEntry* secondary_bucket;
};

#pragma code_seg(".text$02find")
__declspec(noinline) void* __fastcall AnimationManager_Find(
        AnimationLookupContext* context, AnimationScriptId id) {
    if (!id.value)
        return 0;
    for (AnimationLookupAnchorEntry* node = context->primary_bucket; node != 0; node = node->next)
        if (*(int*)node->object == id.value)
            return node->object;
    for (AnimationLookupAnchorEntry* node = context->secondary_bucket; node != 0; node = node->next)
        if (*(int*)node->object == id.value)
            return node->object;
    return 0;
}
#pragma code_seg()

#pragma code_seg(".text$04setflag")
__declspec(noinline) void* __fastcall AnimationManager_SetFlag_004492a0(
        AnimationLookupContext* context, AnimationScriptId id) {
    AnimationLookupAnchorEntry* entry =
        (AnimationLookupAnchorEntry*)AnimationManager_Find(context, id);
    if (entry) {
        entry->flags |= 0x4000000;
        if (!entry->children_flagged)
            for (entry = entry->children; entry != 0; entry = entry->next)
                entry->object->flags |= 0x4000000;
    }
    return entry;
}
#pragma code_seg()

