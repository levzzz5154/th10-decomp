// Compiler context only: the anchor copy of 0x0043DD10, queueing a panned
// sound request. The whole-program pass derives the retail register state
// (receiver in ESI, sound id in EBX). The anchor bytes are never exported as
// recovered code.
#include "th10/platform/sound_queue.hpp"

extern "C" short data_004749ce[];
extern "C" float data_00470b20;

#pragma code_seg(".text$0043dd10_s")
void SoundQueue::QueuePan(int sound_id, float pan) {
    int priority = data_004749ce[sound_id * 4];
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
