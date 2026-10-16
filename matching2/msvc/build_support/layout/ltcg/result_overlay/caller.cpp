#include "end.cpp"
#include "lookup.cpp"
extern "C" short g_sound_priority[];
// 0x00409E50
#pragma code_seg(".text$00409e50_fn")
void AnimationHandle::StopAtFrame1() {
    ResultAnimationId id;
    id.value = value;
    ResultAnimationEntry* node =
        static_cast<ResultAnimationEntry*>(ResultAnimation_Find(g_sprt_ctrl, id));
    if (node) {
        node->flags = 1;
        if (!node->children_flagged)
            for (ResultAnimationEntry* child = node->children; child; child = child->next)
                child->object->flags = 1;
    }
}

// 0x0043DC90
#pragma code_seg(".text$0043dc90_fn")
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


