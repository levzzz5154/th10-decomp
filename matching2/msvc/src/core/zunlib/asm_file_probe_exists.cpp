#include "th10/source_views/file_581343_0.hpp"
#include "th10/source_views/file_581343_1.hpp"
#include "th10/source_views/file_581343_2.hpp"
int __stdcall asm_File_ProbeExists_0044b4d0(LPCSTR path) {
    (*(EnterCriticalSectionFn*)&imp_EnterCriticalSection)(&g_file_critical_section);
    ++g_file_critical_depth;
    HANDLE handle = (*(CreateFileFn*)&imp_CreateFileA)(
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


#include "../../../include/th10/source_views/file_581343_3.hpp"
#include "th10/source_views/file_581343_0.hpp"
#include "th10/source_views/file_581343_1.hpp"
#include "th10/source_views/file_581343_2.hpp"
#include "th10/source_views/file_581343_3.hpp"
int __stdcall asm_File_OpenSharedWrite_0044b620(LPCSTR path) {
    (*(EnterCriticalSectionFn*)&imp_EnterCriticalSection)(&g_file_critical_section);
    ++g_file_critical_depth;
    HANDLE handle = (*(CreateFileFn*)&imp_CreateFileA)(
        path, 0x40000000, 1, 0, 2, 0x80, 0);
    g_file_probe_handle = handle;
    if (handle == (HANDLE)-1) {
        LPSTR message;
        (*(FormatMessageFn*)&imp_FormatMessageA)(
            0x1300, 0, (*(GetLastErrorFn*)&imp_GetLastError)(), 0x400, &message, 0, 0);
        (*(LocalFreeFn*)&imp_LocalFree)(message);
        LeaveCriticalSection(&g_file_critical_section);
        --g_file_critical_depth;
        return -1;
    }
    return 0;
}


#include "../../../include/th10/source_views/file_581343_4.hpp"
#include "th10/source_views/file_581343_0.hpp"
#include "th10/source_views/file_581343_1.hpp"
#include "th10/source_views/file_581343_2.hpp"
#include "th10/source_views/file_581343_3.hpp"
#include "th10/source_views/file_581343_4.hpp"
int __stdcall asm_File_OpenSharedRead_0044b6b0(LPCSTR path) {
    (*(EnterCriticalSectionFn*)&imp_EnterCriticalSection)(&g_file_critical_section);
    ++g_file_critical_depth;
    HANDLE handle = (*(CreateFileFn*)&imp_CreateFileA)(
        path, 0x80000000, 1, 0, 3, 0x8000080, 0);
    g_file_probe_handle = handle;
    if (handle == (HANDLE)-1) {
        LPSTR message;
        (*(FormatMessageFn*)&imp_FormatMessageA)(
            0x1300, 0, (*(GetLastErrorFn*)&imp_GetLastError)(), 0x400, &message, 0, 0);
        (*(LocalFreeFn*)&imp_LocalFree)(message);
        LeaveCriticalSection(&g_file_critical_section);
        --g_file_critical_depth;
        return -1;
    }
    return 0;
}


#include "../../../include/th10/source_views/file_581343_5.hpp"
#include "th10/source_views/file_581343_0.hpp"
#include "th10/source_views/file_581343_1.hpp"
#include "th10/source_views/file_581343_2.hpp"
#include "th10/source_views/file_581343_3.hpp"
#include "th10/source_views/file_581343_4.hpp"
#include "th10/source_views/file_581343_5.hpp"
int File_CloseProbeHandle() {
    HANDLE handle = g_file_probe_handle;
    if (handle != (HANDLE)-1) {
        CloseHandle(handle);
        LeaveCriticalSection(&g_file_critical_section);
        --g_file_critical_depth;
    }
    return 0;
}

