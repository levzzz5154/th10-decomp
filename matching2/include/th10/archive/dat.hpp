#pragma once

#include "th10/game/entity.hpp"

// Entry layout used by the archive index search at 0x00434F30.
struct DatEntry {
    const char* name;
    uint32_t offset;
    uint32_t compressed_size;
    uint32_t uncompressed_size;
};

struct DatArchiveIndex {
    DatEntry* entries;
    int32_t entry_count;
};

const DatEntry* DatArchive_FindEntry(
    const DatArchiveIndex* archive, const char* name);
