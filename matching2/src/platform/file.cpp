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

namespace {

const DWORD kReadAccess = 0x80000000;
const DWORD kWriteAccess = 0x40000000;
const DWORD kCurrentPosition = 1;

} // namespace

// 0x00435460 - Close an open Win32 file handle and reset its state.
void __fastcall FileHandle_Close(FileHandle* file) {
    if (file->handle != (HANDLE)-1) {
        CloseHandle(file->handle);
        file->handle = (HANDLE)-1;
        file->access = 0;
    }
}

// 0x00435490 - Read bytes when the handle was opened for reading.
DWORD FileHandle::Read(void* destination, DWORD size) {
    DWORD bytes_read = 0;
    if (access != kReadAccess) {
        return 0;
    }
    ReadFile(handle, destination, size, &bytes_read, 0);
    return bytes_read;
}

// 0x004354D0 - Write a complete buffer when opened for writing.
BYTE FileHandle::Write(const void* source, DWORD size) {
    DWORD bytes_written = 0;
    if (access != kWriteAccess) {
        return 0;
    }
    WriteFile(handle, source, size, &bytes_written, 0);
    return (BYTE)(size == bytes_written);
}

// 0x00435510 - Return the current Win32 file pointer.
DWORD FileHandle::Tell() const {
    if (handle == (HANDLE)-1) {
        return 0;
    }
    return SetFilePointer(handle, 0, 0, kCurrentPosition);
}

// 0x00435530 - Return the low 32 bits of the file size.
DWORD FileHandle::GetSize() const {
    if (handle == (HANDLE)-1) {
        return 0;
    }
    return GetFileSize(handle, 0);
}

// 0x00435550 - Move the Win32 file pointer.
bool FileHandle::Seek(LONG distance, DWORD origin) {
    if (handle == (HANDLE)-1) {
        return false;
    }
    SetFilePointer(handle, distance, 0, origin);
    return true;
}
