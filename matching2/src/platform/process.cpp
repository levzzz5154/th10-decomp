#include "th10/platform/process.hpp"

// 0x00436570 - Launch a process and optionally poll until it exits.
int Platform_LaunchProcess(void*, char* command_line,
                           const char* application_name, int wait_for_exit) {
    PROCESS_INFORMATION process = {};
    STARTUPINFOA startup = {};
    startup.cb = sizeof(startup);
    startup.dwX = 0x80000000;
    startup.dwY = 0x80000000;
    startup.dwXSize = 0x80000000;
    startup.dwYSize = 0x80000000;
    startup.dwXCountChars = 0x50;
    startup.dwYCountChars = 0x19;
    startup.wShowWindow = 10;

    if (!CreateProcessA(application_name, command_line, 0, 0, FALSE, 0x20,
                        0, 0, &startup, &process)) {
        return -1;
    }

    if (!wait_for_exit)
        return 0;

    DWORD exit_code = 0x103;
    do {
        GetExitCodeProcess(process.hProcess, &exit_code);
    } while (exit_code == 0x103);
    return (int)exit_code;
}

// 0x0044C130/0x0044C150 - Stop a worker handle, polling pending waits and
// clearing the worker's state fields before closing the handle.
void Platform_StopWorker(void* state, unsigned int (*wait)(void*, unsigned int),
                         void (*sleep)(unsigned int), void (*close)(void*)) {
    unsigned char* bytes = (unsigned char*)state;
    void* handle = *(void**)(bytes + 4);
    if (handle == 0)
        return;
    do {
        *(unsigned int*)(bytes + 0xC) = 1;
        *(unsigned int*)(bytes + 0x10) = 0;
        unsigned int result = wait ? wait(handle, 200) : 0;
        if (result != 0x102)
            break;
        if (sleep)
            sleep(1);
    } while (true);
    if (close)
        close(handle);
    *(void**)(bytes + 4) = 0;
    *(unsigned int*)(bytes + 0x18) = 0;
}

// 0x0044C100 - Restore the worker vtable, stop the worker, and honor the
// deleting-destructor flag.
void Platform_DestroyWorker(void* state, void* vtable, unsigned char flags,
                            unsigned int (*wait)(void*, unsigned int),
                            void (*sleep)(unsigned int),
                            void (*close)(void*), void (*free_memory)(void*)) {
    *(void**)state = vtable;
    Platform_StopWorker(state, wait, sleep, close);
    if ((flags & 1u) != 0 && free_memory != 0)
        free_memory(state);
}

// 0x0044D5B0 - Invoke the interface operation when present, otherwise return
// the retail COM E_NOINTERFACE-style status.
#ifdef _MSC_VER
__declspec(naked) int Platform_InvokeInterface(void* state,
                                               int (*invoke)(void*)) {
    __asm {
        mov eax, [ecx+4]
        test eax, eax
        jnz loc_44D5BD
        mov eax, 800401F0h
        ret
loc_44D5BD:
        mov dword ptr [ecx+30h], 0
        mov eax, [eax]
        mov ecx, [eax]
        push eax
        call dword ptr [ecx+48h]
        ret
    }
}
#else
int Platform_InvokeInterface(void* state, int (*invoke)(void*)) {
    unsigned char* bytes = (unsigned char*)state;
    void* interface_ptr = *(void**)(bytes + 4);
    if (interface_ptr == 0)
        return (int)0x800401F0u;
    *(int*)(bytes + 0x30) = 0;
    return invoke != 0 ? invoke(interface_ptr) : 0;
}
#endif

extern "C" __declspec(dllimport) BOOL __stdcall GetVersionExA(
    OSVERSIONINFOA* version_info);

// 0x0044BD10 - Map the GetVersionExA result onto the game's numeric OS
// codes: Win32s reports 31, Windows 95/98 report 95/98 (any other 9x 4.x
// minor collapses to 98), NT 5.x reports 2000, other NT releases report
// (major * 100 + minor) * 10, non-4.x 9x releases report major * 100 +
// minor, and unknown platforms report -1. No surviving retail caller.
int Platform_GetOsVersionCode(void) {
    OSVERSIONINFOA info = {};
    info.dwOSVersionInfoSize = sizeof(info);
    GetVersionExA(&info);
    switch (info.dwPlatformId) {
    case 0:
        return 31;
    case 1:
        if (info.dwMajorVersion == 4)
            return info.dwMinorVersion == 0 ? 95 : 98;
        return (int)(info.dwMajorVersion * 100 + info.dwMinorVersion);
    case 2:
        if (info.dwMajorVersion == 5)
            return 2000;
        return (int)(info.dwMajorVersion * 100 + info.dwMinorVersion) * 10;
    default:
        return -1;
    }
}
