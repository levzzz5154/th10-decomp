// Behavioral recovery of the 786-byte initializer at 0x0043CD30. This typed
// method retains its ECX receiver and one stack window argument (RET 4).
#include "th10/platform/sound_wave_load.hpp"
#include <string.h>

typedef unsigned int (__stdcall* SoundSetTimer)(void* window, unsigned int id,
    unsigned int milliseconds, void* callback);

extern "C" {
    void __cdecl asm_free_004524a1(void* memory);
    int __stdcall Ordinal_11_00452170(const void* device_id,
        WaveDirectSoundDevice** output, void* outer);
    __declspec(noinline) int __stdcall Sound_SetPrimaryFormat_0044c7e0(unsigned short channels,
        unsigned int rate, unsigned short bits, WaveDirectSoundDevice** owner);
    extern SoundSetTimer g_sound_set_timer;
    extern WaveSoundManager g_wave_sound_manager;
    extern const char* g_sound_preload_names[37];
    extern char g_sound_initialize_error[];
    extern char g_sound_initialize_ready[];
    extern char g_sound_preload_error[];
}

extern "C" __declspec(noinline) int __stdcall NativeWave_LoadPending(WaveSoundManager*, int, const char*);

struct SoundDeviceOwner {
    WaveDirectSoundDevice* device;
    SoundDeviceOwner() : device(0) {}
    __forceinline int Configure(void* target_window, unsigned int level,
            unsigned short bits, unsigned short channels, unsigned int rate) {
        WaveDirectSoundDevice* current = device;
        if (current) {
            current->methods->release(current);
            device = 0;
        }
        int result = Ordinal_11_00452170(0, &device, 0);
        if (result >= 0) {
            current = device;
            result = current->methods->set_cooperative_level(current, target_window, level);
            if (result >= 0) {
                Sound_SetPrimaryFormat_0044c7e0(channels, rate, bits, &device);
                result = 0;
            }
        }
        return result;
    }
};

typedef char SoundDeviceOwnerSize[sizeof(SoundDeviceOwner) == 0x4 ? 1 : -1];
typedef char SoundDeviceOwnerDevice[offsetof(SoundDeviceOwner, device) == 0x0 ? 1 : -1];
typedef char SoundInitHandles[offsetof(WaveSoundManager, sound_handles) == 0x408 ? 1 : -1];
typedef char SoundInitStreamBuffer[offsetof(WaveSoundManager, stream_buffer) == 0x608 ? 1 : -1];
typedef char SoundInitWindow[offsetof(WaveSoundManager, window) == 0x60C ? 1 : -1];
typedef char SoundInitDeviceOwner[offsetof(WaveSoundManager, device_owner) == 0x610 ? 1 : -1];
typedef char SoundInitCursor[offsetof(WaveSoundManager, stream_cursor) == 0x618 ? 1 : -1];
typedef char SoundInitMusicHandles[offsetof(WaveSoundManager, music_handles) == 0x620 ? 1 : -1];
typedef char SoundInitVolumeA[offsetof(WaveSoundManager, volume_a) == 0x52C4 ? 1 : -1];
typedef char SoundInitVolumeB[offsetof(WaveSoundManager, volume_b) == 0x52C8 ? 1 : -1];
typedef char SoundInitCooperativeSlot[offsetof(WaveDeviceMethods, set_cooperative_level) == 0x18 ? 1 : -1];
typedef char SoundInitCreateBufferSlot[offsetof(WaveDeviceMethods, create_buffer) == 0xC ? 1 : -1];
typedef char SoundInitLockSlot[offsetof(WaveBufferMethods, lock) == 0x2C ? 1 : -1];
typedef char SoundInitPlaySlot[offsetof(WaveBufferMethods, play) == 0x30 ? 1 : -1];
typedef char SoundInitUnlockSlot[offsetof(WaveBufferMethods, unlock) == 0x4C ? 1 : -1];

#pragma code_seg(".text$0043cd30_fn")
__declspec(noinline) int WaveSoundManager::Initialize(void* target_window) {
    for (unsigned int index = 0; index < 128; ++index)
        sound_handles[index] = -1;
    for (unsigned int index = 0; index < 12; ++index)
        music_handles[index] = -1;

    SoundDeviceOwner* allocated = new SoundDeviceOwner;
    WaveDirectSoundDevice** owner = reinterpret_cast<WaveDirectSoundDevice**>(allocated);
    device_owner = owner;
    // Retail dereferences the newly allocated cell even if allocation failed.
    if (allocated->Configure(target_window, 2, 16, 2, 44100) < 0) {
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

    device = *device_owner;
    stream_cursor = 0;
    WaveBufferDescription description = {};
    WaveFormatImage format = {};
    description.size = sizeof description;
    description.flags = 0x8008;
    description.bytes = 0x8000;
    description.format = &format;
    format.extra_bytes = 0;
    format.tag = 1;
    format.channels = 2;
    format.sample_rate = 44100;
    format.average_bytes_per_second = 176400;
    format.block_alignment = 4;
    format.bits_per_sample = 16;
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
    memset(first, 0, 0x8000);
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
        if (NativeWave_LoadPending(&g_wave_sound_manager, index,
                                   g_sound_preload_names[index])) {
            g_wave_error_log.Append(g_sound_preload_error, g_sound_preload_names[index]);
            return -1;
        }
    }
    g_wave_error_log.Append(g_sound_initialize_ready);
    return 0;
}

#pragma code_seg()
