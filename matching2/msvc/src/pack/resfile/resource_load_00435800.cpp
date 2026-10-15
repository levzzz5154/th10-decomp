// Load an archive entry or a newly allocated disk-file buffer.
#include "th10/archive/dat_archive_types.hpp"
struct ArchiveEntry_004356f0;
struct ArchiveName_004356f0 { char text[1]; __declspec(noinline) const ArchiveEntry_004356f0* Find() const; };
struct ArchiveResourceName { char text[1]; unsigned char* Read(DatArchive* archive, unsigned char* output) const; };
struct ResourcePath { char text[1]; __declspec(noinline) unsigned char* Load(unsigned char* output) const; DWORD GetFileSize() const; };
extern "C" char* __cdecl FirstByteSearch_00452730(const char*, int);
extern "C" const char* data_00474908;
#pragma code_seg(".text$09load")
__declspec(noinline) unsigned char* __stdcall ResourceLoadRetail(const char* path, unsigned char* output) {
    DatArchive* archive = (DatArchive*)((const ArchiveName_004356f0*)path)->Find();
    if (archive) {
        const char* slash = FirstByteSearch_00452730(path, '/');
        const ArchiveResourceName* name = (const ArchiveResourceName*)(slash ? slash + 1 : path);
        return name->Read(archive, output);
    }
    FileHandleOwner file;
    file.Open(path, data_00474908);
    return static_cast<unsigned char*>(file.ReadWhole(file.GetSize()));
}
#pragma code_seg()
