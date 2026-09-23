#include "../../layout/ltcg/archive_cleanup_00434c20_00434d10_types.hpp"

#include <cstddef>
#include <cstring>

extern "C" void* __cdecl asm_operator_new_00452493(unsigned int size);
extern "C" void __cdecl asm_eh_vector_constructor_iterator_0045252d();
extern "C" void* __cdecl asm_malloc_00452706(unsigned int size);

namespace {

typedef void (__fastcall *ArchiveEntryCallback)(void* entry);
typedef void (__stdcall *EhVectorConstructorIterator)(
    void* entries, unsigned int entry_size, int entry_count,
    ArchiveEntryCallback constructor, ArchiveEntryCallback destructor);

} // namespace

typedef char DatArchiveEntrySizeMustBe16[
    sizeof(DatArchiveEntry_00434d10) == 0x10 ? 1 : -1];
typedef char DatArchiveEntryOffsetMustFollowHeapBuffer[
    offsetof(DatArchiveEntry_00434d10, data_offset) == 0x04 ? 1 : -1];

// 0x004350D0 receives (packed records, record count, terminal data offset)
// as three stack arguments and returns the first 16-byte entry in EAX. The
// stdcall declaration preserves retail's ret 0x0c cleanup for its caller.
extern "C" DatArchiveEntry_00434d10* __stdcall DatArchive_BuildIndex_004350d0(
    const unsigned char* packed_records, int record_count,
    unsigned int terminal_data_offset) {
    const unsigned int allocation_count =
        static_cast<unsigned int>(record_count) + 1u;
    const unsigned int allocation_size =
        allocation_count * static_cast<unsigned int>(sizeof(DatArchiveEntry_00434d10)) +
        static_cast<unsigned int>(sizeof(unsigned int));

    unsigned char* allocation = static_cast<unsigned char*>(
        asm_operator_new_00452493(allocation_size));
    if (allocation == 0)
        return 0;

    *reinterpret_cast<unsigned int*>(allocation) = allocation_count;
    DatArchiveEntry_00434d10* entries =
        reinterpret_cast<DatArchiveEntry_00434d10*>(allocation + sizeof(unsigned int));

    // The retail vector helper invokes the HeapBuffer default constructor on
    // every element. Its callback ABI passes the entry in ECX, which is also
    // the one-argument x86 fastcall form used by these two HeapBuffer methods.
    const ArchiveEntryCallback initialize_entry =
        reinterpret_cast<ArchiveEntryCallback>(0x004352c0u);
    const ArchiveEntryCallback release_entry =
        reinterpret_cast<ArchiveEntryCallback>(0x00435250u);
    const EhVectorConstructorIterator construct_entries =
        reinterpret_cast<EhVectorConstructorIterator>(
            &asm_eh_vector_constructor_iterator_0045252d);
    construct_entries(entries,
                      static_cast<unsigned int>(sizeof(DatArchiveEntry_00434d10)),
                      static_cast<int>(allocation_count), initialize_entry,
                      release_entry);

    const unsigned char* packed_cursor = packed_records;
    if (record_count > 0) {
        for (int index = 0; index < record_count; ++index) {
            const char* name = reinterpret_cast<const char*>(packed_cursor);
            const unsigned int name_storage_size =
                static_cast<unsigned int>(std::strlen(name)) + 1u;
            char* name_copy = static_cast<char*>(
                asm_malloc_00452706(name_storage_size));
            if (name_copy != 0)
                std::memcpy(name_copy, name, name_storage_size);
            entries[index].name.data = name_copy;

            // Each packed name is NUL-terminated and padded to a 4-byte
            // boundary before its three DWORD metadata fields.
            const unsigned int padded_name_size =
                (name_storage_size + 3u) & ~3u;
            packed_cursor += padded_name_size;
            std::memcpy(&entries[index].data_offset, packed_cursor,
                        3u * sizeof(unsigned int));
            packed_cursor += 3u * sizeof(unsigned int);
        }
    }

    // The extra element is the array sentinel consumed by the DAT archive
    // reader. HeapBuffer's constructor already cleared its name pointer.
    entries[record_count].data_offset = terminal_data_offset;
    entries[record_count].uncompressed_size = 0;
    return entries;
}
