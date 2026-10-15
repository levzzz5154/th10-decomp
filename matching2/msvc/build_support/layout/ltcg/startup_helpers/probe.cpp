#include "th10/platform/startup_shortcut.hpp"
typedef void (__stdcall* EnterCriticalSectionFn)(void*);
typedef HANDLE (__stdcall* CreateFileFn)(const char*, DWORD, DWORD, void*, DWORD, DWORD, HANDLE);
#pragma code_seg(".text$03probe")
__declspec(noinline) int __stdcall asm_File_ProbeExists_0044b4d0(const char* path) {
    (*(EnterCriticalSectionFn*)&data_004660b0)(&g_file_critical_section);
    ++g_file_critical_depth;
    HANDLE handle = (*(CreateFileFn*)&data_004660c4)(path, 0x80000000, 1, 0, 3, 0x8000080, 0);
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
#pragma code_seg()
