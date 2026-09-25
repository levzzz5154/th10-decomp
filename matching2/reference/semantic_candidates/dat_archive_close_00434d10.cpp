#include "../../layout/ltcg/archive_cleanup_00434c20_00434d10_types.hpp"

extern "C" void __cdecl entry_free_00452422(void* memory);
extern "C" void __cdecl entry_free_004524a1(void* memory);

// 0x00434D10 reads its archive receiver from ESI in retail. The explicit
// pointer is the source-level model; the pair's LTCG context is intended to
// expose that private register convention without inline assembly.
#pragma code_seg(".text$03close")
__declspec(noinline) void __cdecl DatArchive_Close(
    DatArchiveCleanup_00434c20_00434d10* archive) {
    if (archive->filename != 0) {
        entry_free_00452422(archive->filename);
        archive->filename = 0;
    }

    // The index allocation carries its array-new count immediately before
    // the first 16-byte entry. Each entry begins with the owned name buffer;
    // HeapBuffer_Release is the element destructor used by the retail vector
    // destructor iterator at 0x004525FF.
    DatArchiveEntry_00434d10* entries = archive->entries;
    archive->filename = 0;
    if (entries != 0) {
        unsigned int* allocation_count =
            reinterpret_cast<unsigned int*>(entries) - 1;
        int remaining = static_cast<int>(*allocation_count);
        while (remaining > 0) {
            --remaining;
            HeapBuffer_Release(&entries[remaining].name);
        }

        // The filename and individual names use the CRT free entry; the
        // vector allocation itself is released through the adjacent free
        // entry after dropping its four-byte array cookie.
        entry_free_004524a1(allocation_count);
    }

    archive->entries = 0;
    if (archive->file != 0) {
        delete archive->file;
    }
    archive->file = 0;
    archive->entry_count = 0;
}
#pragma code_seg()
