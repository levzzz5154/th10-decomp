#include "asm_encoding.hpp"
#include "asm_symbols.hpp"






// Recovered semantic C++ definitions.
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

extern "C" void* __cdecl entry_malloc_00452706(unsigned int size);
extern "C" void __cdecl entry_free_00452422(void* memory);

struct FileCriticalSection;
extern "C" HANDLE g_file_probe_handle;
extern "C" FileCriticalSection g_file_critical_section;
extern "C" unsigned char g_file_critical_depth;
extern "C" __declspec(dllimport) void __stdcall LeaveCriticalSection(
    FileCriticalSection* section);

// The KERNEL32 slots at 0x004660B0..0x00466128 are bound by the retail layout
// script under their slot names, so the calls go through the slot's stored
// pointer exactly as the retail import thunks do.
typedef void (__stdcall* EnterCriticalSectionFn)(void* section);
typedef HANDLE (__stdcall* CreateFileFn)(LPCSTR path, DWORD access, DWORD share,
                                         void* attributes, DWORD creation,
                                         DWORD flags, HANDLE template_file);
typedef DWORD (__stdcall* GetLastErrorFn)(void);
typedef DWORD (__stdcall* FormatMessageFn)(DWORD flags, void* source, DWORD message_id,
                                           DWORD language_id, LPSTR* buffer,
                                           DWORD buffer_size, void* arguments);
typedef HANDLE (__stdcall* LocalFreeFn)(void* memory);

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

// 0x00435580 - Read the whole file into a fresh heap block when the file is
// no larger than the caller's capacity; the position is restored around the
// read and the block is released if either step fails.
void* FileHandle::ReadWhole(DWORD capacity) {
    if (access != kReadAccess)
        return 0;
    DWORD size = GetSize();
    if (size > capacity)
        return 0;
    void* buffer = entry_malloc_00452706(size);
    if (buffer == 0)
        return 0;
    DWORD position = Tell();
    if (Seek(position, 0) == 0)
        return 0;
    if (Read(buffer, size) == 0) {
        entry_free_00452422(buffer);
        return 0;
    }
    Seek(position, 0);
    return buffer;
}

// 0x0044B4D0 - Probe one path inside the file subsystem's critical section:
// open it for reading, close it at once and report whether it was there. The
// nesting counter brackets the whole probe.
int __stdcall asm_File_ProbeExists_0044b4d0(LPCSTR path) {
    (*(EnterCriticalSectionFn*)&data_004660b0)(&g_file_critical_section);
    ++g_file_critical_depth;
    HANDLE handle = (*(CreateFileFn*)&data_004660c4)(
        path, 0x80000000, 1, 0, 3, 0x8000080, 0);
    if (handle != (HANDLE)-1) {
        CloseHandle(handle);
        LeaveCriticalSection(&g_file_critical_section);
        --g_file_critical_depth;
        return 1;
    }
    LeaveCriticalSection(&g_file_critical_section);
    --g_file_critical_depth;
    return 0;
}

// 0x0044B620 - Open the shared probe file for writing, truncating it. A
// failure formats the Win32 error text, releases it again and unwinds the
// critical section, reporting -1; the shared handle is -1 after a failure.
int __stdcall asm_File_OpenSharedWrite_0044b620(LPCSTR path) {
    (*(EnterCriticalSectionFn*)&data_004660b0)(&g_file_critical_section);
    ++g_file_critical_depth;
    HANDLE handle = (*(CreateFileFn*)&data_004660c4)(
        path, 0x40000000, 1, 0, 2, 0x80, 0);
    g_file_probe_handle = handle;
    if (handle == (HANDLE)-1) {
        LPSTR message;
        (*(FormatMessageFn*)&data_00466124)(
            0x1300, 0, (*(GetLastErrorFn*)&data_0046610c)(), 0x400, &message, 0, 0);
        (*(LocalFreeFn*)&data_00466128)(message);
        LeaveCriticalSection(&g_file_critical_section);
        --g_file_critical_depth;
        return -1;
    }
    return 0;
}

// 0x0044B6B0 - Open the shared probe file for reading, failing the same way as
// the write open does.
int __stdcall asm_File_OpenSharedRead_0044b6b0(LPCSTR path) {
    (*(EnterCriticalSectionFn*)&data_004660b0)(&g_file_critical_section);
    ++g_file_critical_depth;
    HANDLE handle = (*(CreateFileFn*)&data_004660c4)(
        path, 0x80000000, 1, 0, 3, 0x8000080, 0);
    g_file_probe_handle = handle;
    if (handle == (HANDLE)-1) {
        LPSTR message;
        (*(FormatMessageFn*)&data_00466124)(
            0x1300, 0, (*(GetLastErrorFn*)&data_0046610c)(), 0x400, &message, 0, 0);
        (*(LocalFreeFn*)&data_00466128)(message);
        LeaveCriticalSection(&g_file_critical_section);
        --g_file_critical_depth;
        return -1;
    }
    return 0;
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
