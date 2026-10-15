// 0x00402440: BackGround destructor. Unregisters the three scheduler tasks,
// frees the stage buffers and the script bank loaded for this state.
#include "th10/game/background.hpp"
#include "th10/game/manager_teardown_helpers.hpp"

extern "C" {
extern unsigned char data_00474ca0;
void __cdecl entry_free_00452422(void* memory);
}

#pragma code_seg(".text$02dtor")
BackGround::~BackGround() {
    RemoveSchedulerTask(primary);
    RemoveSchedulerTask(secondary);
    RemoveSchedulerTask(after_draw);
    if (file) {
        entry_free_00452422(file);
        file = 0;
    }
    if (original) {
        entry_free_00452422(original);
        original = 0;
    }
    original = 0;
    if (instances) {
        entry_free_00452422(instances);
        instances = 0;
    }
    // Each of the two states owns the script bank loaded for it.
    if (!(data_00474ca0 & 1))
        ReleaseAnimationBank(reinterpret_cast<AnimationBanks_00402440*>(data_00491c10),
                             (stage_flags & 1) + 4);
    if (g_background == this)
        g_background = 0;
    if (data_004776e4 == this)
        data_004776e4 = 0;
}
#pragma code_seg()
