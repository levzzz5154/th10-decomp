// Semantic candidate for 0x00434D70..0x00434DCC (93 bytes).
// Retail vector deleting destructor: receiver in ESI, flags on stack, RET 4.
// This explicit stdcall interface is only the behavioral source model.
#include "dat_archive_types.hpp"

extern "C" void* __stdcall DatArchiveEntry_Delete_00434d70(
        DatArchiveEntry* entry, unsigned char flags) {
    if (flags & 2) {
        unsigned int* allocation = reinterpret_cast<unsigned int*>(entry) - 1;
        asm_eh_vector_destructor_iterator_004525ff(
            entry, sizeof(DatArchiveEntry), static_cast<int>(*allocation),
            ArchiveEntry_Release_00435250);
        if (flags & 1)
            asm_free_004524a1(allocation);
        // Array mode returns the cookie address, even without deallocation.
        return allocation;
    }

    if (entry->name) {
        asm_free_00452422(const_cast<char*>(entry->name));
        entry->name = 0;
    }
    if (flags & 1)
        asm_free_004524a1(entry);
    return entry;
}
