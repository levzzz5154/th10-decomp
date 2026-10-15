#include "th10/platform/startup_shortcut.hpp"
#include <string.h>

// 0x00439FF0: enforce one instance and detect a title naming a replay path.
#pragma code_seg(".text$01startup")
extern "C" __declspec(noinline) int __cdecl Startup_InstanceCheck_00439ff0() {
    startupMutex = CreateMutexA(0, 1, startupMutexName);
    if (GetLastError() == 0xB7) {
        startupLog.AppendLine(startupAlreadyRunning);
        return -1;
    }
    StartupInfoA info = { sizeof(StartupInfoA) };
    char modulePath[0x105];
    char consoleTitle[0x105];
    GetModuleFileNameA(0, modulePath, 0x105);
    GetConsoleTitleA(consoleTitle, 0x105);
    GetStartupInfoA(&info);
    if (info.title) {
        char* extension = strrchr(info.title, '.');
        if (asm_File_ProbeExists_0044b4d0(info.title) && extension) {
            if (_stricmp(extension, startupLinkExtension) == 0) {
                do {
                    // Retail retries the original startup title for each .lnk result.
                    ResolveShortcutTarget(info.title, consoleTitle, 0x104);
                    extension = strrchr(consoleTitle, '.');
                } while (_stricmp(extension, startupLinkExtension) == 0);
            } else {
                strcpy(consoleTitle, info.title);
            }
            if (strcmp(modulePath, consoleTitle) != 0)
                startupReplay = 1;
        }
        startupFlags &= ~0x40;
    } else {
        startupFlags |= 0x40;
    }
    return (int)(startupMutex != 0) - 1;
}
#pragma code_seg()
