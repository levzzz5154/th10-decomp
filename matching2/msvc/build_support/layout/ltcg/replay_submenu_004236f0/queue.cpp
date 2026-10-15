#include "th10/game/replay_submenu_004236f0/state.hpp"
// 0x0043DC90: queue a sound request (this in ECX, sound id in EDI, request
// on the stack).
extern "C" short data_004749ce[];
#pragma code_seg(".text$02n")
int SubSoundQueue_004236f0::Queue(int sound_id, int request) {
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
