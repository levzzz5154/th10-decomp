#pragma once

// One preloaded effect buffer (retail 0x0043D390). Split out of
// memory_file.hpp because it uses no Windows types, so a host that
// includes the real windows.h can still reach it.
struct SoundWaveFormat {
    unsigned short format_tag;
    unsigned short channels;
    unsigned int samples_per_second;
    unsigned int average_bytes_per_second;
    unsigned short block_align;
    unsigned short bits_per_sample;
    unsigned short extra_size;
};

struct SoundWaveLoadEnvironment {
    void* context;
    void (*release_buffer)(void* context, void* buffer);
    void (*wait_10ms)(void* context);
    int (*cancelled)(void* context);
    int (*create_buffer)(void* context, const SoundWaveFormat* format,
                         unsigned int pcm_bytes, unsigned int flags,
                         void** buffer_out);
    int (*lock_buffer)(void* context, void* buffer, unsigned int pcm_bytes,
                       unsigned char** first, unsigned int* first_bytes,
                       unsigned char** second, unsigned int* second_bytes);
    void (*unlock_buffer)(void* context, void* buffer, unsigned char* first,
                          unsigned int first_bytes, unsigned char* second,
                          unsigned int second_bytes);
    void (*release_owned_wave)(void* context, unsigned char* wave);
    void (*report_error)(void* context, const char* operation);
};

// 0x0043D390 - Consume one asynchronously supplied RIFF/WAVE image, replace
// the destination sound buffer, and copy the PCM data through one or two lock
// regions. The owned wave image is released on every parse/create/lock result.
int SoundWave_LoadPending(int enabled, void** buffer_slot,
                          unsigned char** pending_wave_slot,
                          const SoundWaveLoadEnvironment* environment);
