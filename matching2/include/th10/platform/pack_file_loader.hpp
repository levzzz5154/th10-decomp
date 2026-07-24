// =============================================================================
// pack_file_loader.hpp - File loading surfaces (retail 0x0044B360, 0x0043A1C0)
// =============================================================================
#ifndef TH10_PLATFORM_PACK_FILE_LOADER_HPP
#define TH10_PLATFORM_PACK_FILE_LOADER_HPP

// Mounted archive entry (retail table DAT_00497990, count DAT_00497994).
struct PackFileEntry {
    const char* name;
    void* data;
    unsigned int size;
    unsigned int flags;
};

struct PackFileTable {
    const PackFileEntry* entries;
    unsigned int entry_count;
};

struct PackFileHooks {
    void* context;
    void (*lock)(void* context);   // EnterCS(&DAT_004922A4) + DAT_0049231E
    void (*unlock)(void* context);
    void* (*alloc)(void* context, unsigned int size);
    void (*release)(void* context, void* memory);
    // Decompress/copy one table entry into `buffer` (retail 0x00434DD0).
    void (*extract_entry)(void* context, const PackFileEntry* entry,
                          void* buffer);
    void* (*open_for_read)(void* context, const char* name);
    unsigned int (*file_size)(void* context, void* handle);
    int (*read)(void* context, void* handle, void* buffer,
                unsigned int size);
    void (*close)(void* context, void* handle);
};

void* PackFile_Load(const char* name, unsigned int* size_out, int from_disk,
                    const PackFileTable* table, const PackFileHooks* hooks);

struct ExecutableChecksumHooks {
    void* context;
    unsigned int (*module_file_name)(void* context, char* buffer,
                                     unsigned int capacity);
    void* (*load_file)(void* context, const char* name,
                       unsigned int* size_out);
    void (*release)(void* context, void* memory);
};

int Executable_Checksum(unsigned int* checksum_out, unsigned int* size_out,
                        const ExecutableChecksumHooks* hooks);

#endif // TH10_PLATFORM_PACK_FILE_LOADER_HPP
