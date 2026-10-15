extern "C" const float data_00470b20;
#include "th10/platform/sound_queue.hpp"
extern "C" short g_sound_priority[];
#pragma code_seg(".text$40pan")
void SoundQueue::QueuePan(int sound_id, float pan) {
    int priority = g_sound_priority[sound_id * 4];
    int request = int(pan * data_00470b20);
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
            return;
        }
    }
    if (slot < 12) {
        sound_ids[slot] = sound_id;
        priorities[sound_id] = priority;
        requests[slot][0] = request;
        ++counts[slot];
    }
}
#pragma code_seg()
