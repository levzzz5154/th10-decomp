#ifndef TH10_SOUND_QUEUE_HPP
#define TH10_SOUND_QUEUE_HPP
struct SoundQueue {
    char reserved[0x408];
    int priorities[134];
    int sound_ids[12];
    int counts[12];
    int requests[12][128];
    __declspec(noinline) int Queue(int sound_id, int request);
};
extern "C" SoundQueue g_sound_manager;
#endif
