#include "th10/source_views/file_581343_0.hpp"
__declspec(noinline) FileHandle::~FileHandle() {
    Close();
}


#include "th10/source_views/file_581343_0.hpp"
void FileHandle::Close() {
    if (handle != (HANDLE)-1) {
        CloseHandle(handle);
        handle = (HANDLE)-1;
        access = 0;
    }
}


#include "th10/source_views/file_581343_0.hpp"
DWORD FileHandle::Read(void* destination, DWORD size) {
    DWORD bytes_read = 0;
    if (access != kReadAccess)
        return 0;
    ReadFile(handle, destination, size, &bytes_read, 0);
    return bytes_read;
}


#include "th10/source_views/file_581343_0.hpp"
BYTE FileHandle::Write(const void* source, DWORD size) {
    DWORD bytes_written = 0;
    if (access != kWriteAccess)
        return 0;
    WriteFile(handle, source, size, &bytes_written, 0);
    return (BYTE)(size == bytes_written);
}


#include "th10/source_views/file_581343_0.hpp"
DWORD FileHandle::Tell() const {
    if (handle == (HANDLE)-1)
        return 0;
    return SetFilePointer(handle, 0, 0, kCurrentPosition);
}


#include "th10/source_views/file_581343_0.hpp"
DWORD FileHandle::GetSize() const {
    if (handle == (HANDLE)-1)
        return 0;
    return GetFileSize(handle, 0);
}


#include "th10/source_views/file_581343_0.hpp"
BYTE FileHandle::Seek(LONG distance, DWORD origin) {
    if (handle == (HANDLE)-1)
        return 0;
    SetFilePointer(handle, distance, 0, origin);
    return 1;
}


#include "../../../include/th10/source_views/file_581343_1.hpp"
#include "th10/source_views/file_581343_0.hpp"
#include "th10/source_views/file_581343_1.hpp"
void* FileHandle::ReadWhole(DWORD capacity) {
    if (access != kReadAccess)
        return 0;
    DWORD size = GetSize();
    if (size > capacity)
        return 0;
    void* buffer = entry_malloc(size);
    if (buffer == 0)
        return 0;
    DWORD position = Tell();
    if (Seek(position, 0) == 0)
        return 0;
    if (Read(buffer, size) == 0) {
        crt_free(buffer);
        return 0;
    }
    Seek(position, 0);
    return buffer;
}

