#include "runtime.hpp"
#include <string.h>

#pragma code_seg(".text$f00427c70F")
int FrameTimer::AtInterval(int interval) {
    if (current != previous && current % interval == 0) return 1;
    return 0;
}
#pragma code_seg(".text$f004491c0F")
PickupAnimation* PickupAnimationLists::Find(AnimationRef handle) {
    return FindInBuckets(handle);
}
#pragma code_seg(".text$f004492a0F")
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
#pragma code_seg(".text$f0040c480F")
void PlayerAnimationHandle::StopAtFrame2() {
    AnimationRef id(value);
    PickupAnimation* node=static_cast<PickupAnimationLists*>(data_00491c10)->Find(id);
    if (node) {
        node->stop_frame=2;
        if (!node->child_previous)
            for (PickupAnimationNode* child=node->child_next; child; child=child->next)
                child->object->stop_frame=2;
    }
}
#pragma code_seg(".text$f00449450F")
PickupAnimation* PlayerAnimationHandle::Validate() {
    AnimationRef id(value);
    PickupAnimation* object=static_cast<PickupAnimationLists*>(data_00491c10)->Find(id);
    if (!object) value=0;
    return object;
}
#pragma code_seg(".text$f00449630F")
void PlayerAnimationHandle::Retire() {
    AnimationRef id(value);
    static_cast<PickupAnimationLists*>(data_00491c10)->MarkForRemoval(id);
    value=0;
}
#pragma code_seg(".text$f00427b50F")
extern "C" PlayerDamageSource* __fastcall Player_AddDamageSource(
        unsigned int unused, Player* player, const PickupPosition* volatile position,
        unsigned int radius_bits, unsigned int speed_bits, int countdown, unsigned int damage) {
    (void)unused;
    const PickupPosition* saved_position=position;
    PlayerDamageSource* slot=player->damage_sources;
    for (int index=0; index<32; ++index,++slot) {
        if (slot->flags & 1u) continue;
        memset(slot,0,sizeof(*slot));
        slot->flags |= 3u;
        memset(&slot->position,0,sizeof(slot->position)+sizeof(slot->unknown_24));
        slot->position=*saved_position;
        volatile unsigned int* payload=reinterpret_cast<unsigned int*>(&slot->radius);
        payload[0]=radius_bits;
        payload[1]=speed_bits;
        if (!(slot->lifetime.flags & 1u)) {
            slot->lifetime.current=0;
            slot->lifetime.previous=-999999;
            slot->lifetime.elapsed=0.0f;
            slot->lifetime.speed=&data_00476f78;
            slot->lifetime.flags |= 1u;
        }
        slot->lifetime.current=countdown;
        slot->lifetime.previous=countdown-1;
        slot->lifetime.elapsed=static_cast<float>(countdown);
        slot->damage=static_cast<int>(damage);
        slot->damage_dealt=0;
        slot->damage_limit=999999;
        slot->interval=4;
        return slot;
    }
    return slot;
}
#pragma code_seg()
