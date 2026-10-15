#ifndef TH10_RESOURCE_SIZE_FILE_LIFETIME_HPP
#define TH10_RESOURCE_SIZE_FILE_LIFETIME_HPP
#include "th10/platform/windows_types.hpp"
#include <stddef.h>
extern "C" __declspec(dllimport) BOOL __stdcall CloseHandle(HANDLE);
extern "C" __declspec(dllimport) DWORD __stdcall GetFileSize(HANDLE, DWORD*);
extern "C" unsigned char ResourceFileVtable_0046f230;
extern "C" unsigned char ResourceBaseVtable_0046f210;
// Twelve-byte FileHandle layout, with the complete constructor/destructor
// vtable transitions represented explicitly. Open has the genuine retail
// public ECX receiver and path/mode stack arguments.
struct ResourceSizeFile {
    void* vtable;
    HANDLE handle;
    DWORD access;
    __forceinline ResourceSizeFile()
        : vtable(&ResourceFileVtable_0046f230), handle((HANDLE)-1), access(0) {}
    ~ResourceSizeFile();
    BYTE Open(const char* path, const char* mode);
    __forceinline void Close() {
        if (handle != (HANDLE)-1) {
            CloseHandle(handle);
            handle = (HANDLE)-1;
            access = 0;
        }
    }
    __forceinline DWORD GetSize() const {
        if (handle == (HANDLE)-1)
            return 0;
        return GetFileSize(handle, 0);
    }
};
#pragma code_seg(".text$03dtor")
ResourceSizeFile::~ResourceSizeFile() {
    vtable = &ResourceFileVtable_0046f230;
    Close();
    vtable = &ResourceBaseVtable_0046f210;
}
#pragma code_seg()
typedef char ResourceSizeFileLayout[sizeof(ResourceSizeFile) == 12 ? 1 : -1];
typedef char
    ResourceSizeFileHandleOffset[offsetof(ResourceSizeFile, handle) == 4 ? 1 : -1];
typedef char
    ResourceSizeFileAccessOffset[offsetof(ResourceSizeFile, access) == 8 ? 1 : -1];
#endif
