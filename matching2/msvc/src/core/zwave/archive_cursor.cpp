// 0x0044DD40: move an archive cursor back to the start of its entry, optionally past the entry header.
#include <string.h>
extern "C" unsigned long (__stdcall* imp_SetFilePointer)(void* file, long distance, long* distance_high, unsigned long method);
extern "C" int (__stdcall* imp_ReadFile)(void* file, void* buffer, unsigned long size, unsigned long* read, void* overlapped);
extern "C" int g_bgm_data_offset;

struct ArchiveEntry4 {
    unsigned char unknown_00[0x10];
    int offset;
    unsigned char unknown_14[4];
    int header_size;
    int size;
};
struct ArchiveCursor3 {
    unsigned char unknown_00[8];
    unsigned int size;
    unsigned char unknown_0c[0x70];
    unsigned char* memory;
    unsigned char* memory_base;
    unsigned char* memory_cursor;
    unsigned int memory_size;
    void* file;
    ArchiveEntry4* entry;
};

#pragma code_seg(".text$01accessor")
__declspec(noinline) long __stdcall Rewind2(ArchiveCursor3* cursor, bool skip_header) {
    if (cursor->memory) {
        cursor->memory_cursor = cursor->memory_base;
        if (cursor->entry->size > 0) cursor->memory_size = cursor->entry->size;
        if (skip_header && cursor->entry->header_size > 0) cursor->memory_cursor = cursor->memory_base + cursor->entry->header_size;
        return 0;
    }
    if (!cursor->file) return 0x800401F0;
    if (skip_header && cursor->entry->header_size > 0) {
        imp_SetFilePointer(cursor->file, cursor->entry->offset + cursor->entry->header_size + g_bgm_data_offset, 0, 0);
        cursor->size = cursor->entry->size - cursor->entry->header_size;
        return 0;
    }
    imp_SetFilePointer(cursor->file, cursor->entry->offset + g_bgm_data_offset, 0, 0);
    cursor->size = cursor->entry->size;
    return 0;
}
#pragma code_seg()
