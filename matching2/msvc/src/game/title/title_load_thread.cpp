// 0x0042C9F0: the title screen's loading thread. Registers the title tasks and
// loads their animations; on failure it asks the application to leave. It
// then waits until the startup loader has counted 300 frames (or the skip key
// is held), drops the loading animation and lets the title's update task run.
// Compiled in the bullet_manager_load_scripts native-LTCG cluster so
// the title state travels in EBX and the animation record in EDI.
#include "th10/core/func_ctrl.hpp"

struct Title {
    unsigned char pad_000[0x0C];
    SchedulerTask* update_task;          // +0x00C
};
struct StartupLoader {
    unsigned char pad_000[0x3EC];
    int frames;                          // +0x3EC
};
struct AnimationResource6 {
    __declspec(noinline) void Release();
};
struct AnimationManager7 {
    unsigned char pad_000[0x3AD06C];
    AnimationResource6* slots_3ad06c[0x21];
};

extern "C" {
int __stdcall Title_RegisterTasks(Title* title);
__declspec(dllimport) void __stdcall Sleep(unsigned long milliseconds);
void __cdecl crt_free_startup(void* memory);
extern Title* g_title;
extern StartupLoader* g_loading;
extern AnimationManager7* g_sprt_ctrl;
extern unsigned int g_app_flags;       // held input
extern unsigned int g_main_state;       // requested application state
}

#pragma code_seg(".text$00hbstartupzmzl")
extern "C" __declspec(noinline) int __cdecl Title_LoadThread() {
    if (Title_RegisterTasks(g_title) != 0) {
        g_main_state = (~(g_app_flags >> 12) & 1) | 2;
        return 0;
    }
    if (g_loading) {
        while (g_loading->frames < 300) {
            if (g_app_flags & 0x80)
                break;
            Sleep(16);
        }
        AnimationResource6** slot = &g_sprt_ctrl->slots_3ad06c[1];
        if (*slot != 0) {
            (*slot)->Release();
            crt_free_startup(*slot);
            *slot = 0;
        }
    }
    g_title->update_task->reserved_flags |= 1;
    return 0;
}
#pragma code_seg()
