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

// 0x0044B4D0 - Probe a path under the file-system critical-section boundary.
// The clean form accepts provider hooks so handle ownership is testable on a
// host without importing CreateFileA/CloseHandle.
bool File_ProbeExists(const char* path,
                      void* (*open_file)(const char*),
                      void (*close_file)(void*)) {
    if (open_file == 0)
        return false;
    void* handle = open_file(path);
    if (handle == (void*)-1)
        return false;
    if (close_file != 0)
        close_file(handle);
    return true;
}

// 0x0044B7E0 - Close the shared probe handle and leave its critical section.
int File_CloseProbeHandle(void* handle, void (*close_file)(void*),
                          unsigned char* critical_depth) {
    if (handle != (void*)-1) {
        if (close_file != 0)
            close_file(handle);
        if (critical_depth != 0 && *critical_depth != 0)
            --*critical_depth;
    }
    return 0;
}

// Shared body of the two retail open leaves. Entering the file-system
// critical section increments the depth byte; a failed open reports the Win32
// error through the hook, unwinds the depth, and returns -1. A successful
// open intentionally keeps the section held and the depth incremented for
// the paired read/write and close leaves.
static int File_OpenSharedImpl(const char* path, void* (*open_file)(const char*),
                               void (*report_error)(void),
                               void** shared_handle,
                               unsigned char* critical_depth) {
    if (critical_depth != 0)
        ++*critical_depth;
    void* handle = 0;
    if (open_file != 0)
        handle = open_file(path);
    if (shared_handle != 0)
        *shared_handle = handle;
    if (handle == (void*)-1 || handle == 0) {
        if (report_error != 0)
            report_error();
        if (critical_depth != 0 && *critical_depth != 0)
            --*critical_depth;
        return -1;
    }
    return 0;
}

// 0x0044B620 - Create/truncate the shared output file (GENERIC_WRITE,
// CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL) inside the critical section.
int File_OpenSharedWrite(const char* path, void* (*open_file)(const char*),
                         void (*report_error)(void),
                         void** shared_handle, unsigned char* critical_depth) {
    return File_OpenSharedImpl(
        path, open_file, report_error, shared_handle, critical_depth);
}

// 0x0044B6B0 - Open the shared input file (GENERIC_READ, OPEN_EXISTING,
// FILE_FLAG_SEQUENTIAL_SCAN | FILE_ATTRIBUTE_NORMAL) inside the critical
// section.
int File_OpenSharedRead(const char* path, void* (*open_file)(const char*),
                        void (*report_error)(void),
                        void** shared_handle, unsigned char* critical_depth) {
    return File_OpenSharedImpl(
        path, open_file, report_error, shared_handle, critical_depth);
}

// 0x0044B540 - Create/truncate a file and write one buffer under the
// file-system critical section (GENERIC_WRITE, FILE_SHARE_READ,
// CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL). Retail enters 0x004922A4 first and
// only then raises the depth byte; every exit leaves the section and unwinds
// the depth. An open failure additionally reports the Win32 error through the
// hook (retail formats the system message and discards it) and returns -1, a
// short write returns -2 after closing, a complete write returns 0.
int File_WriteWholeFile(const char* path, const void* source, DWORD size,
                        void* (*open_file)(const char*),
                        DWORD (*write_file)(void*, const void*, DWORD),
                        void (*close_file)(void*),
                        void (*report_error)(void),
                        unsigned char* critical_depth,
                        void (*enter_section)(void),
                        void (*leave_section)(void)) {
    if (enter_section != 0)
        enter_section();
    if (critical_depth != 0)
        ++*critical_depth;
    void* handle = 0;
    if (open_file != 0)
        handle = open_file(path);
    if (handle == (void*)-1 || handle == 0) {
        if (report_error != 0)
            report_error();
        if (leave_section != 0)
            leave_section();
        if (critical_depth != 0 && *critical_depth != 0)
            --*critical_depth;
        return -1;
    }
    DWORD written = 0;
    if (write_file != 0)
        written = write_file(handle, source, size);
    if (close_file != 0)
        close_file(handle);
    if (leave_section != 0)
        leave_section();
    if (critical_depth != 0 && *critical_depth != 0)
        --*critical_depth;
    return written == size ? 0 : -2;
}

// 0x0044B740 - Write a complete shared diagnostic record, retiring the
// handle and critical-section depth when the provider reports a short write.
int File_WriteShared(void* handle, const void* source, DWORD size,
                     DWORD (*write_file)(void*, const void*, DWORD),
                     void (*close_file)(void*), unsigned char* critical_depth) {
    if (handle == (void*)-1 || write_file == 0)
        return -1;
    DWORD written = write_file(handle, source, size);
    if (written != size) {
        if (close_file != 0)
            close_file(handle);
        if (critical_depth != 0 && *critical_depth != 0)
            --*critical_depth;
        return -2;
    }
    return 0;
}

// 0x0044B790 - Allocate and fill one record from the shared diagnostic file.
// Allocation failure retires the shared handle; the retail leaf leaves the
// read count to the caller's surrounding protocol.
void* File_ReadShared(void* handle, DWORD size,
                      void* (*allocate)(DWORD),
                      DWORD (*read_file)(void*, void*, DWORD),
                      void (*close_file)(void*)) {
    if (handle == (void*)-1 || allocate == 0 || read_file == 0)
        return 0;
    void* buffer = allocate(size);
    if (buffer == 0) {
        if (close_file != 0)
            close_file(handle);
        return 0;
    }
    read_file(handle, buffer, size);
    return buffer;
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
