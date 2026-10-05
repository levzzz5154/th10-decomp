// Behavioral recovery of 0x0043D390 (684 bytes). The public fastcall entry
// matches retail: index in ECX, manager in EDX, filename on the stack.
// Equivalent MSVC recovery: the sole residual is ADD -12 versus SUB 12.
// Chunk/log definitions below establish ABI context; calls bind to retail owners.
#include "th10/platform/memory_file.hpp"

#include "sound_wave_load_0043d390.hpp"

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

#include <string.h>
#pragma intrinsic(memcpy)
__declspec(noinline) const unsigned char* FindWaveChunk(
    const unsigned char*, unsigned int*, unsigned int, const char[4]);
#pragma code_seg(".text$03wave")
extern "C" __declspec(noinline) int __fastcall SoundWave_LoadPending_0043d390(
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

    if (strncmp(reinterpret_cast<const char*>(wave), g_wave_riff_tag, 4) != 0) {
        g_wave_error_log.Append(g_wave_invalid_riff_message, filename);
        entry_free_00452422(wave);
        return -1;
    }
    const unsigned char* chunks = wave + 4;
    unsigned int chunk_bytes = *reinterpret_cast<const unsigned int*>(chunks);
    chunks += 4;
    if (strncmp(reinterpret_cast<const char*>(chunks), g_wave_wave_tag, 4) != 0) {
        g_wave_error_log.Append(g_wave_invalid_format_message, filename);
        entry_free_00452422(wave);
        return -1;
    }
    chunks += 4;
    chunk_bytes -= 12;
    unsigned int payload_size;
    const unsigned char* format_bytes = FindWaveChunk(chunks, &payload_size, chunk_bytes, g_wave_format_tag);
    if (!format_bytes) {
        g_wave_error_log.Append(g_wave_invalid_format_message, filename);
        entry_free_00452422(wave);
        return -1;
    }
    WaveFormatImage format;
    memcpy(&format, format_bytes, sizeof format);
    const unsigned char* pcm = FindWaveChunk(chunks, &payload_size, chunk_bytes, g_wave_data_tag);
    if (!pcm) {
        g_wave_error_log.Append(g_wave_invalid_format_message, filename);
        entry_free_00452422(wave);
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
    memcpy(first, pcm, first_bytes);
    if (second_bytes)
        memcpy(second, pcm + first_bytes, second_bytes);
    buffer = *slot;
    buffer->methods->unlock(buffer, first, first_bytes, second, second_bytes);
    entry_free_00452422(wave);
    return 0;
}
#pragma code_seg()

#include "th10/platform/memory_file.hpp"

extern "C" int __cdecl strncmp(const char*, const char*, unsigned int);

struct ResourceChunkHeader {
    char tag[4];
    unsigned int payload_size;
};

// 0x0043D250. Walk packed resource chunks and return the matching payload.
// The original advances by exactly header + payload bytes, without padding
// or a separate check for a chunk extending beyond the supplied size.
#pragma code_seg(".text$01chunk")
__declspec(noinline) const unsigned char* FindWaveChunk(
    const unsigned char* data, unsigned int* payload_size, unsigned int size,
    const char tag[4]) {
    if (size > 0) {
        do {
            const ResourceChunkHeader* header =
                reinterpret_cast<const ResourceChunkHeader*>(data);
            *payload_size = header->payload_size;
            if (strncmp(header->tag, tag, sizeof header->tag) == 0) {
                return data + sizeof(ResourceChunkHeader);
            }
            size -= sizeof(ResourceChunkHeader) + *payload_size;
            data += sizeof(ResourceChunkHeader) + *payload_size;
        } while (size);
    }
    return 0;
}
#pragma code_seg()

// 0x0044B810..0x0044B8D8: TextLog::Append
//
// Formats into an 8 KiB staging buffer while holding the text-log critical
// section, then appends the result when it fits in the log's 8 KiB ring.
#include <stdarg.h>
#include <string.h>
#include "th10/platform/text_log.hpp"
#include "th10/platform/thread_sync.hpp"

extern "C" int __cdecl asm_vsprintf_004524a6(
    char* buffer, const char* format, char* arguments);


#pragma code_seg(".text$05log")
__declspec(noinline) char* TextLog_0044b810::Append(char* format, ...) {
    char staging[0x2000];
    va_list arguments;
    va_start(arguments, format);

    EnterCriticalSection(&g_thread_synchronization.critical_sections[3]);
    ++g_thread_synchronization.text_log_lock_depth;
    asm_vsprintf_004524a6(staging, format, arguments);

    unsigned int length = strlen(staging);
    char* destination = cursor;
    if ((unsigned int)(destination + length) <
        (unsigned int)((char*)this + 0x1FFF)) {
        strcpy(cursor, staging);
        cursor = (char*)((unsigned int)cursor + length);
        *cursor = 0;
    }

    LeaveCriticalSection(&g_thread_synchronization.critical_sections[3]);
    --g_thread_synchronization.text_log_lock_depth;
    return format;
}
#pragma code_seg()

// Compiler entry preserves the public fastcall boundary via an escaping pointer.
typedef int (__fastcall *WaveLoadCallback)(int, WaveSoundManager*, const char*);
WaveLoadCallback volatile WaveLoadEntryCallback = SoundWave_LoadPending_0043d390;
extern "C" int __stdcall WaveLoadEntry(int index, WaveSoundManager* manager, const char* filename) {
    return WaveLoadEntryCallback(index, manager, filename);
}
