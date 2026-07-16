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
extern "C" __declspec(dllimport) HANDLE __stdcall CreateFileA(
    const char* path, DWORD access, DWORD share_mode, void* security,
    DWORD creation_disposition, DWORD flags, HANDLE template_file);
extern "C" __declspec(dllimport) BOOL __stdcall DeleteFileA(const char* path);
extern "C" void* __cdecl _malloc(DWORD size);
extern "C" void __cdecl _free(void* memory);

namespace {

const DWORD kReadAccess = 0x80000000;
const DWORD kWriteAccess = 0x40000000;
const DWORD kCurrentPosition = 1;
const DWORD kEndPosition = 2;
const DWORD kShareRead = 1;
const DWORD kCreateAlways = 2;
const DWORD kOpenExisting = 3;
const DWORD kOpenAlways = 4;
const DWORD kSequentialNormalFile = 0x08000080;

} // namespace

// Clean constructor corresponding to the initialization helper at 0x00435300.
FileHandle::FileHandle() : handle((HANDLE)-1), access(0) {
}

// 0x00435340 - Restore the base vtable and release an open Win32 handle.
__declspec(noinline) FileHandle::~FileHandle() {
    Close();
}

// 0x00435610 - Preserve absolute drive paths or resolve relative paths beside
// the executable.
void File_ResolvePath(const char* path, char output[260]) {
    const char* cursor = path;
    while (*cursor != 0 && *cursor != ':') {
        ++cursor;
    }
    if (*cursor == ':') {
        do {
            *output++ = *path;
        } while (*path++ != 0);
        return;
    }

    GetModuleFileNameA(0, output, 260);
    char* separator = output;
    char* last_separator = 0;
    while (*separator != 0) {
        if (*separator == '\\') {
            last_separator = separator;
        }
        ++separator;
    }
    if (last_separator) {
        last_separator[1] = 0;
    } else {
        output[0] = 0;
    }

    while (*output != 0) {
        ++output;
    }
    do {
        *output++ = *path;
    } while (*path++ != 0);
}

// 0x00435370 - Open a Win32 file using TH10's fopen-like mode parsing.
BYTE FileHandle::Open(const char* path, const char* mode) {
    DWORD creation_disposition = 0;
    bool append = false;
    Close();

    const char* mode_cursor = mode;
    while (*mode_cursor != 0) {
        if (*mode_cursor == 'r') {
            access = kReadAccess;
            creation_disposition = kOpenExisting;
            break;
        }
        if (*mode_cursor == 'w') {
            DeleteFileA(path);
            access = kWriteAccess;
            creation_disposition = kCreateAlways;
            break;
        }
        if (*mode_cursor == 'a') {
            append = true;
            access = kWriteAccess;
            creation_disposition = kOpenAlways;
            break;
        }
        ++mode_cursor;
    }
    if (*mode_cursor == 0) {
        return 0;
    }

    char resolved_path[260];
    File_ResolvePath(path, resolved_path);
    handle = CreateFileA(
        resolved_path,
        access,
        kShareRead,
        0,
        creation_disposition,
        kSequentialNormalFile,
        0);
    if (handle == (HANDLE)-1) {
        return 0;
    }
    if (append) {
        SetFilePointer(handle, 0, 0, kEndPosition);
    }
    return 1;
}

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
    if (Seek(0, 0)) {
        if (Read(data, size) == size) {
            goto succeeded;
        }
        _free(data);
    }
    return 0;

succeeded:
    Seek(position, 0);
    return data;
}
