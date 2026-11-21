#include "th10/platform/sound_queue.hpp"
extern "C" short g_sound_priority[];

#ifndef TH10_SOUND_QUEUE_SECTION
#define TH10_SOUND_QUEUE_SECTION ".text$05queue"
#endif
#pragma code_seg(TH10_SOUND_QUEUE_SECTION)
// A new sound returns SlotCount if no slot is free. A duplicate returns its
// existing slot even when that slot cannot accept another request.
int SoundQueue::Queue(int sound_id, int request) {
    enum { SlotCount = sizeof(sound_ids) / sizeof(sound_ids[0]),
           RequestsPerSlot = sizeof(requests[0]) / sizeof(requests[0][0]) };
    int priority = g_sound_priority[sound_id * 4];
    int slot;
    for (slot = 0; slot < SlotCount; ++slot) {
        if (sound_ids[slot] < 0)
            break;
        if (sound_ids[slot] == sound_id) {
            int count = counts[slot];
            if (count < RequestsPerSlot) {
                requests[slot][count] = request;
                ++counts[slot];
            }
            return slot;
        }
    }
    if (slot < SlotCount) {
        sound_ids[slot] = sound_id;
        priorities[sound_id] = priority;
        requests[slot][0] = request;
        ++counts[slot];
    }
    return slot;
}
#pragma code_seg()
#undef TH10_SOUND_QUEUE_SECTION
