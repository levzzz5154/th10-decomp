// 0x00422220..0x00422356: release a manager: remove its scheduler task pair,
// destroy and free its twenty-five owned objects, mark the animation it names
// (and that animation's children, unless already flagged) for removal, and
// clear the global pointer at 0x00477830.  The lookup of 0x004491C0 is inlined
// here.  Compiled in the scheduler's native-LTCG cluster so that its calls to
// 0x00449F60 load the task register first.
#include "th10/game/scheduler_remove_locked.hpp"
#include "th10/render/animation_mark_for_removal.hpp"

struct ManagerOwned_00422220;

struct Manager_00422220 {
    SchedulerTaskPair tasks;                    // +0x000 (tasks at +0x08, +0x0C)
    unsigned char unknown_010[0x1DC - 0x10];
    int animation_id;                           // +0x1DC
    unsigned char unknown_1e0[0x1EC - 0x1E0];
    ManagerOwned_00422220* owned[25];           // +0x1EC
};

extern "C" void __stdcall ManagerOwned_Destroy_004294a0(ManagerOwned_00422220* owned);
extern "C" void* g_pause;

#pragma code_seg(".text$00hbstartupzm")
extern "C" __declspec(noinline) int __stdcall Manager_Release_00422220(Manager_00422220* manager) {
    RemoveScheduledTaskPair(&manager->tasks);
    for (int i = 0; i < 25; ++i) {
        ManagerOwned_00422220* owned = manager->owned[i];
        if (owned) {
            ManagerOwned_Destroy_004294a0(owned);
            operator delete(owned);
        }
    }
    MarkAnimationForRemoval(data_00491c10, manager->animation_id);
    manager->animation_id = 0;
    g_pause = 0;
    return 0;
}
#pragma code_seg()
