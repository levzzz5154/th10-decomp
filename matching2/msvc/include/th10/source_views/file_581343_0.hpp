#pragma once
#include "../../../build_support/include/asm_encoding.hpp"
#include "../../../build_support/include/asm_symbols.hpp"






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

extern "C" void* __cdecl entry_malloc(unsigned int size);
extern "C" void __cdecl crt_free(void* memory);

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

