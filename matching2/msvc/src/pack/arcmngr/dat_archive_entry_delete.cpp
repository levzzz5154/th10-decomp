// 0x00434D70: scalar/array cleanup and optional deallocation of archive entries.
// Passing the flags as a value record retains the retail four-byte stack slot
// under native LTCG. Only the low byte participates in deletion decisions.
struct EntryDeletionFlags { unsigned char bits; };

struct ArchiveEntryOwner {
    char* name;
    unsigned int offset;
    unsigned int uncompressed_size;
    unsigned int metadata;
    __declspec(noinline) void* Delete(EntryDeletionFlags flags);
};
typedef char ArchiveEntryOwner_size[sizeof(ArchiveEntryOwner) == 16 ? 1 : -1];
typedef char EntryDeletionFlags_size[sizeof(EntryDeletionFlags) == 1 ? 1 : -1];

typedef void (__fastcall* EntryRelease)(ArchiveEntryOwner*);
extern "C" {
    void __cdecl ReleaseName(void*);
    void __cdecl ReleaseAllocation(void*);
    void __stdcall DestroyEntryArray(void*, unsigned int, int, EntryRelease);
    void __fastcall ReleaseArchiveEntry(ArchiveEntryOwner*);
}
#pragma code_seg(".text$01delete")
void* ArchiveEntryOwner::Delete(EntryDeletionFlags mode) {
    const unsigned char flags = mode.bits;
    if (flags & 2) {
        unsigned int* allocation = reinterpret_cast<unsigned int*>(this) - 1;
        DestroyEntryArray(this, sizeof(ArchiveEntryOwner), *allocation, ReleaseArchiveEntry);
        if (flags & 1)
            ReleaseAllocation(allocation);
        // Array mode returns the cookie address, including when not freed.
        return allocation;
    }
    if (name) {
        ReleaseName(name);
        name = 0;
    }
    if (flags & 1)
        ReleaseAllocation(this);
    return this;
}
#pragma code_seg()
