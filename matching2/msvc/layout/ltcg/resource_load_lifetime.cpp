#include "th10/platform/windows_types.hpp"
struct FileOwnerVtable;
extern "C" unsigned char file_handle_vtable;
extern "C" unsigned char file_interface_vtable;
extern "C" __declspec(dllimport) BOOL __stdcall CloseHandle(HANDLE);
extern "C" __declspec(dllimport) DWORD __stdcall GetFileSize(HANDLE, DWORD*);
struct FileHandleOwner {
    void* vtable;
    HANDLE handle;
    DWORD access;
    __forceinline FileHandleOwner() : vtable(&file_handle_vtable), handle((HANDLE)-1), access(0) {}
    ~FileHandleOwner();
    __forceinline void Close();
    __forceinline DWORD GetSize() const;
    BYTE Open(const char* path, const char* mode);
    void* ReadWhole(DWORD capacity);
};
#pragma code_seg(".text$03dtor")
FileHandleOwner::~FileHandleOwner() { vtable = &file_handle_vtable; Close(); vtable = &file_interface_vtable; }

void FileHandleOwner::Close() { if (handle != (HANDLE)-1) { CloseHandle(handle); handle = (HANDLE)-1; access = 0; } }

DWORD FileHandleOwner::GetSize() const { if (handle == (HANDLE)-1) return 0; return GetFileSize(handle, 0); }
#pragma code_seg()
