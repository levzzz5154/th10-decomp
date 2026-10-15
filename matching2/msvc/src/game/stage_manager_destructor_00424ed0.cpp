// 0x00424ED0: destroy the stage manager. Unregister its scheduler tasks,
// retire its animation bank or pass its stage data to the next stage, and
// release its embedded sprite. Native LTCG supplies this on stack, RET 4.
#include "th10/game/game_thread.hpp"
#include "th10/game/manager_teardown_helpers.hpp"

// Same common 0x3AC-byte sprite ownership as the game-thread slots.
typedef GameThreadSlot StageSprite_00424ed0;

struct StageManager_00424ed0 {
    unsigned int flags;
    unsigned int reserved_004;
    SchedulerTask* update_task;
    SchedulerTask* draw_task;
    void* animation_resource;
    StageSprite_00424ed0 sprite;
    unsigned char reserved_3c0[0x45C - 0x3C0];
    void* stage_data;
    __declspec(noinline) ~StageManager_00424ed0();
};
typedef char StageSpriteOffset_00424ed0[offsetof(StageManager_00424ed0, sprite) == 0x14 ? 1 : -1];
typedef char StageDataOffset_00424ed0[offsetof(StageManager_00424ed0, stage_data) == 0x45C ? 1 : -1];

extern "C" {
extern unsigned int data_00474ca0;
extern StageManager_00424ed0* g_player;
extern void* data_00491bf0;
extern AnimationBanks_00402440* data_00491c10;
}
#pragma code_seg(".text$01dtor")
StageManager_00424ed0::~StageManager_00424ed0() {
    RemoveSchedulerTask(update_task);
    RemoveSchedulerTask(draw_task);
    g_player = 0;
    if (data_00474ca0 & 1) {
        reinterpret_cast<AnimationManager*>(data_00491c10)->MarkResourceForRemoval(animation_resource);
        data_00491bf0 = stage_data;
    } else {
        ReleaseAnimationBank(data_00491c10, 8);
        if (stage_data) {
            entry_free_00452422(stage_data);
            stage_data = 0;
        }
        data_00491bf0 = 0;
    }
}
#pragma code_seg()
