// Complete 0x00422C30: clear pause, queue the resource request, then restore speed.
#include "th10/game/pause_choice_00422c80/animation.hpp"
extern "C" char data_0046e0b8[];
#pragma code_seg(".text$29unpause")
void PauseOwner_00422c30::Unpause() {
    g_pause_flags->flags &= ~0x10u;
    g_music_requests.RegisterResource(data_0046e0b8, 7, 0);
    AnimationManager_SetFlag_004492a0(g_sprt_ctrl, animation);
    animation.value = 0;
    g_game_speed = saved_speed;
}
#pragma code_seg()
