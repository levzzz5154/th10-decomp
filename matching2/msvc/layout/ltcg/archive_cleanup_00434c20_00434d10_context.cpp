// Compiler context only; never selected as recovered game code.
#include "../../src/archive/dat_archive_reset_00434c20.cpp"

#pragma code_seg(".text$05context")
extern "C" __declspec(noinline) int __stdcall ArchiveCleanupPairCompilerContext(
    DatArchiveCleanup_00434c20_00434d10** archives, int count) {
    int fully_reset = 0;
    while (count > 0) {
        DatArchiveCleanup_00434c20_00434d10* archive = *archives++;
        DatArchive_Reset(archive);
        if (archive->entries == 0 && archive->entry_count == 0 &&
            archive->filename == 0 && archive->file == 0) {
            ++fully_reset;
        }
        --count;
    }
    return fully_reset;
}
#pragma code_seg()
