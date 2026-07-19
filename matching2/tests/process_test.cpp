#include "th10/platform/process.hpp"
#include "th10/platform/text_log.hpp"
#include "th10/platform/timer.hpp"

#include <stdarg.h>
#include <stdio.h>
#include <string.h>

unsigned int DAT_004922bc;
unsigned char DAT_0049231f;

namespace {

unsigned int g_worker_waits;
unsigned int TestWorkerWait(void*, unsigned int timeout) {
    ++g_worker_waits;
    return g_worker_waits < 3 ? 0x102 : timeout;
}
unsigned int g_worker_sleeps;
void TestWorkerSleep(unsigned int) { ++g_worker_sleeps; }
unsigned int g_worker_closes;
void TestWorkerClose(void*) { ++g_worker_closes; }
unsigned int g_worker_frees;
void TestWorkerFree(void*) { ++g_worker_frees; }
static int g_interface_calls;
static int InvokeInterface(void*) { ++g_interface_calls; return 37; }

bool g_create_succeeds;
unsigned int g_exit_queries;
const char* g_application;
char* g_command_line;
STARTUPINFOA g_startup;

bool TestCreateFailure() {
    g_create_succeeds = false;
    char command[] = "--failure";
    return Platform_LaunchProcess(0, command, "game.exe", 0) == -1;
}

bool TestAsynchronousLaunch() {
    g_create_succeeds = true;
    g_exit_queries = 0;
    char command[] = "--async";
    const char* application = "game.exe";
    int result = Platform_LaunchProcess(0, command, application, 0);
    return result == 0 && g_exit_queries == 0 &&
        g_application == application &&
        g_command_line == command && g_startup.cb == sizeof(STARTUPINFOA) &&
        g_startup.dwX == 0x80000000 && g_startup.dwY == 0x80000000 &&
        g_startup.dwXCountChars == 0x50 &&
        g_startup.dwYCountChars == 0x19 && g_startup.wShowWindow == 10;
}

bool TestWaitedLaunch() {
    g_create_succeeds = true;
    g_exit_queries = 0;
    char command[] = "--wait";
    return Platform_LaunchProcess(0, command, "game.exe", 1) == 37 &&
        g_exit_queries == 3;
}

bool TestWorkerStop() {
    unsigned char state[0x20] = {};
    *(void**)(state + 4) = (void*)1;
    g_worker_waits = g_worker_sleeps = g_worker_closes = 0;
    Platform_StopWorker(state, TestWorkerWait, TestWorkerSleep, TestWorkerClose);
    return g_worker_waits == 3 && g_worker_sleeps == 2 &&
        g_worker_closes == 1 && *(void**)(state + 4) == 0 &&
        *(unsigned int*)(state + 0xC) == 1 &&
        *(unsigned int*)(state + 0x18) == 0;
}

bool TestWorkerDestroy() {
    unsigned char state[0x20] = {};
    *(void**)(state + 4) = 0;
    g_worker_frees = 0;
    Platform_DestroyWorker(state, (void*)0x1234, 0, TestWorkerWait,
                           TestWorkerSleep, TestWorkerClose, TestWorkerFree);
    if (*(void**)state != (void*)0x1234 || g_worker_frees != 0) return false;
    Platform_DestroyWorker(state, (void*)0x5678, 1, TestWorkerWait,
                           TestWorkerSleep, TestWorkerClose, TestWorkerFree);
    return *(void**)state == (void*)0x5678 && g_worker_frees == 1;
}
bool TestInterfaceInvoke() {
    unsigned char state[0x40] = {};
    g_interface_calls = 0;
    if (Platform_InvokeInterface(state, InvokeInterface) != (int)0x800401F0u)
        return false;
    *(void**)(state + 4) = (void*)1;
    return Platform_InvokeInterface(state, InvokeInterface) == 37 &&
        g_interface_calls == 1 && *(int*)(state + 0x30) == 0;
}

DWORD g_version_platform;
DWORD g_version_major;
DWORD g_version_minor;
bool g_version_struct_clean;
bool TestOsVersionCode() {
    struct VersionCase { DWORD platform, major, minor; int expected; };
    const VersionCase cases[] = {
        {0, 9, 9, 31}, {1, 4, 0, 95}, {1, 4, 10, 98},
        {1, 3, 5, 305}, {2, 5, 1, 2000}, {2, 6, 1, 6010},
        {2, 4, 0, 4000}, {3, 1, 2, -1}
    };
    for (unsigned int index = 0; index < sizeof(cases) / sizeof(cases[0]);
         ++index) {
        g_version_platform = cases[index].platform;
        g_version_major = cases[index].major;
        g_version_minor = cases[index].minor;
        g_version_struct_clean = false;
        if (Platform_GetOsVersionCode() != cases[index].expected ||
            !g_version_struct_clean) return false;
    }
    return true;
}

unsigned int g_enter_count;
unsigned int g_leave_count;
bool g_formatted_inside_lock;
bool TestTextLog() {
    TextLog log = {};
    log.cursor = log.text;
    DAT_0049231f = 0;
    g_enter_count = g_leave_count = 0;
    g_formatted_inside_lock = true;
    TextLog_Append(&log, "cfg %d", 7);
    if (strcmp(log.text, "cfg 7") != 0 || log.cursor != log.text + 5 ||
        log.dirty != 0) return false;
    TextLog_AppendLine(&log, " %s", "ready");
    if (strcmp(log.text, "cfg 7 ready") != 0 || log.dirty != 1 ||
        DAT_0049231f != 0 || g_enter_count != 2 || g_leave_count != 2 ||
        !g_formatted_inside_lock) return false;

    char* old_cursor = log.text + 0x1FF0;
    log.cursor = old_cursor;
    *old_cursor = 0;
    TextLog_Append(&log, "123456789012345");
    return log.cursor == old_cursor && *old_cursor == 0 &&
        DAT_0049231f == 0 && g_enter_count == 3 && g_leave_count == 3;
}

UINT g_killed_timer;
UINT g_ended_periods[2];
unsigned int g_end_count;
bool TestTimerRelease() {
    TimerWin32 timer = {(void**)0x1111, 73, 4};
    g_killed_timer = 0;
    g_end_count = 0;
    TimerWin32_Release(&timer, (void*)0x2222);
    if (timer.vtable != (void**)0x2222 || timer.timer_id != 0 ||
        g_killed_timer != 73 || g_end_count != 2 ||
        g_ended_periods[0] != 4 || g_ended_periods[1] != 4) return false;
    timer.timer_id = 0;
    g_killed_timer = 0;
    g_end_count = 0;
    TimerWin32_Release(&timer, (void*)0x3333);
    return g_killed_timer == 0 && g_end_count == 2;
}

} // namespace

