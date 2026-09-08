#include "th10/platform/memory_file.hpp"
#include "th10/platform/buffer_file_lifetime.inl"

extern "C" __declspec(dllimport) HANDLE __stdcall FindResourceA(HMODULE, LPCSTR, LPCSTR);
extern "C" __declspec(dllimport) HANDLE __stdcall LoadResource(HMODULE, HANDLE);
extern "C" __declspec(dllimport) void* __stdcall LockResource(HANDLE);
extern "C" __declspec(dllimport) BOOL __stdcall FreeResource(HANDLE);
extern "C" __declspec(dllimport) DWORD __stdcall SizeofResource(HMODULE, HANDLE);
extern "C" void* __cdecl entry_malloc_00452706(DWORD);
#ifdef _MSC_VER
extern "C" void* __cdecl memcpy(void*, const void*, DWORD);
#pragma intrinsic(memcpy)
#else
#include <cstring>
#endif

// 0x00436680: destruction needs only BufferFile's owned-buffer cleanup.
__declspec(noinline) ResourceFile::~ResourceFile() {}

// Emit the class's deleting-destructor entry. The retail EAX-this constructor
// at 0x00436640 remains assembly; this thiscall constructor is not selected.
ResourceFile::ResourceFile() {}

// 0x004366C0: copy an embedded RCDATA resource into an owned file buffer.
// Retail returns 1 even on failure. Preserve its cleanup behavior, including
// FreeResource(NULL) after a failed lock and no FreeResource on malloc failure.
BYTE ResourceFile::Open(const char* name, const char*) {
    Close();
    HANDLE resource = FindResourceA(0, name, (LPCSTR)10);
    if (!resource)
        goto failed;

    HANDLE loaded;
    loaded = LoadResource(0, resource);
    if (!loaded)
        goto failed;

    void* source;
    source = LockResource(loaded);
    if (!source) {
        FreeResource(source);
        goto failed;
    }

    size_ = SizeofResource(0, resource);
    data_ = (BYTE*)entry_malloc_00452706(size_);
    if (!data_) {
    failed:
        Close();
        return 1;
    }

    memcpy(data_, source, size_);
    position_ = data_;
    FreeResource(loaded);
    return 1;
}
