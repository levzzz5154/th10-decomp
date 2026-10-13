// 0x004491C0 - look a script id up in the primary and then the secondary
// animation bucket, returning the registered object of the matching entry.
//
// Two conventions come out of the whole-program pass rather than the source.
// The script id is a four-byte record, so MSVC leaves it in the caller's push
// slot; as a plain int the pass promotes it into ECX - the receiver register,
// which retail's callers never write because this lookup never reads its own
// receiver.  Both shapes are what the retail callers and the StopAtFrame pair
// require, so this unit is compiled as a cluster
// (layout/ltcg/stop_at_frame_pair_0040c480.json).

// One node of a lookup bucket; the object it registers carries its script id
// in its first word.
struct AnimationEntry {
    AnimationEntry* object;             // +0x00: object registered by this node
    AnimationEntry* next;               // +0x04: next node of the bucket list
    unsigned char reserved_08[0x0C];
    AnimationEntry* children;           // +0x14: head of the child node list
    int children_flagged;               // +0x18: children already flagged
    unsigned char reserved_1c[0x340];
    unsigned int flags;                  // +0x35C
};

// The lookup buckets live far inside the animation context, the large runtime
// structure this lookup receives in EDX.
struct AnimationLookupContext {
    unsigned char reserved[0x72DAD4];
    AnimationEntry* primary_bucket;     // +0x72DAD4
    int reserved_2;                     // +0x72DAD8
    AnimationEntry* secondary_bucket;   // +0x72DADC
};

struct AnimationScriptId {
    int value;
};

class AnimationManager {
public:
    void* __fastcall Find(AnimationLookupContext* context, AnimationScriptId id);
};

#pragma code_seg(".text$004491c0_find")
__declspec(noinline) void* __fastcall AnimationManager::Find(
        AnimationLookupContext* context, AnimationScriptId id) {
    if (!id.value)
        return 0;
    for (AnimationEntry* node = context->primary_bucket; node != 0; node = node->next)
        if (*(int*)node->object == id.value)
            return node->object;
    for (AnimationEntry* node = context->secondary_bucket; node != 0; node = node->next)
        if (*(int*)node->object == id.value)
            return node->object;
    return 0;
}
#pragma code_seg()
