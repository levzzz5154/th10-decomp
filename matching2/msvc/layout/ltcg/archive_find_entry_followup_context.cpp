// Compiler context only; this caller is never selected as recovered game code.
#include "../../src/archive/dat_archive_find_entry_00434f30.cpp"

#pragma code_seg(".text$03context")
extern "C" __declspec(noinline) int __stdcall ArchiveFindEntryFollowupCompilerContext(
        ArchiveFindEntryIndex** archives, const char** names, int count) {
    int result = 0;
    for (int index = 0; index < count; ++index) {
        ArchiveFindEntryIndex* archive = archives[index];
        const char* name = names[index];
        ArchiveFindEntryRecord* entry = DatArchive_FindEntry(archive, name);
        result += entry != 0;
    }
    return result;
}
#pragma code_seg()
