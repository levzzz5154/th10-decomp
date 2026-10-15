// Compiler context only; never selected as recovered game code. The callee
// bodies give the whole-program pass the register receivers retail uses
// (worker and timer and archive in ESI, block in EBX, registrar in EAX with
// the name in EDX); the caller makes the application arrive in EAX.
#include "../../src/game/mother/app_shutdown_00420270.cpp"
#include "../../src/platform/platform_stop_worker_0044c150.cpp"
#include "../../src/game/fps/platform_release_owned_handle_00413450.cpp"

extern Win32TimerVtable g_win32_timer_vtable;

#pragma code_seg(".text$11release")
void Win32Timer::Release() {
    vtable = &g_win32_timer_vtable;
    Cancel();
    timeEndPeriod(caps.minimum_period);
}
#pragma code_seg()

#pragma code_seg(".text$13register")
char* AnimationManager_0043e460::RegisterResource(const char* name, int resource, int parameter) {
    int index = 0;
    for (; index < 31; ++index) {
        if (records[index].resource == 0) {
            records[index].resource = resource;
            records[index].parameter = parameter;
            char* out = records[index].name;
            const char* text = name;
            while ((*out++ = *text++) != 0) {}
            records[index].state = 0;
            return const_cast<char*>(text);
        }
    }
    return (char*)(long)index;
}
#pragma code_seg()

#pragma code_seg(".text$30context")
extern "C" int __stdcall AppShutdownContext_00420270(App_00420270* apps, int count) {
    int total = 0;
    for (int index = 0; index < count; ++index)
        total += apps[index].Shutdown();
    return total;
}
#pragma code_seg()
