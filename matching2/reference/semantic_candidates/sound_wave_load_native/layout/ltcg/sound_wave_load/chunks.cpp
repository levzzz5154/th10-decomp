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
