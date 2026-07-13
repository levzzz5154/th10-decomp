#pragma once

#include "th10/game/entity.hpp"

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

const DatEntry* DatArchive_FindEntry(
    const DatArchiveIndex* archive, const char* name);

bool DatArchive_DecodeHeader(
    uint8_t encrypted_header[16], DatArchiveHeader* header);

DatEntry* DatArchive_ParseEntries(
    const uint8_t* packed_entries,
    uint32_t entry_count,
    uint32_t data_end_offset);

void DatArchive_FreeEntries(DatEntry* entries, uint32_t entry_count);
