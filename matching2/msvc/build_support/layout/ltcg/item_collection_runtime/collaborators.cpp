// Complete real animation lookup/removal, life-icon and sound-queue callees.
#include "types/update.hpp"
#pragma code_seg(".text$f004491c0F")
ItemAnimationNode* ItemAnimationLists::Find(ItemAnimationHandle handle) {
    if (!handle.value)
        return 0;
    for (ItemAnimationNode* node = primary; node != 0; node = node->next)
        if (*reinterpret_cast<unsigned int*>(node->object) == handle.value)
            return node->object;
    for (ItemAnimationNode* node = secondary; node != 0; node = node->next)
        if (*reinterpret_cast<unsigned int*>(node->object) == handle.value)
            return node->object;
    return 0;
}
#pragma code_seg(".text$f004492a0F")
void* ItemAnimationLists::MarkForRemoval(ItemAnimationHandle handle) {
    ItemAnimationNode* node = Find(handle);
    if (node) {
        node->flags |= 0x04000000u;
        if (!node->children_flagged)
            for (node = node->children; node != 0; node = node->next)
                node->object->flags |= 0x04000000u;
    }
    return node;
}
#pragma code_seg()

#pragma code_seg(".text$f00413790F")
void ItemHud::SetActiveCount(int count) {
    int index=0;
    for (;index<count;++index)
        *reinterpret_cast<unsigned int*>(storage+0x4CDC+index*0x3AC)|=2;
    if (index>=9) return;
    for (;index<9;++index)
        *reinterpret_cast<unsigned int*>(storage+0x4CDC+index*0x3AC)&=~2u;
}
#pragma code_seg()
#include "th10/platform/sound_queue.hpp"
extern "C" short g_sound_priority[];
#pragma code_seg(".text$f0043dc90F")
int SoundQueue::Queue(int sound_id, int request) {
    int priority = g_sound_priority[sound_id * 4];
    int slot;
    for (slot = 0; slot < 12; ++slot) {
        if (sound_ids[slot] < 0)
            break;
        if (sound_ids[slot] == sound_id) {
            int count = counts[slot];
            if (count < 128) {
                requests[slot][count] = request;
                ++counts[slot];
            }
            return slot;
        }
    }
    if (slot < 12) {
        sound_ids[slot] = sound_id;
        priorities[sound_id] = priority;
        requests[slot][0] = request;
        ++counts[slot];
    }
    return slot;
}
#pragma code_seg()
