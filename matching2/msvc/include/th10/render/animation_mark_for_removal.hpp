#pragma once
// Mark the animation a script id names, and its children unless they are
// already flagged, for removal.  Teardown code inlines this together with the
// bucket lookup of 0x004491C0.

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

extern "C" AnimationBuckets* g_sprt_ctrl;  // the animation manager

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
