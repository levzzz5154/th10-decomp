// 0x00424ED0: destroy the player. Unregister its scheduler tasks, retire its
// animation file (or, between stages, hand the loaded shot-type file to the
// next stage's player) and release its sprite. Native LTCG supplies this on stack, RET 4.
#include "th10/game/game_thread.hpp"
#include "th10/game/manager_teardown_helpers.hpp"
#include "th10/game/player.hpp"

extern "C" {
extern unsigned int g_globals_flags;
extern void* g_player_parameter_file;
extern AnimationBanks* g_sprt_ctrl;
}
#pragma code_seg(".text$01dtor")
Player::~Player() {
    RemoveSchedulerTask(update_task);
    RemoveSchedulerTask(draw_task);
    g_player = 0;
    if (g_globals_flags & 1) {
        reinterpret_cast<SprtCtrl*>(g_sprt_ctrl)->MarkResourceForRemoval(animation_file);
        g_player_parameter_file = shot_type;
    } else {
        ReleaseAnimationBank(g_sprt_ctrl, 8);
        if (shot_type) {
            crt_free(shot_type);
            shot_type = 0;
        }
        g_player_parameter_file = 0;
    }
}
#pragma code_seg()
