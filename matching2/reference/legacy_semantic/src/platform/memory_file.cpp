#include "th10/platform/memory_file.hpp"


// 0x0043D250 - Walk length-prefixed four-byte resource chunks.
const unsigned char* Resource_FindChunk(const unsigned char* data,
                                        unsigned int size, const char tag[4],
                                        unsigned int* payload_size) {
    while (size >= 8) {
        unsigned int length = *(const unsigned int*)(data + 4);
        if (data[0] == (unsigned char)tag[0] &&
            data[1] == (unsigned char)tag[1] &&
            data[2] == (unsigned char)tag[2] &&
            data[3] == (unsigned char)tag[3]) {
            if (payload_size != 0)
                *payload_size = length;
            return data + 8;
        }
        if (length > size - 8)
            break;
        data += length + 8;
        size -= length + 8;
    }
    if (payload_size != 0)
        *payload_size = 0;
    return 0;
}
#include "th10/archive/resource_manager.hpp"

extern "C" void* __stdcall SelectObject(void*, void*);
extern "C" int __stdcall DeleteDC(void*);
extern "C" int __stdcall DeleteObject(void*);

extern "C" void* __cdecl _malloc(DWORD size);
extern "C" void __cdecl _free(void* memory);
extern "C" void* memcpy(
    void* destination, const void* source, std::size_t size);

BufferFile::BufferFile() : size_(0), position_(0), data_(0) {
}

// 0x00436260 - Replace one child link while preserving its parent's branch.
void MemoryFile_RelinkChild(MemoryFileLink* links, unsigned int source,
                            unsigned int replacement) {
    const int parent = links[source].parent;
    links[replacement].parent = parent;
    if (links[parent].left == (int)source)
        links[parent].left = (int)replacement;
    else
        links[parent].right = (int)replacement;
    links[source].parent = 0;
}

// 0x004362B0 - Replace a node and reconnect both of its child branches.
void MemoryFile_ReplaceNode(MemoryFileLink* links, unsigned int source,
                            unsigned int replacement) {
    const int parent = links[source].parent;
    if (links[parent].left == (int)source)
        links[parent].left = (int)replacement;
    else
        links[parent].right = (int)replacement;
    links[replacement] = links[source];
    links[links[replacement].left].parent = (int)replacement;
    links[links[replacement].right].parent = (int)replacement;
    links[source].parent = 0;
}

// 0x00436330 - Find the rightmost node in this node's left branch.
unsigned int MemoryFile_FindPredecessor(const MemoryFileLink* links,
                                        unsigned int node) {
    unsigned int predecessor = (unsigned int)links[node].left;
    unsigned int next = (unsigned int)links[predecessor].right;
    while (next != 0) {
        predecessor = next;
        next = (unsigned int)links[predecessor].right;
    }
    return predecessor;
}

// 0x00436210 - Remove a linked tree node, using its in-order predecessor when
// both branches are populated. Index zero is the retail null-link sentinel.
void MemoryFile_RemoveNode(MemoryFileLink* links, unsigned int node) {
    if (links[node].parent == 0)
        return;

    const unsigned int right = (unsigned int)links[node].right;
    if (right == 0) {
        MemoryFile_RelinkChild(
            links, node, (unsigned int)links[node].left);
        return;
    }

    if (links[node].left == 0) {
        MemoryFile_RelinkChild(links, node, right);
        return;
    }

    const unsigned int predecessor =
        MemoryFile_FindPredecessor(links, node);
    MemoryFile_RemoveNode(links, predecessor);
    MemoryFile_ReplaceNode(links, node, predecessor);
}

// 0x00436A30 - Release the optional GDI surface owned by a resource window.
void ResourceWindow_Reset(void* window) {
    uint8_t* bytes = (uint8_t*)window;
    void* dc = *(void**)(bytes + 0x114);
    if (dc == 0)
        return;
    SelectObject(dc, *(void**)(bytes + 0x118));
    DeleteDC(dc);
    DeleteObject(*(void**)(bytes + 0x11c));
    *(uint32_t*)(bytes + 0x100) = 0xFFFFFFFF;
    *(uint32_t*)(bytes + 0x104) = 0;
    *(uint32_t*)(bytes + 0x108) = 0;
    *(uint32_t*)(bytes + 0x114) = 0;
    *(uint32_t*)(bytes + 0x118) = 0;
    *(uint32_t*)(bytes + 0x11c) = 0;
    *(uint32_t*)(bytes + 0x120) = 0;
}

// 0x004363C0 - Release the owned byte buffer and restore the base vtable.
__declspec(noinline) BufferFile::~BufferFile() {
    Close();
}

// 0x00436400 - Resolve a path through the registered archive/file manager.
BYTE BufferFile::Open(const char* path, const char*) {
    Close();
    data_ = Resource_LoadFile(path, 0);
    size_ = Resource_GetFileSize(path);
    position_ = data_;
    return (BYTE)(data_ != 0);
}

