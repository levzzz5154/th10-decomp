#pragma once
#include "th10/core/func_ctrl.hpp"
#include "th10/platform/thread_sync.hpp"
#include "th10/render/native_render_targets.hpp"
#include "th10/game/ending_text_view.hpp"
#include "th10/render/animation_resource_removal.hpp"

// The singleton has the existing SprtCtrlTargetsView view. The removal code
// below takes its own typed views of the same original manager bytes.
struct AnimationBucketEntry {
    AnimationBucketEntry* object;    // +0x00: object registered by this node
    AnimationBucketEntry* next;      // +0x04: next node of the bucket list
    unsigned char reserved_08[0x0C];
    AnimationBucketEntry* children;  // +0x14: head of the child node list
    int children_flagged;            // +0x18
    unsigned char reserved_1c[0x340];
    unsigned int flags;              // +0x35C
};

struct AnimationBuckets {
    unsigned char reserved[0x72DAD4];
    AnimationBucketEntry* primary_bucket;    // +0x72DAD4
    int reserved_2;                          // +0x72DAD8
    AnimationBucketEntry* secondary_bucket;  // +0x72DADC
};

enum { kAnimationMarkedForRemoval = 0x04000000 };


__forceinline AnimationBucketEntry* FindAnimationEntry(AnimationBuckets* buckets, int id) {
    for (AnimationBucketEntry* node = buckets->primary_bucket; node != 0; node = node->next)
        if (*(int*)node->object == id)
            return node->object;
    for (AnimationBucketEntry* node = buckets->secondary_bucket; node != 0; node = node->next)
        if (*(int*)node->object == id)
            return node->object;
    return 0;
}

__forceinline void MarkAnimationForRemoval(AnimationBuckets* buckets, int id) {
    if (id) {
        AnimationBucketEntry* animation = FindAnimationEntry(buckets, id);
        if (animation) {
            animation->flags |= kAnimationMarkedForRemoval;
            if (!animation->children_flagged) {
                for (AnimationBucketEntry* child = animation->children; child != 0;
                     child = child->next)
                    child->object->flags |= kAnimationMarkedForRemoval;
            }
        }
    }
}

// One entry's animation interface.  Retail calls its third virtual slot (+0x8)
// with the interface itself pushed, i.e. a __stdcall member.
struct AnimationHandle9 {
    virtual void slot0();
    virtual void slot1();
    virtual void __stdcall slot2();
};

struct AnimationResourceEntry {
    AnimationHandle9* handle;   // +0x00
    void* allocation;                   // +0x04
    unsigned char pad_008[8];
};

struct AnimationResource6 {
    unsigned char pad_000[0x108];
    void* resource_108;                            // +0x108: the record's own interface
    int entry_count_10c;                           // +0x10C
    unsigned char pad_110[0x118 - 0x110];
    void* auxiliary_118;                           // +0x118
    void* auxiliary_11c;                           // +0x11C
    AnimationResourceEntry* entries_120;  // +0x120
    unsigned char pad_124[0x12C - 0x124];
    void* auxiliary_12c;                           // +0x12C

    __declspec(noinline) void Release();
};

void __cdecl operator delete(void*);
extern "C" void __cdecl crt_free_startup(void*);
