// Semantic candidate for 0x00434D10..0x00434D65 (86 bytes).
// Retail receives the archive in ESI and has no stack arguments. This ordinary
// stdcall parameter exposes the receiver for behavioral validation.
#include "dat_archive_types.hpp"

extern "C" void __stdcall DatArchive_Close_00434d10(DatArchive* archive) {
    if (archive->filename) {
        asm_free_00452422(archive->filename);
        archive->filename = 0;
    }

    DatArchiveEntry* entries = archive->entries;
    archive->filename = 0;
    if (entries) {
        // The allocation's cookie includes the sentinel; entry_count does
        // not control destruction. Keep the helper's reverse-order cleanup
        // and its own exception handling by calling the actual vector helper.
        unsigned int* allocation = reinterpret_cast<unsigned int*>(entries) - 1;
        asm_eh_vector_destructor_iterator_004525ff(
            entries, sizeof(DatArchiveEntry), static_cast<int>(*allocation),
            ArchiveEntry_Release_00435250);
        asm_free_004524a1(allocation);
    }

    FileInterface* file = archive->file;
    archive->entries = 0;
    if (file)
        delete file;
    archive->file = 0;
    archive->entry_count = 0;
}
