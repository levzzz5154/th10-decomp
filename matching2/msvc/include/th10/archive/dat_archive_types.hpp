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

extern "C" void __cdecl asm_free_00452422(void* memory);
extern "C" void __cdecl asm_free_004524a1(void* memory);
extern "C" void __stdcall asm_eh_vector_destructor_iterator_004525ff(
    void* entries, unsigned int entry_size, int entry_count,
    ArchiveEntryCallback release);

#endif
