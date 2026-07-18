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
int Platform_InvokeInterface(void* state, int (*invoke)(void*)) {
    unsigned char* bytes = (unsigned char*)state;
    void* interface_ptr = *(void**)(bytes + 4);
    if (interface_ptr == 0)
        return (int)0x800401F0u;
    *(int*)(bytes + 0x30) = 0;
    return invoke != 0 ? invoke(interface_ptr) : 0;
}
