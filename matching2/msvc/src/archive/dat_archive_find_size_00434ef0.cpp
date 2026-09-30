#include "th10/archive/dat_archive_types.hpp"

extern "C" int __cdecl asm_stricmp_0046054e(
    const unsigned char* left, const unsigned char* right);

#pragma code_seg(".text$01findsize")
__declspec(noinline) unsigned int DatArchive_FindSize(
        DatArchive* archive, const char* name) {
    DatArchiveEntry* entry = archive->entries;
    if (entry != 0) {
        int remaining = archive->entry_count;
        while (remaining > 0) {
            if (asm_stricmp_0046054e(
                    reinterpret_cast<const unsigned char*>(name),
                    reinterpret_cast<const unsigned char*>(entry->name)) == 0)
                goto found;
            --remaining;
            ++entry;
        }
    }
    return 0;

found:
    return entry->uncompressed_size;
}
#pragma code_seg()
