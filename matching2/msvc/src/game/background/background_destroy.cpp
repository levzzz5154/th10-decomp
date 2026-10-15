// 0x00402440: BackGround destructor. Unregisters the three scheduler tasks,
// frees the stage buffers and the script bank loaded for this state.
#include "th10/game/background.hpp"
#include "th10/game/manager_teardown_helpers.hpp"

extern "C" {
extern unsigned char g_globals_flags;
void __cdecl crt_free(void* memory);
}

#pragma code_seg(".text$02dtor")
BackGround::~BackGround() {
    RemoveSchedulerTask(primary);
    RemoveSchedulerTask(secondary);
    RemoveSchedulerTask(after_draw);
    if (file) {
        crt_free(file);
        file = 0;
    }
    if (original) {
        crt_free(original);
        original = 0;
    }
    original = 0;
    if (instances) {
        crt_free(instances);
        instances = 0;
    }
    // Each of the two states owns the script bank loaded for it.
    if (!(g_globals_flags & 1))
        ReleaseAnimationBank(reinterpret_cast<AnimationBanks_00402440*>(g_sprt_ctrl),
                             (stage_flags & 1) + 4);
    if (g_background == this)
        g_background = 0;
    if (g_background_prev == this)
        g_background_prev = 0;
}
#pragma code_seg()
