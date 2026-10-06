#include "item_update.hpp"
#pragma code_seg(".text$124icons")
void FrontScript::SetActiveCount(int count) {
    int index=0;
    for (;index<count;++index)
        *reinterpret_cast<unsigned int*>(storage+0x4CDC+index*0x3AC)|=2;
    if (index>=9) return;
    for (;index<9;++index)
        *reinterpret_cast<unsigned int*>(storage+0x4CDC+index*0x3AC)&=~2u;
}
#pragma code_seg()
#include "sound_queue.hpp"
extern "C" short data_004749ce[];
#pragma code_seg(".text$125queue")
int SoundQueue::Queue(int sound_id, int request) {
    int priority = data_004749ce[sound_id * 4];
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
