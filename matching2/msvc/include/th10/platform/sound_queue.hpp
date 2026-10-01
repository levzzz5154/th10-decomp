#ifndef TH10_SOUND_QUEUE_HPP
#define TH10_SOUND_QUEUE_HPP
#include <stddef.h>

struct SoundQueue {
    char reserved[0x408];
    int priorities[134];
    int sound_ids[12];
    int counts[12];
    int requests[12][128];
    __declspec(noinline) int Queue(int sound_id, int request);
    __declspec(noinline) void QueuePan(int sound_id, float pan);
};
typedef char SoundQueueIdsOffset[offsetof(SoundQueue, sound_ids) == 0x620 ? 1 : -1];
typedef char SoundQueueCountsOffset[offsetof(SoundQueue, counts) == 0x650 ? 1 : -1];
typedef char SoundQueueRequestsOffset[offsetof(SoundQueue, requests) == 0x680 ? 1 : -1];
extern "C" SoundQueue data_00492590;
#endif
