#include "th10/platform/file.hpp"

extern "C" __declspec(dllimport) BOOL __stdcall CloseHandle(HANDLE handle);
extern "C" __declspec(dllimport) BOOL __stdcall ReadFile(
    HANDLE handle, void* buffer, DWORD size, DWORD* bytes_read, void* overlapped);
extern "C" __declspec(dllimport) BOOL __stdcall WriteFile(
    HANDLE handle, const void* buffer, DWORD size, DWORD* bytes_written,
    void* overlapped);
extern "C" __declspec(dllimport) DWORD __stdcall SetFilePointer(
    HANDLE handle, LONG distance, LONG* distance_high, DWORD origin);
extern "C" __declspec(dllimport) DWORD __stdcall GetFileSize(
    HANDLE handle, DWORD* size_high);

struct FileCriticalSection;
extern "C" HANDLE g_file_probe_handle;
extern "C" FileCriticalSection g_file_critical_section;
extern "C" unsigned char g_file_critical_depth;
extern "C" __declspec(dllimport) void __stdcall LeaveCriticalSection(
    FileCriticalSection* section);

namespace {
const DWORD kReadAccess = 0x80000000;
const DWORD kWriteAccess = 0x40000000;
const DWORD kCurrentPosition = 1;
} // namespace

FileHandle::FileHandle() : handle((HANDLE)-1), access(0) {
}

__declspec(noinline) FileHandle::~FileHandle() {
    Close();
}

void FileHandle::Close() {
    if (handle != (HANDLE)-1) {
        CloseHandle(handle);
        handle = (HANDLE)-1;
        access = 0;
    }
}

DWORD FileHandle::Read(void* destination, DWORD size) {
    DWORD bytes_read = 0;
    if (access != kReadAccess)
        return 0;
    ReadFile(handle, destination, size, &bytes_read, 0);
    return bytes_read;
}

BYTE FileHandle::Write(const void* source, DWORD size) {
    DWORD bytes_written = 0;
    if (access != kWriteAccess)
        return 0;
    WriteFile(handle, source, size, &bytes_written, 0);
    return (BYTE)(size == bytes_written);
}

DWORD FileHandle::Tell() const {
    if (handle == (HANDLE)-1)
        return 0;
    return SetFilePointer(handle, 0, 0, kCurrentPosition);
}

DWORD FileHandle::GetSize() const {
    if (handle == (HANDLE)-1)
        return 0;
    return GetFileSize(handle, 0);
}

BYTE FileHandle::Seek(LONG distance, DWORD origin) {
    if (handle == (HANDLE)-1)
        return 0;
    SetFilePointer(handle, distance, 0, origin);
    return 1;
}

// 0x0044B7E0 - Close the shared probe handle, release the file subsystem's
// critical section, and balance its nesting counter.
int File_CloseProbeHandle() {
    HANDLE handle = g_file_probe_handle;
    if (handle != (HANDLE)-1) {
        CloseHandle(handle);
        LeaveCriticalSection(&g_file_critical_section);
        --g_file_critical_depth;
    }
    return 0;
}
