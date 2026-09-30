// Semantic candidates for disk Open (0x00434C30, 108 bytes) and resource Open
// (0x00434CA0, 100 bytes). Both retail entries receive archive in ECX and path
// in EAX, with an AL boolean result. Explicit stdcall parameters are used here
// until native LTCG can reproduce the entry and helper register conventions.
#include "dat_archive_types.hpp"
#include "th10/platform/memory_file.hpp"

extern "C" void* __cdecl asm_operator_new_00452493(unsigned int size);
extern "C" bool __stdcall DatArchive_LoadIndex_00434f70(DatArchive* archive, const char* path);
extern "C" char* __stdcall LegacyString_Duplicate_00435220(const char* text);
extern "C" const char* g_dat_archive_read_mode;

// Standalone candidate context for the constructors in platform/file.cpp,
// platform/memory_file.cpp and platform/resource_lifetime.cpp. The maintained
// class layouts and virtual interfaces are reused; these definitions allow
// the same initializations to inline into the two opener bodies.
FileHandle::FileHandle() : handle((HANDLE)-1), access(0) {}
BufferFile::BufferFile() : size_(0), position_(0), data_(0) {}
ResourceFile::ResourceFile() {}

inline void* __cdecl operator new(size_t, void* storage) { return storage; }

extern "C" bool __stdcall DatArchive_Open_00434c30(DatArchive* archive, const char* path) {
    DatArchive_Close_00434d10(archive);
    void* storage = asm_operator_new_00452493(sizeof(FileHandle));
    archive->file = storage ? new (storage) FileHandle : 0;
    if (!archive->file)
        return false;

    if (DatArchive_LoadIndex_00434f70(archive, path)) {
        archive->filename = LegacyString_Duplicate_00435220(path);
        if (archive->filename) {
            // The disk backend is reopened with the owned filename. Retail
            // ignores this Open result and reports success unconditionally.
            archive->file->Open(archive->filename, g_dat_archive_read_mode);
            return true;
        }
    }
    DatArchive_Close_00434d10(archive);
    return false;
}

extern "C" bool __stdcall DatArchive_OpenResource_00434ca0(DatArchive* archive, const char* path) {
    DatArchive_Close_00434d10(archive);
    void* storage = asm_operator_new_00452493(sizeof(ResourceFile));
    archive->file = storage ? new (storage) ResourceFile : 0;
    if (!archive->file)
        return false;

    if (DatArchive_LoadIndex_00434f70(archive, path)) {
        archive->filename = LegacyString_Duplicate_00435220(path);
        if (archive->filename)
            return true;
    }
    DatArchive_Close_00434d10(archive);
    return false;
}
