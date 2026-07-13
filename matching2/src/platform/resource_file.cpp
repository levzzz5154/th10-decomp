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

ResourceFile::ResourceFile() {
}

__declspec(noinline) ResourceFile::~ResourceFile() {
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
        FreeResource(0);
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
