#include <string.h>
#pragma intrinsic(memcpy)
#pragma code_seg(".text$05read")
extern "C" __declspec(noinline) int __stdcall ArchiveRead(
        MusicCursor* cursor, unsigned int requested,
        unsigned int destination, unsigned int* received) {
    if (cursor->buffered) {
        if (!cursor->position) return (int)0x800401F0u;
        if (received) *received = 0;
        unsigned int limit = cursor->memory_end;
        unsigned int begin = (unsigned int)cursor->base;
        unsigned int position = (unsigned int)cursor->position;
        if (position + requested > begin + limit)
            requested = begin - position + limit;
        memcpy((void*)destination, (void*)position, requested);
        cursor->position = (unsigned char*)((unsigned int)cursor->position + requested);
        if (received) *received = requested;
        return 0;
    } else {
    void* file = cursor->file;
    if (!file) return (int)0x800401F0u;
    if (!destination || !received) return (int)0x80070057u;
    unsigned int remaining = cursor->remaining;
    if (requested > remaining) requested = remaining;
    cursor->remaining = remaining - requested;
    ReadFile(file, (void*)destination, requested, &destination, 0);
    *received = destination;
    return 0;
    }
}
#pragma code_seg()
