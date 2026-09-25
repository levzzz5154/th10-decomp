struct DatArchiveFindSizeEntry_00434EF0 {
    const char* name;
    unsigned int data_offset;
    unsigned int uncompressed_size;
    unsigned int reserved_metadata;
};

struct DatArchiveFindSizeIndex_00434EF0 {
    DatArchiveFindSizeEntry_00434EF0* entries;
    int entry_count;
};

extern "C" int __cdecl asm_stricmp_0046054e(const char* left, const char* right);

// Retail callers pass the archive index in EAX and the requested name in
// EBX. These ordinary C++ parameters document the values and operation, but
// do not claim that the compiler reproduces that private register ABI.
__declspec(noinline) unsigned int DatArchive_FindSize(
    DatArchiveFindSizeIndex_00434EF0* archive, const char* name) {
    if (archive->entries == 0)
        return 0;

    DatArchiveFindSizeEntry_00434EF0* entry = archive->entries;
    int remaining = archive->entry_count;
    while (remaining > 0) {
        if (asm_stricmp_0046054e(name, entry->name) == 0)
            return entry->uncompressed_size;
        --remaining;
        ++entry;
    }

    return 0;
}
