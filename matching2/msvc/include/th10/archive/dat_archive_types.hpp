#ifndef TH10_ARCHIVE_DAT_ARCHIVE_TYPES_HPP
#define TH10_ARCHIVE_DAT_ARCHIVE_TYPES_HPP

#include "th10/platform/file.hpp"
#include <stddef.h>

struct DatArchiveEntry {
    const char* name;
    unsigned int offset;
    unsigned int uncompressed_size;
    unsigned int metadata;
};

struct DatArchive {
    DatArchiveEntry* entries;
    int entry_count;
    char* filename;
    FileInterface* file;

    void Close();
    void Reset();
    bool Open(const char* path);
    bool OpenResource(const char* resource_name);
    bool LoadIndex(const char* path);
};

typedef char DatArchiveEntry_must_be_16_bytes[
    sizeof(DatArchiveEntry) == 16 ? 1 : -1];
typedef char DatArchive_file_must_be_at_12[
    offsetof(DatArchive, file) == 12 ? 1 : -1];

typedef void (__fastcall *ArchiveEntryCallback)(DatArchiveEntry* entry);

extern "C" void __cdecl crt_free(void* memory);
extern "C" void __cdecl crt_free_startup(void* memory);
extern "C" void __stdcall crt_eh_vector_dtor(
    void* entries, unsigned int entry_size, int entry_count,
    ArchiveEntryCallback release);

#endif
