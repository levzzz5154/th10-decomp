// Behavioral candidate for FileHandle::Open (0x00435370, 239 bytes).
// The thiscall interface is known; resolver ABI and native MSVC stack-cookie
// lowering remain unverified. See recovery_notes/file_open_and_resolve.md.
#include "th10/platform/file.hpp"

extern "C" __declspec(dllimport) BOOL __stdcall DeleteFileA(LPCSTR path);
extern "C" __declspec(dllimport) HANDLE __stdcall CreateFileA(
    LPCSTR path, DWORD access, DWORD sharing, void* security, DWORD disposition,
    DWORD attributes, HANDLE template_file);
extern "C" __declspec(dllimport) DWORD __stdcall SetFilePointer(
    HANDLE file, LONG distance, LONG* high_distance, DWORD origin);

BYTE FileHandle::Open(const char* path, const char* mode) {
    char resolved_path[260];
    DWORD disposition = 0;
    bool append = false;
    Close();
    // Ignore unrecognized prefixes and stop at the first supported mode.
    while (*mode) {
        if (*mode == 'r') {
            access = 0x80000000;
            disposition = 3;
            break;
        }
        if (*mode == 'w') {
            DeleteFileA(path);
            access = 0x40000000;
            disposition = 2;
            break;
        }
        if (*mode == 'a') {
            append = true;
            access = 0x40000000;
            disposition = 4;
            break;
        }
        ++mode;
    }
    // DeleteFileA may change the caller's mode storage. Retail reads it again.
    if (!*mode)
        return 0;
    File_ResolvePath(path, resolved_path);
    HANDLE opened = CreateFileA(resolved_path, access, 1, 0, disposition, 0x08000080, 0);
    handle = opened;
    if (opened == (HANDLE)-1)
        return 0;
    if (append)
        SetFilePointer(opened, 0, 0, 2);
    return 1;
}
