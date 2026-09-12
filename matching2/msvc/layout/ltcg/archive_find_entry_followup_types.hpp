#pragma once

// Task-local archive layouts and retail custom-call adapters.  These are
// compiler context for the focused native-LTCG probe, never selected code.
struct ArchiveFindEntryRecord {
    const char* name;
    unsigned int offset;
    unsigned int uncompressed_size;
    unsigned int reserved;
};

struct ArchiveFindEntryIndex {
    ArchiveFindEntryRecord* entries;
    int entry_count;
};

static inline int archive_find_stricmp(const char* left, const char* right) {
    return reinterpret_cast<int (__cdecl *)(const char*, const char*)>(
        &asm_stricmp_0046054e)(left, right);
}

ArchiveFindEntryRecord* DatArchive_FindEntry(
    ArchiveFindEntryIndex* archive, const char* name);
