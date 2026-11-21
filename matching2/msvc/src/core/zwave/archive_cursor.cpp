// 0x0044DD40: move an archive cursor back to the start of its entry, optionally past the intro/loop start.
#include <string.h>
extern "C" unsigned long (__stdcall* imp_SetFilePointer)(void* file, long distance, long* distance_high, unsigned long method);
extern "C" int (__stdcall* imp_ReadFile)(void* file, void* buffer, unsigned long size, unsigned long* read, void* overlapped);
extern "C" int g_bgm_data_offset;

struct MusicTrackRecord {
    unsigned char unknown_00[0x10];
    int offset;
    unsigned char unknown_14[4];
    int loop_start;
    int size;
};
struct MusicReadCursor {
    unsigned char unknown_00[8];
    unsigned int size;
    unsigned char unknown_0c[0x70];
    unsigned char* memory;
    unsigned char* memory_base;
    unsigned char* memory_cursor;
    unsigned int memory_size;
    void* file;
    MusicTrackRecord* entry;
};

#pragma code_seg(".text$01accessor")
__declspec(noinline) long __stdcall Rewind2(MusicReadCursor* cursor, bool skip_intro) {
    if (cursor->memory) {
        cursor->memory_cursor = cursor->memory_base;
        if (cursor->entry->size > 0) cursor->memory_size = cursor->entry->size;
        if (skip_intro && cursor->entry->loop_start > 0) cursor->memory_cursor = cursor->memory_base + cursor->entry->loop_start;
        return 0;
    }
    if (!cursor->file) return 0x800401F0;
    if (skip_intro && cursor->entry->loop_start > 0) {
        imp_SetFilePointer(cursor->file, cursor->entry->offset + cursor->entry->loop_start + g_bgm_data_offset, 0, 0);
        cursor->size = cursor->entry->size - cursor->entry->loop_start;
        return 0;
    }
    imp_SetFilePointer(cursor->file, cursor->entry->offset + g_bgm_data_offset, 0, 0);
    cursor->size = cursor->entry->size;
    return 0;
}
#pragma code_seg()
