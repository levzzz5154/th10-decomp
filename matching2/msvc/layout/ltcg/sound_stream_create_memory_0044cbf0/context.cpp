// Compiler context only; never selected as recovered game code. The stream
// constructor and fill bodies are co-compiled so each takes its receiver and
// arguments where the real one does, and the factory gets a direct caller that
// passes what the cached-music player passes.
#include "../../../src/core/zwave/sound_stream_create_memory_0044cbf0.cpp"
#include "../sound_interfaces_dependencies/fill.cpp"
#include "../sound_interfaces_dependencies/rewind.cpp"
#include "../sound_interfaces_dependencies/read.cpp"

extern "C" extern WaveGuidImage data_0046a67c;

#pragma code_seg(".text$10context")
extern "C" __declspec(noinline) int __stdcall SoundMemoryStreamContext(WaveSoundManager** managers,
        int count) {
    int result = 0;
    while (count--) {
        WaveSoundManager* manager = *managers++;
        result |= reinterpret_cast<SoundDeviceOwner*>(manager->device_owner)->CreateMemoryStream(
            reinterpret_cast<SoundStreamingState**>(&manager->music_stream),
            manager->music_read_cursors[count], manager->music_remaining_bytes[count],
            manager->cached_music_records[count], 0x10100, data_0046a67c, 16,
            manager->music_thread_id, manager->music_worker_event);
    }
    return result;
}
#pragma code_seg()
