#include "th10/archive/dat.hpp"

extern "C" int __cdecl _stricmp(const char* left, const char* right);

// Clean reconstruction of 0x00434F30. The retail function receives archive in
// EAX and name in EBX; the typed implementation uses a conventional C++ API.
const DatEntry* DatArchive_FindEntry(
        const DatArchiveIndex* archive, const char* name) {
    if (!archive->entries) {
        return 0;
    }

    const DatEntry* entry = archive->entries;
    for (int32_t remaining = archive->entry_count;
            remaining > 0; --remaining, ++entry) {
        if (_stricmp(name, entry->name) == 0) {
            return entry;
        }
    }
    return 0;
}
