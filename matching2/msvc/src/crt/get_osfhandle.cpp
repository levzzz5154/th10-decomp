struct FileEntry { int handle; unsigned char flags; unsigned char padding[31]; };
extern "C" unsigned int g_crt_handle_count;
extern "C" FileEntry* g_crt_file_table[];
extern "C" int* __cdecl crt_errno();
extern "C" unsigned int* __cdecl crt_doserrno();

extern "C" int __cdecl crt_get_osfhandle(int file) {
    if (static_cast<unsigned int>(file) < g_crt_handle_count) {
        FileEntry* entry = &g_crt_file_table[file >> 5][file & 0x1f];
        if (entry->flags & 1) return entry->handle;
    }
    *crt_errno() = 9;
    *crt_doserrno() = 0;
    return -1;
}
