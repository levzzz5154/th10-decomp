#pragma once

#include "th10/platform/file.hpp"
#include "th10/util/heap.hpp"

// Layout shared by DatArchive_Reset and DatArchive_Close. The index entries
// use a HeapBuffer as their first word so the retail array callback can free
// and clear each entry name through HeapBuffer_Release.
struct DatArchiveEntry_00434d10 {
    HeapBuffer name;
    unsigned int data_offset;
    unsigned int uncompressed_size;
    unsigned int reserved_metadata;
};

struct DatArchiveCleanup_00434c20_00434d10 {
    DatArchiveEntry_00434d10* entries;
    int entry_count;
    char* filename;
    FileInterface* file;
};

void __cdecl DatArchive_Close(DatArchiveCleanup_00434c20_00434d10* archive);
void __fastcall DatArchive_Reset(DatArchiveCleanup_00434c20_00434d10* archive);
