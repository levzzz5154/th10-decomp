// Behavioral recovery of the 786-byte initializer at 0x0043CD30. This typed
// method retains its ECX receiver and one stack window argument (RET 4).
#include "sound_wave_types.hpp"

typedef unsigned int (__stdcall* SoundSetTimer)(void* window, unsigned int id,
    unsigned int milliseconds, void* callback);

extern "C" {
    void* __cdecl asm_operator_new_00452493(unsigned int bytes);
    void __cdecl asm_free_004524a1(void* memory);
    int __stdcall Ordinal_11_00452170(const void* device_id,
        WaveDirectSoundDevice** output, void* outer);
    int __stdcall Sound_SetPrimaryFormat_0044c7e0(unsigned short bits,
        unsigned short channels, unsigned int rate, WaveDirectSoundDevice** owner);
    extern SoundSetTimer g_sound_set_timer;
    extern WaveSoundManager g_wave_sound_manager;
    extern const char* g_sound_preload_names[37];
    extern char g_sound_initialize_error[];
    extern char g_sound_initialize_ready[];
    extern char g_sound_preload_error[];
}

int WaveSoundManager::Initialize(void* target_window) {
    for (unsigned int index = 0; index < 128; ++index)
        sound_handles[index] = -1;
    for (unsigned int index = 0; index < 12; ++index)
        music_handles[index] = -1;

    WaveDirectSoundDevice** owner = static_cast<WaveDirectSoundDevice**>(asm_operator_new_00452493(4));
    if (owner)
        *owner = 0;
    device_owner = owner;
    // Retail still reads a null owner after allocation failure. The volatile
    // access also preserves the observed read after initializing the cell.
    WaveDirectSoundDevice* previous = *static_cast<WaveDirectSoundDevice* volatile*>(owner);
    if (previous) {
        previous->methods->release(previous);
        *owner = 0;
    }
    if (Ordinal_11_00452170(0, owner, 0) < 0 ||
        (*owner)->methods->set_cooperative_level(*owner, target_window, 2) < 0) {
        g_wave_error_log.Append(g_sound_initialize_error);
        // Logging may replace the manager's owner cell. Cleanup uses its
        // current cell, then clears the manager after freeing that cell.
        owner = device_owner;
        if (owner) {
            WaveDirectSoundDevice* owned_device = *owner;
            if (owned_device) {
                owned_device->methods->release(owned_device);
                *owner = 0;
            }
            asm_free_004524a1(owner);
            device_owner = 0;
        }
        return -1;
    }

    Sound_SetPrimaryFormat_0044c7e0(16, 2, 44100, owner);
    device = *device_owner;
    stream_cursor = 0;
    WaveFormatImage format = {1, 2, 44100, 176400, 4, 16, 0};
    WaveBufferDescription description = {};
    description.size = sizeof description;
    description.flags = 0x8008;
    description.bytes = 0x8000;
    description.format = &format;
    WaveDirectSoundDevice* stream_device = device;
    if (stream_device->methods->create_buffer(stream_device, &description, &stream_buffer, 0) < 0)
        return -1;

    unsigned char* first;
    unsigned char* second;
    unsigned int first_bytes;
    unsigned int second_bytes;
    WaveSecondaryBuffer* buffer = stream_buffer;
    if (buffer->methods->lock(buffer, 0, 0x8000, &first, &first_bytes, &second, &second_bytes, 0) < 0)
        return -1;

    // The first span always receives 0x2000 dword stores. Reported lock
    // lengths and a possible second span do not change this clear.
    volatile unsigned int* clear = reinterpret_cast<volatile unsigned int*>(first);
    for (unsigned int word = 0; word < 0x2000; ++word)
        clear[word] = 0;
    buffer = stream_buffer;
    buffer->methods->unlock(buffer, first, first_bytes, second, second_bytes);
    buffer = stream_buffer;
    buffer->methods->play(buffer, 0, 0, 1);
    volume_a = 100;
    volume_b = 100;
    g_sound_set_timer(target_window, 0, 250, 0);
    window = target_window;

    for (int index = 0; index < 37; ++index) {
        if (g_sound_shutdown_state == 2)
            return -1;
        // This call intentionally uses the global manager, not this receiver.
        if (SoundWave_LoadPending_0043d390(index, &g_wave_sound_manager, g_sound_preload_names[index])) {
            g_wave_error_log.Append(g_sound_preload_error, g_sound_preload_names[index]);
            return -1;
        }
    }
    g_wave_error_log.Append(g_sound_initialize_ready);
    return 0;
}