// 0x00436430 - Release and reset a buffer-backed file.
void BufferFile::Close() {
    if (data_) {
        _free(data_);
        data_ = 0;
    }
    data_ = 0;
    size_ = 0;
    position_ = 0;
}

// 0x00436460 - Read up to the remaining byte count.
DWORD BufferFile::Read(void* destination, DWORD requested) {
    DWORD remaining = (DWORD)((data_ + size_) - position_);
    if (remaining >= requested) {
        memcpy(destination, position_, requested);
        position_ += requested;
        return requested;
    }
    if (remaining != 0) {
        memcpy(destination, position_, remaining);
        position_ += remaining;
        return remaining;
    }
    return 0;
}

// 0x00436370 - Buffer files are read-only.
BYTE BufferFile::Write(const void*, DWORD) {
    return 0;
}

// 0x004364D0
DWORD BufferFile::Tell() const {
    return (DWORD)(position_ - data_);
}

// 0x004364E0
DWORD BufferFile::GetSize() const {
    return size_;
}

// 0x004364F0 - Retail seek rules use strict end bounds.
BYTE BufferFile::Seek(LONG distance, DWORD origin) {
    switch (origin) {
    case 0:
        goto from_start;
    case 1: {
        DWORD remaining = (DWORD)((data_ + size_) - position_);
        if ((LONG)remaining <= distance) goto failed;
        position_ += distance;
        return 1;
    }
    case 2: {
        if (distance > 0) goto failed;
        DWORD magnitude = distance < 0 ? (DWORD)-distance : (DWORD)distance;
        if (magnitude >= size_) goto failed;
        position_ = data_ + size_ + distance;
        return 1;
    }
    default:
        goto failed;
    }

failed:
    return 0;

from_start:
    if (distance < 0 || (DWORD)distance >= size_) goto failed;
    position_ = data_ + distance;
    return 1;
}


// Historical approximate model of 0x0043D390, not a faithful retail recovery:
// it changes chunk-count arithmetic, bounds-checks/zero-fills the format, and
// abstracts the volatile pending handoff. The tested complete candidate is
// reference/semantic_candidates/sound_wave_load.cpp; see its recovery note.
// 0x0043D390 - Build one secondary sound buffer from an owned RIFF/WAVE image.
int SoundWave_LoadPending(int enabled, void** buffer_slot,
                          unsigned char** pending_wave_slot,
                          const SoundWaveLoadEnvironment* environment) {
    if (enabled == 0) {
        return 0;
    }
    if (*buffer_slot != 0) {
        environment->release_buffer(environment->context, *buffer_slot);
        *buffer_slot = 0;
    }
    while (*pending_wave_slot == 0) {
        environment->wait_10ms(environment->context);
        if (environment->cancelled(environment->context) != 0) {
            return 0;
        }
    }

    unsigned char* wave = *pending_wave_slot;
    *pending_wave_slot = 0;
    if (wave == 0) {
        return -1;
    }

    int result = -1;
    const unsigned int riff_size = *(const unsigned int*)(wave + 4);
    if (wave[0] != 'R' || wave[1] != 'I' || wave[2] != 'F' || wave[3] != 'F') {
        environment->report_error(environment->context, "RIFF");
    } else if (wave[8] != 'W' || wave[9] != 'A' || wave[10] != 'V' ||
               wave[11] != 'E') {
        environment->report_error(environment->context, "WAVE");
    } else {
        const unsigned int chunk_bytes = riff_size >= 4 ? riff_size - 4 : 0;
        unsigned int format_bytes = 0;
        const unsigned char* format_data =
            Resource_FindChunk(wave + 12, chunk_bytes, "fmt ", &format_bytes);
        unsigned int pcm_bytes = 0;
        const unsigned char* pcm =
            Resource_FindChunk(wave + 12, chunk_bytes, "data", &pcm_bytes);
        if (format_data == 0 || format_bytes < 16 || pcm == 0) {
            environment->report_error(environment->context, "WAVE chunks");
        } else {
            SoundWaveFormat format = {};
            const unsigned int copy_bytes =
                format_bytes < sizeof(format) ? format_bytes : sizeof(format);
            memcpy(&format, format_data, copy_bytes);
            if (environment->create_buffer(environment->context, &format,
                                           pcm_bytes, 0x80C8u,
                                           buffer_slot) >= 0) {
                unsigned char* first = 0;
                unsigned char* second = 0;
                unsigned int first_bytes = 0;
                unsigned int second_bytes = 0;
                if (environment->lock_buffer(
                        environment->context, *buffer_slot, pcm_bytes, &first,
                        &first_bytes, &second, &second_bytes) >= 0) {
                    memcpy(first, pcm, first_bytes);
                    if (second_bytes != 0) {
                        memcpy(second, pcm + first_bytes, second_bytes);
                    }
                    environment->unlock_buffer(
                        environment->context, *buffer_slot, first, first_bytes,
                        second, second_bytes);
                    result = 0;
                }
            }
        }
    }
    environment->release_owned_wave(environment->context, wave);
    return result;
}
