// Select an archive entry by path, or use a temporary Win32 FileHandle.
// Its normal and exceptional destruction retain the original vtable changes
// and handle close. Native MSVC emits the genuine unwind action and handler.
#include "th10/archive/dat_archive_types.hpp"
#include "../../../build_support/layout/ltcg/resource_size_file.hpp"
__declspec(noinline) unsigned int DatArchive_FindSize(DatArchive*, const char*);
struct ArchiveEntry_004356f0;
struct ArchiveName {
    char text[1];
    __declspec(noinline) const ArchiveEntry_004356f0* Find() const;
};
extern "C" char* __cdecl FirstByteSearch(const char*, int);
extern "C" const char* g_resource_archive_path;
extern "C" __declspec(dllimport) BOOL __stdcall CloseHandle(HANDLE);
extern "C" __declspec(dllimport) DWORD __stdcall GetFileSize(HANDLE, DWORD*);
#pragma code_seg(".text$09query")
__declspec(noinline) unsigned int __fastcall ResourceGetFileSize(const char* path) {
    DatArchive* archive = (DatArchive*)((const ArchiveName*)path)->Find();
    if (archive) {
        const char* slash = FirstByteSearch(path, '/');
        return DatArchive_FindSize(archive, slash ? slash + 1 : path);
    }
    ResourceSizeFile file;
    file.Open(path, g_resource_archive_path);
    return file.GetSize();
}
#pragma code_seg()
