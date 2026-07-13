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
extern "C" void* __cdecl _malloc(DWORD size);
extern "C" void __cdecl _free(void* memory);

namespace {

const DWORD kReadAccess = 0x80000000;
const DWORD kWriteAccess = 0x40000000;
const DWORD kCurrentPosition = 1;

} // namespace

// 0x00435460 - Close an open Win32 file handle and reset its state.
void FileHandle::Close() {
    if (handle != (HANDLE)-1) {
        CloseHandle(handle);
        handle = (HANDLE)-1;
        access = 0;
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
BYTE FileHandle::Seek(LONG distance, DWORD origin) {
    if (handle == (HANDLE)-1) {
        return 0;
    }
    SetFilePointer(handle, distance, 0, origin);
    return 1;
}

// 0x00435580 - Read an entire readable file without changing its position.
void* FileHandle::ReadWhole(DWORD capacity) {
    if (access != kReadAccess) {
        return 0;
    }

    DWORD size = GetSize();
    if (size > capacity) {
        return 0;
    }

    void* data = _malloc(size);
    if (!data) {
        return 0;
    }

    DWORD position = Tell();
    if (Seek(position, 0)) {
        if (Read(data, size)) {
            goto succeeded;
        }
        _free(data);
    }
    return 0;

succeeded:
    Seek(position, 0);
    return data;
}
