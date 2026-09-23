#include "asm_encoding.hpp"
#include "asm_symbols.hpp"
#include "../../layout/ltcg/archive_find_entry_followup_types.hpp"

// 0x00434C20..0x00434C29: ?DatArchive_Reset@@
// Naked body preserves the retail register/stack ABI.

#pragma code_seg(".text$01find")
__declspec(noinline) ArchiveFindEntryRecord* DatArchive_FindEntry(
        ArchiveFindEntryIndex* archive, const char* name) {
    if (archive->entries == 0)
        return 0;
    ArchiveFindEntryRecord* entry = archive->entries;
    int remaining = archive->entry_count;
    while (remaining > 0) {
        if (archive_find_stricmp(name, entry->name) == 0)
            return entry;
        --remaining;
        ++entry;
    }
    return 0;
}
#pragma code_seg()
