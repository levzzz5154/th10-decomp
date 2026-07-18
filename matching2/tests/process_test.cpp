#include "th10/platform/process.hpp"

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

int main() {
    if (!TestCreateFailure()) return 1;
    if (!TestAsynchronousLaunch()) return 2;
    if (!TestWaitedLaunch()) return 3;
    if (!TestWorkerStop()) return 4;
    if (!TestWorkerDestroy()) return 5;
    if (!TestInterfaceInvoke()) return 6;
    return 0;
}
