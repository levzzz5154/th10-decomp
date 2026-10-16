// Compiler context and ABI anchors only; none of these bytes enter the image.
#include "../../../src/pack/arcmngr/dat_archive_open.cpp"
#include "../../../src/pack/arcmngr/dat_archive_close.cpp"
#include "../../../src/pack/arcmngr/legacy_string_duplicate.cpp"

// The constructors the openers inline; the real definitions live in
// platform/file.cpp, platform/memory_file.cpp and platform/resource_lifetime.cpp.
FileHandle::FileHandle() : handle((HANDLE)-1), access(0) {}
BufferFile::BufferFile() : size_(0), position_(0), data_(0) {}
ResourceFile::ResourceFile() {}

extern "C" int __stdcall DatIndexDecode_0044b0d0(void* data, int size, int key);

// LoadIndex (0x00434F70) modelled only for its argument shape: archive in
// ESI, path on the stack, RET 4.  Never selected as recovered code.
#pragma code_seg(".text$05loadindex")
__declspec(noinline) bool DatArchive::LoadIndex(const char* path) {
    if (!file)
        return false;
    unsigned int header[4];
    if (file->Open(path, g_dat_archive_read_mode) && file->Read(header, sizeof(header))) {
        entry_count = DatIndexDecode_0044b0d0(header, 16, 0x1B);
        if (entry_count > 0)
            return true;
    }
    delete file;
    file = 0;
    return false;
}
#pragma code_seg()

bool DatArchive_OpenNext(const char* path);

#pragma code_seg(".text$09context")
int __stdcall DatArchiveOpenContext_00434c30(DatArchive* archives, const char** paths, int count) {
    int opened = 0;
    for (int i = 0; i < count; ++i) {
        if (archives[i].Open(paths[i]))
            ++opened;
        if (archives[i].OpenResource(paths[i] + 4))
            ++opened;
        if (DatArchive_OpenNext(paths[i] + 8))
            ++opened;
    }
    return opened;
}
#pragma code_seg()
