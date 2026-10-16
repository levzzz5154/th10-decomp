// Complete 0x00422C30: clear pause, queue the resource request, then restore speed.
#include "th10/game/pause_choice/animation.hpp"
extern "C" char str_unpause[];
#pragma code_seg(".text$29unpause")
void PauseOwner::Unpause() {
    g_pause_flags->flags &= ~0x10u;
    g_music_requests.RegisterResource(str_unpause, 7, 0);
    AnimationManager_SetFlag2(g_sprt_ctrl, animation);
    animation.value = 0;
    g_game_speed = saved_speed;
}
#pragma code_seg()
