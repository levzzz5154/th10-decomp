// 0x0043D120, 301 bytes. Retail's manager input is EAX, with plain RET.
// The explicit stdcall entry below remains outside the exact-build manifest.
#include "sound_wave_types.hpp"

typedef int (__stdcall* SoundKillTimer)(void* window, unsigned int timer_id);
extern "C" {
    void __cdecl entry_free_00452422(void* memory);
    void __cdecl owner_free_004524a1(void* memory);
    extern SoundKillTimer g_sound_kill_timer;
}

extern "C" int __stdcall Sound_Cleanup_0043d120(WaveSoundManager* manager) {
    if (manager->loaded_music_data) {
        entry_free_00452422(manager->loaded_music_data);
        manager->loaded_music_data = 0;
    }
    // Retail interleaves the second bank with the first, rather than
    // releasing all 256 slots in increasing address order.
    for (unsigned int index = 0; index < 128; ++index) {
        WaveSecondaryBuffer* buffer = manager->secondary_buffers[index + 128];
        if (buffer) {
            buffer->methods->release(buffer);
            manager->secondary_buffers[index + 128] = 0;
        }
        buffer = manager->secondary_buffers[index];
        if (buffer) {
            buffer->methods->release(buffer);
            manager->secondary_buffers[index] = 0;
        }
    }
    for (unsigned int index = 0; index < 37; ++index) {
        unsigned char* pending = manager->pending_wave[index];
        if (pending) {
            entry_free_00452422(pending);
            manager->pending_wave[index] = 0;
        }
    }
    if (manager->device_owner) {
        g_sound_kill_timer(manager->window, 1);
        Sound_StopMusicWorker_0043dab0(manager);
        WaveSecondaryBuffer* buffer = manager->stream_buffer;
        manager->device = 0;
        // This call is unconditional. An absent stream buffer faults after
        // the raw-device field has already been cleared.
        buffer->methods->stop(buffer);
        buffer = manager->stream_buffer;
        if (buffer) {
            buffer->methods->release(buffer);
            manager->stream_buffer = 0;
        }
        SoundStream* output = manager->music_stream;
        if (output) {
            output->methods->destroy(output, 1);
            manager->music_stream = 0;
        }
        WaveDirectSoundDevice** owner = manager->device_owner;
        if (owner) {
            WaveDirectSoundDevice* device = *owner;
            if (device) {
                device->methods->release(device);
                *owner = 0;
            }
            owner_free_004524a1(owner);
            manager->device_owner = 0;
        }
        for (unsigned int index = 0; index < 16; ++index) {
            if (manager->cached_music_data[index]) {
                entry_free_00452422(manager->cached_music_data[index]);
                manager->cached_music_data[index] = 0;
            }
        }
    }
    return 0;
}
