// Semantic candidate for 0x004350D0..0x00435216 (327 bytes).
// The entry/helper argument conventions and raw-allocation exception cleanup
// are represented in C++. The exact native MSVC unwind frame is not yet matched.
#include "dat_archive_types.hpp"

extern "C" void* __cdecl asm_operator_new_00452493(unsigned int size);

namespace {

// Retail's one outer unwind state releases the raw array allocation. The
// vector helper owns partial-construction cleanup; previously copied names
// are not individually released if a later name allocation throws.
class PendingIndexAllocation {
public:
    explicit PendingIndexAllocation(void* allocation) : allocation_(allocation) {}
    ~PendingIndexAllocation() {
        if (allocation_)
            asm_free_004524a1(allocation_);
    }
    void Release() { allocation_ = 0; }

private:
    PendingIndexAllocation(const PendingIndexAllocation&);
    PendingIndexAllocation& operator=(const PendingIndexAllocation&);
    void* allocation_;
};

__forceinline unsigned int NameStorageSize(const char* name) {
    const char* cursor = name;
    while (*cursor++) {}
    return static_cast<unsigned int>(cursor - name);
}

__forceinline void CopyName(char* destination, const char* source) {
    while ((*destination++ = *source++) != 0) {}
}

} // namespace

extern "C" DatArchiveEntry* __stdcall DatArchive_BuildIndex_004350d0(
        const unsigned char* packed_records, int record_count,
        unsigned int terminal_data_offset) {
    unsigned int allocation_count = static_cast<unsigned int>(record_count) + 1u;
    unsigned int allocation_size = allocation_count * sizeof(DatArchiveEntry) + sizeof(unsigned int);
    unsigned char* allocation = static_cast<unsigned char*>(asm_operator_new_00452493(allocation_size));
    if (!allocation)
        return 0;
    PendingIndexAllocation pending_allocation(allocation);

    // The cookie includes the terminal sentinel, as does array construction.
    *reinterpret_cast<unsigned int*>(allocation) = allocation_count;
    DatArchiveEntry* entries = reinterpret_cast<DatArchiveEntry*>(allocation + sizeof(unsigned int));
    asm_eh_vector_constructor_iterator_0045252d(
        entries, sizeof(DatArchiveEntry), static_cast<int>(allocation_count),
        ArchiveEntry_Construct_004352c0, ArchiveEntry_Release_00435250);
    if (!entries) {
        pending_allocation.Release();
        return 0;
    }

    const unsigned char* cursor = packed_records;
    for (int index = 0; index < record_count; ++index) {
        const char* name = reinterpret_cast<const char*>(cursor);
        char* copy = static_cast<char*>(asm_malloc_00452706(NameStorageSize(name)));
        if (copy)
            CopyName(copy, name);
        entries[index].name = copy;

        // Retail scans again after allocation/copy. A failed name allocation
        // still advances through the record and preserves its metadata.
        unsigned int name_bytes = NameStorageSize(name);
        cursor += (name_bytes + 3u) & ~3u;
        const unsigned int* fields = reinterpret_cast<const unsigned int*>(cursor);
        entries[index].offset = fields[0];
        entries[index].uncompressed_size = fields[1];
        entries[index].metadata = fields[2];
        cursor += 3 * sizeof(unsigned int);
    }

    entries[record_count].offset = terminal_data_offset;
    entries[record_count].uncompressed_size = 0;
    // Construction cleared the sentinel name; its metadata word is untouched.
    pending_allocation.Release();
    return entries;
}
