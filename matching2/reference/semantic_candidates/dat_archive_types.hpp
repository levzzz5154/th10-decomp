#ifndef TH10_SEMANTIC_DAT_ARCHIVE_TYPES_HPP
#define TH10_SEMANTIC_DAT_ARCHIVE_TYPES_HPP

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
};

struct DatCryptParameters {
    unsigned char key;
    unsigned char step;
    int block_size;
    int byte_limit;
};

typedef char DatArchiveEntry_must_be_16_bytes[sizeof(DatArchiveEntry) == 16 ? 1 : -1];
typedef char DatArchive_file_must_be_at_12[offsetof(DatArchive, file) == 12 ? 1 : -1];
typedef char DatCryptParameters_must_be_12_bytes[sizeof(DatCryptParameters) == 12 ? 1 : -1];

extern "C" const DatCryptParameters g_dat_read_crypt_parameters[8];
extern "C" DatArchiveEntry* __stdcall Archive_FindEntry_00434f30(
    DatArchive* archive, const char* name);
extern "C" void* __cdecl asm_malloc_00452706(unsigned int size);
extern "C" void __cdecl asm_free_00452422(void* memory);
extern "C" void __cdecl asm_free_004524a1(void* memory);
// Single-pointer fastcall uses ECX, matching the retail vector callbacks.
typedef void (__fastcall *ArchiveEntryCallback)(DatArchiveEntry* entry);
extern "C" void __fastcall ArchiveEntry_Construct_004352c0(DatArchiveEntry* entry);
extern "C" void __fastcall ArchiveEntry_Release_00435250(DatArchiveEntry* entry);
extern "C" void __stdcall asm_eh_vector_constructor_iterator_0045252d(
    void* entries, unsigned int entry_size, int entry_count,
    ArchiveEntryCallback construct, ArchiveEntryCallback release);
extern "C" void __stdcall asm_eh_vector_destructor_iterator_004525ff(
    void* entries, unsigned int entry_size, int entry_count,
    ArchiveEntryCallback release);
extern "C" void __stdcall DatArchive_Close_00434d10(DatArchive* archive);
extern "C" unsigned char* __stdcall Dat_Decrypt_0044b0d0(
    unsigned char* data, int size, unsigned char key, unsigned char step,
    int block_size, int byte_limit);
extern "C" unsigned char* __stdcall DecompressDatLzss_00435dc0(
    const unsigned char* source, int source_length,
    unsigned char* output, unsigned int output_capacity);

#endif
