// 0x0044DBF0: open an archive cursor on one archive entry, either from the
// archive file on disk or from an archive already held in memory.
extern "C" void* (__stdcall* imp_CreateFileA)(const char* path, unsigned long access, unsigned long share, void* security, unsigned long disposition, unsigned long flags, void* template_file);
extern "C" unsigned long (__stdcall* imp_SetFilePointer)(void* file, long distance, long* distance_high, unsigned long method);
extern "C" int g_bgm_data_offset;

struct ArchiveEntry_0044dbf0 {
    unsigned char unknown_00[0x10];
    int offset;
    unsigned char unknown_14[8];
    int size;
};
struct ArchiveCursor_0044dbf0 {
    unsigned char unknown_00[8];
    int size;
    unsigned char unknown_0c[0x20];
    int remaining;
    unsigned char unknown_30[0x48];
    int mode;
    unsigned char* memory;
    unsigned char* memory_base;
    unsigned char* memory_cursor;
    int memory_size;
    void* file;
    ArchiveEntry_0044dbf0* entry;
};

#pragma code_seg(".text$01accessor")
__declspec(noinline) long __stdcall OpenCursor(ArchiveCursor_0044dbf0* cursor, int mode, const char* path, ArchiveEntry_0044dbf0* entry) {
    cursor->mode = mode;
    cursor->memory = 0;
    if (mode == 1) {
        if (!path) return 0x80070057;
        cursor->file = imp_CreateFileA(path, 0x80000000, 1, 0, 3, 0x08000080, 0);
        if (cursor->file == (void*)-1) return 0x80004005;
        cursor->entry = entry;
        if (cursor->memory) {
            cursor->memory_cursor = cursor->memory_base;
            if (entry->size > 0) cursor->memory_size = entry->size;
        } else if (cursor->file) {
            imp_SetFilePointer(cursor->file, entry->offset + g_bgm_data_offset, 0, 0);
            cursor->size = cursor->entry->size;
        }
        cursor->remaining = cursor->size;
    }
    return 0;
}
#pragma code_seg()
