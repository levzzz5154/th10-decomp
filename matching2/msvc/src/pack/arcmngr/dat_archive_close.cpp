// 0x00434D10: DatArchive::Close
#include "th10/archive/dat_archive_types.hpp"
#include "th10/util/heap.hpp"

// Native LTCG selects the retail ESI receiver from the real Reset and global
// shutdown callers. The member signature remains ordinary C++.
#pragma code_seg(".text$02close")
__declspec(noinline) void DatArchive::Close() {
    if (filename) {
        crt_free(filename);
        filename = 0;
    }

    DatArchiveEntry* current_entries = entries;
    filename = 0;
    if (current_entries) {
        unsigned int* allocation =
            reinterpret_cast<unsigned int*>(current_entries) - 1;
        const ArchiveEntryCallback release =
            reinterpret_cast<ArchiveEntryCallback>(HeapBuffer_Release);
        crt_eh_vector_dtor(
            current_entries, sizeof(DatArchiveEntry),
            static_cast<int>(*allocation), release);
        crt_free_startup(allocation);
    }

    FileInterface* current_file = file;
    entries = 0;
    if (current_file)
        delete current_file;
    file = 0;
    entry_count = 0;
}
#pragma code_seg()