extern "C" BOOL __stdcall CreateProcessA(
        LPCSTR application, LPSTR command_line, LPSECURITY_ATTRIBUTES,
        LPSECURITY_ATTRIBUTES, BOOL, DWORD creation_flags, LPVOID, LPCSTR,
        STARTUPINFOA* startup, PROCESS_INFORMATION* process) {
    g_application = application;
    g_command_line = command_line;
    g_startup = *startup;
    process->hProcess = (HANDLE)1;
    return g_create_succeeds && creation_flags == 0x20;
}

extern "C" BOOL __stdcall GetExitCodeProcess(HANDLE, LPDWORD exit_code) {
    ++g_exit_queries;
    *exit_code = g_exit_queries < 3 ? 0x103 : 37;
    return TRUE;
}

extern "C" BOOL __stdcall GetVersionExA(OSVERSIONINFOA* info) {
    g_version_struct_clean = info->dwOSVersionInfoSize == sizeof(*info) &&
        info->dwMajorVersion == 0 && info->dwMinorVersion == 0 &&
        info->dwBuildNumber == 0 && info->dwPlatformId == 0 &&
        info->szCSDVersion[0] == 0;
    info->dwPlatformId = g_version_platform;
    info->dwMajorVersion = g_version_major;
    info->dwMinorVersion = g_version_minor;
    return TRUE;
}

extern "C" void __stdcall EnterCriticalSection(void*) { ++g_enter_count; }
extern "C" void __stdcall LeaveCriticalSection(void*) { ++g_leave_count; }
extern "C" int __cdecl _vsprintf(char* destination, const char* format,
                                    va_list arguments) {
    if (DAT_0049231f != 1) g_formatted_inside_lock = false;
    return vsprintf(destination, format, arguments);
}
extern "C" UINT __stdcall timeKillEvent(UINT timer_id) {
    g_killed_timer = timer_id;
    return 0;
}
extern "C" UINT __stdcall timeEndPeriod(UINT period) {
    if (g_end_count < 2) g_ended_periods[g_end_count] = period;
    ++g_end_count;
    return 0;
}

int main() {
    if (!TestCreateFailure()) return 1;
    if (!TestAsynchronousLaunch()) return 2;
    if (!TestWaitedLaunch()) return 3;
    if (!TestWorkerStop()) return 4;
    if (!TestWorkerDestroy()) return 5;
    if (!TestInterfaceInvoke()) return 6;
    if (!TestOsVersionCode()) return 7;
    if (!TestTextLog()) return 8;
    if (!TestTimerRelease()) return 9;
    return 0;
}
