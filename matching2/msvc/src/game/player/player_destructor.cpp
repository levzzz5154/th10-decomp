// 0x00424ED0: destroy the player. Unregister its scheduler tasks, retire its
// animation file (or, between stages, hand the loaded shot-type file to the
// next stage's player) and release its sprite. Native LTCG supplies this on stack, RET 4.
#include "th10/game/game_thread.hpp"
#include "th10/game/manager_teardown_helpers.hpp"
#include "th10/game/player.hpp"

extern "C" {
extern unsigned int g_globals_flags;
extern void* data_00491bf0;
extern AnimationBanks_00402440* g_sprt_ctrl;
}
#pragma code_seg(".text$01dtor")
Player::~Player() {
    RemoveSchedulerTask(update_task);
    RemoveSchedulerTask(draw_task);
    g_player = 0;
    if (g_globals_flags & 1) {
        reinterpret_cast<SprtCtrl*>(g_sprt_ctrl)->MarkResourceForRemoval(animation_file);
        data_00491bf0 = shot_type;
    } else {
        ReleaseAnimationBank(g_sprt_ctrl, 8);
        if (shot_type) {
            entry_free_00452422(shot_type);
            shot_type = 0;
        }
        data_00491bf0 = 0;
    }
}
#pragma code_seg()
