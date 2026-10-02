#include "th10/archive/dat_archive_types.hpp"
#include "th10/util/heap.hpp"

// Native LTCG selects the retail ESI receiver from the real Reset and global
// shutdown callers. The member signature remains ordinary C++.
#pragma code_seg(".text$a04close")
__declspec(noinline) void DatArchive::Close() {
    if (filename) {
        asm_free_00452422(filename);
        filename = 0;
    }

    DatArchiveEntry* current_entries = entries;
    filename = 0;
    if (current_entries) {
        unsigned int* allocation =
            reinterpret_cast<unsigned int*>(current_entries) - 1;
        const ArchiveEntryCallback release =
            reinterpret_cast<ArchiveEntryCallback>(HeapBuffer_Release);
        asm_eh_vector_destructor_iterator_004525ff(
            current_entries, sizeof(DatArchiveEntry),
            static_cast<int>(*allocation), release);
        asm_free_004524a1(allocation);
    }

    FileInterface* current_file = file;
    entries = 0;
    if (current_file)
        delete current_file;
    file = 0;
    entry_count = 0;
}
#pragma code_seg()
