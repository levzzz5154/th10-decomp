// 0x0044DD40: move an archive cursor back to the start of its entry, optionally past the entry header.
#include <string.h>
extern "C" unsigned long (__stdcall* data_004660c8)(void* file, long distance, long* distance_high, unsigned long method);
extern "C" int (__stdcall* data_004660d0)(void* file, void* buffer, unsigned long size, unsigned long* read, void* overlapped);
extern "C" int data_004977a4;

struct ArchiveEntry_0044dd40 {
    unsigned char unknown_00[0x10];
    int offset;
    unsigned char unknown_14[4];
    int header_size;
    int size;
};
struct ArchiveCursor_0044dd40 {
    unsigned char unknown_00[8];
    unsigned int size;
    unsigned char unknown_0c[0x70];
    unsigned char* memory;
    unsigned char* memory_base;
    unsigned char* memory_cursor;
    unsigned int memory_size;
    void* file;
    ArchiveEntry_0044dd40* entry;
};

#pragma code_seg(".text$01accessor")
__declspec(noinline) long __stdcall Rewind_0044dd40(ArchiveCursor_0044dd40* cursor, bool skip_header) {
    if (cursor->memory) {
        cursor->memory_cursor = cursor->memory_base;
        if (cursor->entry->size > 0) cursor->memory_size = cursor->entry->size;
        if (skip_header && cursor->entry->header_size > 0) cursor->memory_cursor = cursor->memory_base + cursor->entry->header_size;
        return 0;
    }
    if (!cursor->file) return 0x800401F0;
    if (skip_header && cursor->entry->header_size > 0) {
        data_004660c8(cursor->file, cursor->entry->offset + cursor->entry->header_size + data_004977a4, 0, 0);
        cursor->size = cursor->entry->size - cursor->entry->header_size;
        return 0;
    }
    data_004660c8(cursor->file, cursor->entry->offset + data_004977a4, 0, 0);
    cursor->size = cursor->entry->size;
    return 0;
}
#pragma code_seg()
