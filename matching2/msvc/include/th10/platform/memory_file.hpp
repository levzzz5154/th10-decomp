#pragma once

#include "th10/platform/file.hpp"

// Buffer-backed file owner used by the vtable at 0x0046F308.
class BufferFile : public FileInterface {
public:
    BufferFile();
    virtual ~BufferFile();

    virtual BYTE Open(const char* path, const char* mode);
    virtual void Close();
    virtual DWORD Read(void* destination, DWORD size);
    virtual BYTE Write(const void* source, DWORD size);
    virtual DWORD Tell() const;
    virtual DWORD GetSize() const;
    virtual BYTE Seek(LONG distance, DWORD origin);

protected:
    DWORD size_;
    BYTE* position_;
    BYTE* data_;
};

// Embedded Win32 RCDATA backend used by the vtable at 0x0046F328.
class ResourceFile : public BufferFile {
public:
    ResourceFile();
    virtual ~ResourceFile();

    virtual BYTE Open(const char* resource_name, const char* mode);
};

void ResourceFile_FillPalette(unsigned short* palette, unsigned int count,
                              unsigned int color);
const unsigned char* Resource_FindChunk(const unsigned char* data,
                                        unsigned int size, const char tag[4],
                                        unsigned int* payload_size);

struct MemoryFileLink {
    int parent;
    int left;
    int right;
};

void MemoryFile_RelinkChild(MemoryFileLink* links, unsigned int source,
                            unsigned int replacement);
void MemoryFile_ReplaceNode(MemoryFileLink* links, unsigned int source,
                            unsigned int replacement);
unsigned int MemoryFile_FindPredecessor(const MemoryFileLink* links,
                                        unsigned int node);
void MemoryFile_RemoveNode(MemoryFileLink* links, unsigned int node);
void ResourceWindow_Reset(void* window);


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

