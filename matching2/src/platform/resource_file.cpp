#include "th10/platform/memory_file.hpp"

extern "C" void* __cdecl _malloc(DWORD size);

extern "C" __declspec(dllimport) HANDLE __stdcall FindResourceA(
    HMODULE module, const char* name, const char* type);
extern "C" __declspec(dllimport) HANDLE __stdcall LoadResource(
    HMODULE module, HANDLE resource);
extern "C" __declspec(dllimport) void* __stdcall LockResource(HANDLE resource);
extern "C" __declspec(dllimport) DWORD __stdcall SizeofResource(
    HMODULE module, HANDLE resource);
extern "C" __declspec(dllimport) BOOL __stdcall FreeResource(HANDLE resource);

#ifdef _MSC_VER
extern "C" void _free(void*);
extern "C" char off_46F308;
extern "C" char off_46F210;
#endif

ResourceFile::ResourceFile() {
}

// 0x00436CA0 - Fill the resource palette with the packed retail color.
void ResourceFile_FillPalette(unsigned short* palette, unsigned int count,
                              unsigned int color) {
    const unsigned short packed = (unsigned short)((((color >> 0x14) & 0x0f) << 8) |
        (((color >> 0x0c) & 0x0f) << 4) | ((color >> 4) & 0x0f));
    for (unsigned int index = 0; index != count; ++index)
        palette[index] = packed;
}

// 0x00436680 - Restore the BufferFile boundary, release its owned bytes, then
// complete the FileInterface destructor chain.
__declspec(noinline) ResourceFile::~ResourceFile() {
    Close();
}

// 0x004366C0 - Copy a Win32 RCDATA resource into an owned memory buffer.
BYTE ResourceFile::Open(const char* resource_name, const char*) {
    Close();
    HANDLE resource = FindResourceA(0, resource_name, (const char*)10);
    if (!resource) return 1;
    HANDLE loaded = LoadResource(0, resource);
    if (!loaded) return 1;
    const BYTE* source = (const BYTE*)LockResource(loaded);
    if (!source) {
        FreeResource(loaded);
        Close();
        return 1;
    }

    size_ = SizeofResource(0, resource);
    data_ = (BYTE*)_malloc(size_);
    if (!data_) {
        Close();
        return 1;
    }
    for (DWORD index = 0; index < size_; ++index) {
        data_[index] = source[index];
    }
    position_ = data_;
    FreeResource(loaded);
    return 1;
}
