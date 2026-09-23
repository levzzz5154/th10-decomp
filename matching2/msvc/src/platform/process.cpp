#include <string.h>
#include "asm_encoding.hpp"
#include "th10/platform/windows_types.hpp"
#include "asm_symbols.hpp"
#include "th10/platform/sound_buffer.hpp"

// 0x00436570..0x00436638: create a process and optionally poll for its exit.
// The retail entry uses a fastcall-shaped ABI: ECX is an unused context slot,
// EDX carries the mutable command line, and the two stack arguments are the
// application name followed by the wait flag. A fastcall function with four
// parameters retains that register/stack split and callee-cleans 8 stack bytes.
extern "C" int __fastcall Platform_LaunchProcess_00436570(
    void* ignored_ecx, char* command_line, const char* application_name,
    int wait_for_exit) {
    (void)ignored_ecx;

    PROCESS_INFORMATION process_info;
    STARTUPINFOA startup_info;

    startup_info.cb = 0x44;
    startup_info.lpReserved = 0;
    startup_info.lpDesktop = 0;
    startup_info.lpTitle = 0;
    startup_info.dwX = 0x80000000u;
    startup_info.dwY = 0x80000000u;
    startup_info.dwXSize = 0x80000000u;
    startup_info.dwYSize = 0x80000000u;
    startup_info.dwXCountChars = 0x50;
    startup_info.dwYCountChars = 0x19;
    startup_info.dwFillAttribute = 0;
    startup_info.dwFlags = 0;
    startup_info.wShowWindow = 10;
    startup_info.cbReserved2 = 0;
    startup_info.lpReserved2 = 0;
    startup_info.hStdInput = 0;
    startup_info.hStdOutput = 0;
    startup_info.hStdError = 0;

    if (!CreateProcessA(application_name, command_line, 0, 0, FALSE, 0x20,
                        0, 0, &startup_info, &process_info)) {
        return -1;
    }

    if (wait_for_exit == 0)
        return 0;

    DWORD exit_code = 0x103;
    do {
        GetExitCodeProcess(process_info.hProcess, &exit_code);
    } while (exit_code == 0x103);

    return (int)exit_code;
}

extern "C" __declspec(dllimport) BOOL __stdcall GetVersionExA(OSVERSIONINFOA*);

int Platform_GetOsVersionCode() {
    OSVERSIONINFOA version_info;
    memset(&version_info, 0, sizeof(version_info));
    version_info.dwOSVersionInfoSize = sizeof(version_info);
    GetVersionExA(&version_info);

    switch (version_info.dwPlatformId) {
    case 0:
        return 31;
    case 1:
        if (version_info.dwMajorVersion == 4)
            return version_info.dwMinorVersion != 0 ? 98 : 95;
        return version_info.dwMajorVersion * 100 + version_info.dwMinorVersion;
    case 2:
        if (version_info.dwMajorVersion == 5)
            return 2000;
        return (version_info.dwMajorVersion * 100 + version_info.dwMinorVersion) * 10;
    default:
        return -1;
    }
}



// 0x0044D5B0..0x0044D5CC: stop the first DirectSound buffer and clear the
// wrapper's playing flag. DirectSound methods use their stdcall COM ABI.
int __fastcall Platform_InvokeInterface(SoundBuffer* sound_buffer) {
    DirectSoundBuffer** const buffers = sound_buffer->buffers;
    if (buffers == 0)
        return (int)0x800401F0u;

    sound_buffer->is_playing = 0;
    DirectSoundBuffer* const buffer = buffers[0];
    return buffer->vtable->stop(buffer);
}
