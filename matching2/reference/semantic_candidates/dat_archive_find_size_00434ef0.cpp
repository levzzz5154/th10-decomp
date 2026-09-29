#include "dat_archive_types.hpp"

extern "C" int __cdecl asm_stricmp_0046054e(const char* left, const char* right);

// Retail callers pass the archive index in EAX and the requested name in
// EBX. These ordinary C++ parameters document the values and operation, but
// do not claim that the compiler reproduces that private register ABI.
extern "C" unsigned int __stdcall DatArchive_FindSize_00434ef0(
    DatArchive* archive, const char* name) {
    if (archive->entries == 0)
        return 0;

    DatArchiveEntry* entry = archive->entries;
    int remaining = archive->entry_count;
    while (remaining > 0) {
        if (asm_stricmp_0046054e(name, entry->name) == 0)
            return entry->uncompressed_size;
        --remaining;
        ++entry;
    }

    return 0;
}
