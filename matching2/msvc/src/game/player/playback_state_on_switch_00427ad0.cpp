// 0x00427AD0 (12 bytes): scheduler callback that re-evaluates the playback
// coordinate mode of its state and lets the chain continue.
#include "th10/game/playback_state.hpp"

#pragma code_seg(".text$45timedzbc5")
int __fastcall PlaybackState_OnSwitch(PlaybackState* state) {
    state->SwitchPlaybackState();
    return 0;
}
#pragma code_seg()
