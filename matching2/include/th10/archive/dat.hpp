#pragma once

#include "th10/game/entity.hpp"

class FileInterface;

// Entry layout used by the archive index search at 0x00434F30.
struct DatEntry {
    const char* name;
    uint32_t offset;
    uint32_t uncompressed_size;
    uint32_t unknown;
};

struct DatArchiveHeader {
    uint32_t magic;
    uint32_t entry_list_size;
    uint32_t entry_list_compressed_size;
    uint32_t entry_count;
};

struct DatArchiveIndex {
    DatEntry* entries;
    int32_t entry_count;
};

// Retail archive owner used by 0x00434C20-0x004350D0.
struct DatArchive : DatArchiveIndex {
    char* filename;
    FileInterface* file;
};

void DatArchive_Initialize(DatArchive* archive);
void DatArchive_Close(DatArchive* archive);

bool DatArchive_Open(
    DatArchive* archive,
    FileInterface* owned_file,
    const char* path);

// Decode and install the index from archive->file (retail 0x00434F70).
// The caller retains ownership of the file and is responsible for cleanup
// when loading fails.
bool DatArchive_LoadIndex(DatArchive* archive, const char* path);

bool DatArchive_OpenFile(DatArchive* archive, const char* path);
bool DatArchive_OpenResource(DatArchive* archive, const char* resource_name);

uint8_t* DatArchive_Read(
    DatArchive* archive,
    const char* name,
    uint8_t* output);

const DatEntry* DatArchive_FindEntry(
    const DatArchiveIndex* archive, const char* name);

uint32_t DatArchive_FindSize(
    const DatArchiveIndex* archive, const char* name);

uint32_t DatEntry_GetCompressedSize(const DatEntry* entry);

uint8_t* DatArchive_DecodeEntryData(
    const DatEntry* entry,
    uint8_t* encrypted_data,
    uint8_t* output);

bool DatArchive_DecodeHeader(
    uint8_t encrypted_header[16], DatArchiveHeader* header);

DatEntry* DatArchive_ParseEntries(
    const uint8_t* packed_entries,
    uint32_t entry_count,
    uint32_t data_end_offset);

void DatArchive_FreeEntries(DatEntry* entries, uint32_t entry_count);
