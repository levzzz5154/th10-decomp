// Complete compiler context for the maintained WAVE loader at 0x0043D390.
// Logical inputs are manager, index and filename; native LTCG derives the
// retail index ECX / manager EDX / filename stack handoff, RET 4.
#include "th10/platform/memory_file.hpp"

#include "th10/platform/sound_wave_load.hpp"

typedef void (__stdcall* WaveSleep)(unsigned int milliseconds);
extern "C" {
    void __cdecl crt_free(void* memory);
    int __cdecl strncmp(const char*, const char*, unsigned int);
    extern WaveSleep g_sound_sleep;
    extern char g_wave_invalid_riff_message[];
    extern char g_wave_invalid_format_message[];
    extern const char g_wave_riff_tag[];
    extern const char g_wave_wave_tag[];
    extern const char g_wave_format_tag[4];
    extern const char g_wave_data_tag[4];
}

#include <string.h>
#pragma intrinsic(memcpy)
__declspec(noinline) const unsigned char* FindWaveChunk(
    const unsigned char*, unsigned int*, unsigned int, const char[4]);
#pragma code_seg(".text$0043d390_fn")
extern "C" __declspec(noinline) int __stdcall NativeWave_LoadPending(
        WaveSoundManager* manager, int index, const char* filename) {
    if (!manager->device_owner)
        return 0;

    WaveSecondaryBuffer** slot = &manager->secondary_buffers[index];
    if (*slot) {
        (*slot)->methods->release(*slot);
        *slot = 0;
    }
    if (!manager->pending_wave[index]) {
        // Retail caches the imported Sleep address once before waiting.
        const WaveSleep wait = g_sound_sleep;
        do {
            wait(10);
            if (g_sound_shutdown_state == 2)
                return 0;
        } while (!manager->pending_wave[index]);
    }
    // The second volatile read retains the handoff race after polling.
    unsigned char* wave = manager->pending_wave[index];
    manager->pending_wave[index] = 0;
    if (!wave)
        return -1;

    if (strncmp(reinterpret_cast<const char*>(wave), g_wave_riff_tag, 4) != 0) {
        g_wave_error_log.Append(g_wave_invalid_riff_message, filename);
        crt_free(wave);
        return -1;
    }
    const unsigned char* chunks = wave + 4;
    const unsigned int chunk_bytes = *reinterpret_cast<const unsigned int*>(chunks);
    chunks += 4;
    if (strncmp(reinterpret_cast<const char*>(chunks), g_wave_wave_tag, 4) != 0) {
        g_wave_error_log.Append(g_wave_invalid_format_message, filename);
        crt_free(wave);
        return -1;
    }
    chunks += 4;
    // Retail subtracts the complete 12-byte RIFF header from the stored length.
    unsigned int payload_size;
    const unsigned char* format_bytes = FindWaveChunk(chunks, &payload_size, chunk_bytes - 12, g_wave_format_tag);
    if (!format_bytes) {
        g_wave_error_log.Append(g_wave_invalid_format_message, filename);
        crt_free(wave);
        return -1;
    }
    WaveFormatImage format;
    memcpy(&format, format_bytes, sizeof format);
    const unsigned char* pcm = FindWaveChunk(chunks, &payload_size, chunk_bytes - 12, g_wave_data_tag);
    if (!pcm) {
        g_wave_error_log.Append(g_wave_invalid_format_message, filename);
        crt_free(wave);
        return -1;
    }
    const unsigned int pcm_bytes = payload_size;
    WaveBufferDescription description = {};
    description.size = sizeof description;
    description.flags = 0x80C8;
    description.bytes = pcm_bytes;
    description.format = &format;
    WaveDirectSoundDevice* device = manager->device;
    if (device->methods->create_buffer(device, &description, slot, 0) < 0) {
        crt_free(wave);
        return -1;
    }
    unsigned char* first;
    unsigned char* second;
    unsigned int first_bytes;
    unsigned int second_bytes;
    WaveSecondaryBuffer* buffer = *slot;
    if (buffer->methods->lock(buffer, 0, pcm_bytes, &first, &first_bytes,
                             &second, &second_bytes, 0) < 0) {
        crt_free(wave);
        return -1;
    }
    memcpy(first, pcm, first_bytes);
    if (second_bytes)
        memcpy(second, pcm + first_bytes, second_bytes);
    buffer = *slot;
    buffer->methods->unlock(buffer, first, first_bytes, second, second_bytes);
    crt_free(wave);
    return 0;
}
#pragma code_seg()
