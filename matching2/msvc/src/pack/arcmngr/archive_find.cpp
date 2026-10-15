#include "../../../build_support/layout/ltcg/native_archive_read/archive.hpp"
#ifndef ARCHIVE_FIND_SECTION
#define ARCHIVE_FIND_SECTION ".text$a02find"
#endif
#pragma code_seg(ARCHIVE_FIND_SECTION)
extern "C" __declspec(noinline) DatArchiveEntry* __stdcall ArchiveFind(DatArchive* archive,const char* name) {
    if (!archive->entries) return 0;
    DatArchiveEntry* entry = archive->entries;
    int remaining = archive->entry_count;
    while (remaining > 0) {
        if (asm_stricmp_0046054e(name,entry->name)==0) return entry;
        --remaining;
        ++entry;
    }
    return 0;
}
#pragma code_seg()
