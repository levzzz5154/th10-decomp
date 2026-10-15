// 0x00427AE0: switch between live and playback coordinates, updating the
// animation only on a mode transition. Volatile coordinate words preserve
// the observed sequence of reads and writes, including across animation calls.
#include "th10/game/playback_state.hpp"
#include "th10/game/player.hpp"

#pragma code_seg(".text$45timedzbd")
void PlaybackState::SwitchPlaybackState() {
    int selected = g_player->focused;
    if (selected == 0) {
        if (playback != 0) animation.SetStopFrame(6);
        saved_x = live_x;
        saved_y = live_y;
    } else {
        if (playback == 0) animation.SetStopFrame(3);
        current_x = saved_x;
        current_y = saved_y;
    }
    playback = selected;
}
#pragma code_seg()
