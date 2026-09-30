// Behavioral recovery of 0x0043D390 (684 bytes). The public fastcall entry
// matches retail: index in ECX, manager in EDX, filename on the stack.
// Native MSVC frame/byte matching and the chunk/log helper ABIs are pending.
#include "th10/platform/memory_file.hpp"

#include "sound_wave_types.hpp"

typedef void (__stdcall* WaveSleep)(unsigned int milliseconds);
extern "C" {
    void __cdecl entry_free_00452422(void* memory);
    int __cdecl strncmp(const char*, const char*, unsigned int);
    extern WaveSleep g_sound_sleep;
    extern char g_wave_invalid_riff_message[];
    extern char g_wave_invalid_format_message[];
    extern const char g_wave_riff_tag[];
    extern const char g_wave_wave_tag[];
    extern const char g_wave_format_tag[4];
    extern const char g_wave_data_tag[4];
}

namespace {
// Preserve the forward dword snapshots used by the two retail REP copies,
// including overlap. memcpy/memmove have different overlap contracts.
void CopyWaveRegion(unsigned char* destination, const unsigned char* source,
                    unsigned int size) {
    while (size >= 4) {
        unsigned int word = source[0] | (static_cast<unsigned int>(source[1]) << 8) |
            (static_cast<unsigned int>(source[2]) << 16) | (static_cast<unsigned int>(source[3]) << 24);
        destination[0] = static_cast<unsigned char>(word);
        destination[1] = static_cast<unsigned char>(word >> 8);
        destination[2] = static_cast<unsigned char>(word >> 16);
        destination[3] = static_cast<unsigned char>(word >> 24);
        source += 4;
        destination += 4;
        size -= 4;
    }
    while (size--)
        *destination++ = *source++;
}
}

extern "C" int __fastcall SoundWave_LoadPending_0043d390(
        int index, WaveSoundManager* manager, const char* filename) {
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

    char* error = g_wave_invalid_riff_message;
    if (strncmp(reinterpret_cast<const char*>(wave), g_wave_riff_tag, 4) == 0) {
        const unsigned int chunk_bytes = *reinterpret_cast<const unsigned int*>(wave + 4) - 12;
        error = g_wave_invalid_format_message;
        if (strncmp(reinterpret_cast<const char*>(wave + 8), g_wave_wave_tag, 4) == 0) {
            unsigned int payload_size;
            const unsigned char* format_bytes = Resource_FindChunk(
                wave + 12, chunk_bytes, g_wave_format_tag, &payload_size);
            if (format_bytes) {
                // Always read 18 bytes, even when the fmt chunk claims fewer.
                WaveFormatImage format = *reinterpret_cast<const WaveFormatImage*>(format_bytes);
                const unsigned char* pcm = Resource_FindChunk(
                    wave + 12, chunk_bytes, g_wave_data_tag, &payload_size);
                if (pcm) {
                    const unsigned int pcm_bytes = payload_size;
                    WaveBufferDescription description = {};
                    description.size = sizeof description;
                    description.flags = 0x80C8;
                    description.bytes = pcm_bytes;
                    description.format = &format;
                    WaveDirectSoundDevice* device = manager->device;
                    if (device->methods->create_buffer(device, &description, slot, 0) < 0) {
                        entry_free_00452422(wave);
                        return -1;
                    }
                    unsigned char* first;
                    unsigned char* second;
                    unsigned int first_bytes;
                    unsigned int second_bytes;
                    WaveSecondaryBuffer* buffer = *slot;
                    if (buffer->methods->lock(buffer, 0, pcm_bytes, &first, &first_bytes,
                                             &second, &second_bytes, 0) < 0) {
                        entry_free_00452422(wave);
                        return -1;
                    }
                    CopyWaveRegion(first, pcm, first_bytes);
                    if (second_bytes)
                        CopyWaveRegion(second, pcm + first_bytes, second_bytes);
                    // Lock or the copies can change the slot; retail reloads it.
                    buffer = *slot;
                    buffer->methods->unlock(buffer, first, first_bytes, second, second_bytes);
                    entry_free_00452422(wave);
                    return 0;
                }
            }
        }
    }
    g_wave_error_log.Append(error, filename);
    entry_free_00452422(wave);
    return -1;
}
