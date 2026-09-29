// 0x004357D0..0x004357F3 (36 bytes): append a successfully opened archive.
// Retail receives the path in EAX. This explicit stdcall parameter still
// requires private ABI recovery with DatArchive_Open before promotion.
#include "dat_archive_types.hpp"

extern "C" unsigned int g_resource_archive_count;
extern "C" DatArchive g_resource_archives[];
extern "C" bool __stdcall DatArchive_Open_00434c30(DatArchive* archive, const char* path);

extern "C" bool __stdcall Resource_RegisterArchive_004357d0(const char* archive_path) {
    DatArchive* archive = g_resource_archives + g_resource_archive_count;
    if (!DatArchive_Open_00434c30(archive, archive_path))
        return false;

    // Reload after Open and retain 32-bit wrapping. Retail has no capacity
    // check and does not separately initialize the selected archive record.
    ++g_resource_archive_count;
    return true;
}
