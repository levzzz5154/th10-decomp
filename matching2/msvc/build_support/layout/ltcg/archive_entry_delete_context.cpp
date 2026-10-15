// Compiler context only; never selected as recovered game code.
#include "../../../src/pack/arcmngr/dat_archive_entry_delete.cpp"
#pragma code_seg(".text$03context")
extern "C" int __stdcall ArchiveDeleteContext(ArchiveEntryOwner* entry, unsigned char* flags, int count) {
    int result = 0;
    for (int index = 0; index < count; ++index) {
        EntryDeletionFlags mode = { flags[index] };
        result += entry->Delete(mode) != 0;
    }
    return result;
}
#pragma code_seg()
