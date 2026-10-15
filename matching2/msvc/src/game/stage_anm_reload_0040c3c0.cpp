// The stage's animation file reload, run on a worker thread.
#include "th10/game/stage_anm_reload.hpp"

// 0x0040B4F0: reload the owner's stage. Retail keeps this copy without a
// remaining caller; the owner arrives in EAX.
#pragma code_seg(".text$01owner")
int StageOwner_0040c3c0::ReloadStageAnm() {
    return stage->ReloadAnm();
}
#pragma code_seg()

// 0x0040C3A0: the worker thread's entry.
#pragma code_seg(".text$03thread")
extern "C" unsigned int __cdecl Stage_ReloadAnmThread_0040c3a0() {
    data_00477700->stage->ReloadAnm();
    return 0;
}
#pragma code_seg()

// 0x0040C3C0: load the stage's animation file into its slot, clear the reload
// request and take down the loading sprite. The stage arrives in EBX.
#pragma code_seg(".text$05reload")
int Stage_0040c3c0::ReloadAnm() {
    const char* name = anm_name;
    data_00497c38[0] = 0;
    strcat(data_00497c38, name);
    anm[header->anm_slot] =
        Recovery_LoadCachedResource(header->anm_slot + 0x1D, data_00491c10, data_00497c38);
    flags &= ~4u;
    g_ascii_manager->StopLoadingSprite();
    return 0;
}
#pragma code_seg()
