// 0x0042C9F0: the title screen's loading thread. Registers the title tasks and
// loads their animations; on failure it asks the application to leave. It
// then waits until the startup loader has counted 300 frames (or the skip key
// is held), drops the loading animation and lets the title's update task run.
// Compiled in the bullet_manager_load_scripts_0040ae70 native-LTCG cluster so
// the title state travels in EBX and the animation record in EDI.
#include "th10/game/scheduler.hpp"

struct TitleState_0042caa0 {
    unsigned char pad_000[0x0C];
    SchedulerTask* update_task;          // +0x00C
};
struct StartupLoader_00477820 {
    unsigned char pad_000[0x3EC];
    int frames;                          // +0x3EC
};
struct AnimationResource_00447810 {
    __declspec(noinline) void Release();
};
struct AnimationManager_0042c800 {
    unsigned char pad_000[0x3AD06C];
    AnimationResource_00447810* slots_3ad06c[0x21];
};

extern "C" {
int __stdcall Title_RegisterTasks_0042caa0(TitleState_0042caa0* title);
__declspec(dllimport) void __stdcall Sleep(unsigned long milliseconds);
void __cdecl entry_free_004524a1(void* memory);
extern TitleState_0042caa0* data_0047784c;
extern StartupLoader_00477820* g_loading;
extern AnimationManager_0042c800* data_00491c10;
extern unsigned int data_00491ff4;       // held input
extern unsigned int data_00491fb8;       // requested application state
}

#pragma code_seg(".text$00hbstartupzmzl")
extern "C" __declspec(noinline) int __cdecl TitleLoadThread_0042c9f0() {
    if (Title_RegisterTasks_0042caa0(data_0047784c) != 0) {
        data_00491fb8 = (~(data_00491ff4 >> 12) & 1) | 2;
        return 0;
    }
    if (g_loading) {
        while (g_loading->frames < 300) {
            if (data_00491ff4 & 0x80)
                break;
            Sleep(16);
        }
        AnimationResource_00447810** slot = &data_00491c10->slots_3ad06c[1];
        if (*slot != 0) {
            (*slot)->Release();
            entry_free_004524a1(*slot);
            *slot = 0;
        }
    }
    data_0047784c->update_task->reserved_flags |= 1;
    return 0;
}
#pragma code_seg()
