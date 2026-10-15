// Scan to the first supported mode, then open the resolved path. Native LTCG
// preserves the public thiscall ABI and compiler-generated stack protection.
#include "th10/platform/file.hpp"
extern "C" __declspec(dllimport) BOOL __stdcall DeleteFileA(LPCSTR path);
extern "C" __declspec(dllimport) HANDLE __stdcall CreateFileA(LPCSTR path, DWORD access,
                                                              DWORD sharing, void* security,
                                                              DWORD disposition, DWORD attributes,
                                                              HANDLE template_file);
extern "C" __declspec(dllimport) DWORD __stdcall SetFilePointer(HANDLE file, LONG distance,
                                                                LONG* high_distance, DWORD origin);
extern "C" __declspec(noinline) void __fastcall ResolvePath435610(char* output, const char* path);
#pragma code_seg(".text$01open")
BYTE FileHandle::Open(const char* path, const char* mode) {
    char resolved_path[260];
    DWORD disposition = 0;
    int append = 0;
    Close();
    const char* cursor = mode;
    char current = *mode;
    if (current) {
        do {
            if (current == 'r') {
                access = 0x80000000;
                disposition = 3;
                goto Selected;
            }
            if (current == 'w') {
                DeleteFileA(path);
                access = 0x40000000;
                disposition = 2;
                goto Selected;
            }
            if (current == 'a') {
                append = 1;
                access = 0x40000000;
                disposition = 4;
                goto Selected;
            }
            current = *++cursor;
        } while (current);
        return 0;
    }
Selected:
    // The delete callback can alter the selected byte, so read it again.
    if (!*cursor)
        return 0;
    ResolvePath435610(resolved_path, path);
    HANDLE opened = CreateFileA(resolved_path, access, 1, 0, disposition, 0x08000080, 0);
    handle = opened;
    if (opened == (HANDLE)-1)
        return 0;
    if (append)
        SetFilePointer(opened, 0, 0, 2);
    return 1;
}
#pragma code_seg()
