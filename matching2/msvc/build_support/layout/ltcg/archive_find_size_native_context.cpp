// Compiler context only; the lookup return remains live through the caller.
#include "../../../src/pack/arcmngr/dat_archive_find_size.cpp"

#pragma code_seg(".text$03context")
extern "C" __declspec(noinline) int __stdcall ArchiveFindSizeCompilerContext(
        DatArchive** archives, const char** names, int count) {
    int result = 0;
    for (int index = 0; index < count; ++index) {
        DatArchive* archive = archives[index];
        const char* name = names[index];
        result += DatArchive_FindSize(archive, name);
    }
    return result;
}
#pragma code_seg()
