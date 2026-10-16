// Load an archive entry or a newly allocated disk-file buffer.
#include "th10/archive/dat_archive_types.hpp"
struct ArchiveEntry2;
struct ArchiveName { char text[1]; __declspec(noinline) const ArchiveEntry2* Find() const; };
struct ArchiveResourceName { char text[1]; unsigned char* Read(DatArchive* archive, unsigned char* output) const; };
struct ResourcePath { char text[1]; __declspec(noinline) unsigned char* Load(unsigned char* output) const; DWORD GetFileSize() const; };
extern "C" char* __cdecl FirstByteSearch(const char*, int);
extern "C" const char* g_resource_archive_path;
#pragma code_seg(".text$09load")
__declspec(noinline) unsigned char* __stdcall ResourceLoadRetail(const char* path, unsigned char* output) {
    DatArchive* archive = (DatArchive*)((const ArchiveName*)path)->Find();
    if (archive) {
        const char* slash = FirstByteSearch(path, '/');
        const ArchiveResourceName* name = (const ArchiveResourceName*)(slash ? slash + 1 : path);
        return name->Read(archive, output);
    }
    FileHandleOwner file;
    file.Open(path, g_resource_archive_path);
    return static_cast<unsigned char*>(file.ReadWhole(file.GetSize()));
}
#pragma code_seg()
