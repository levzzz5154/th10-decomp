#include "runtime.hpp"
#include <string.h>

#pragma code_seg(".text$30interval")
int FrameTimer::AtInterval(int interval) {
    if (current != previous && current % interval == 0) return 1;
    return 0;
}
#pragma code_seg(".text$40find")
PickupAnimation* PickupAnimationLists::Find(AnimationRef handle) {
    return FindInBuckets(handle);
}
#pragma code_seg(".text$50mark")
void* PickupAnimationLists::MarkForRemoval(AnimationRef handle) {
    // Retail returns the object when it has a previous child link, otherwise
    // the child cursor after traversal (null). Retire ignores this result.
    void* cursor=Find(handle);
    PickupAnimation* object=static_cast<PickupAnimation*>(cursor);
    if (object) {
        object->flags |= 0x04000000u;
        if (!object->child_previous)
            for (cursor=object->child_next; cursor;
                 cursor=static_cast<PickupAnimationNode*>(cursor)->next)
                static_cast<PickupAnimationNode*>(cursor)->object->flags |= 0x04000000u;
    }
    return cursor;
}
#pragma code_seg(".text$60stop")
void PickupHandle::StopAtFrame2() {
    AnimationRef id(value);
    PickupAnimation* node=static_cast<PickupAnimationLists*>(data_00491c10)->Find(id);
    if (node) {
        node->stop_frame=2;
        if (!node->child_previous)
            for (PickupAnimationNode* child=node->child_next; child; child=child->next)
                child->object->stop_frame=2;
    }
}
#pragma code_seg(".text$70validate")
PickupAnimation* PickupHandle::Validate() {
    AnimationRef id(value);
    PickupAnimation* object=static_cast<PickupAnimationLists*>(data_00491c10)->Find(id);
    if (!object) value=0;
    return object;
}
#pragma code_seg(".text$80retire")
void PickupHandle::Retire() {
    AnimationRef id(value);
    static_cast<PickupAnimationLists*>(data_00491c10)->MarkForRemoval(id);
    value=0;
}
#pragma code_seg(".text$90indicator")
extern "C" PickupRegion* __fastcall Pickup_AllocateIndicator(
        unsigned int unused, PickupManager* manager, const PickupPosition* volatile position,
        unsigned int radius_bits, unsigned int speed_bits, int countdown, unsigned int value) {
    (void)unused;
    const PickupPosition* saved_position=position;
    PickupRegion* slot=manager->regions;
    for (int index=0; index<32; ++index,++slot) {
        if (slot->flags & 1u) continue;
        memset(slot,0,sizeof(*slot));
        slot->flags |= 3u;
        memset(&slot->center,0,sizeof(slot->center)+sizeof(slot->reserved_24));
        slot->center=*saved_position;
        volatile unsigned int* payload=reinterpret_cast<unsigned int*>(&slot->radius);
        payload[0]=radius_bits;
        payload[1]=speed_bits;
        if (!(slot->timer.flags & 1u)) {
            slot->timer.current=0;
            slot->timer.previous=-999999;
            slot->timer.elapsed=0.0f;
            slot->timer.speed=&data_00476f78;
            slot->timer.flags |= 1u;
        }
        slot->timer.current=countdown;
        slot->timer.previous=countdown-1;
        slot->timer.elapsed=static_cast<float>(countdown);
        slot->value=static_cast<int>(value);
        slot->accumulated=0;
        slot->limit=999999;
        slot->interval=4;
        return slot;
    }
    return slot;
}
#pragma code_seg()
