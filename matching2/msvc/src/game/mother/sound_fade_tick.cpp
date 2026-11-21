#include "th10/platform/sound_fade_manager_wave18.hpp"
#pragma code_seg(".text$00e_fade")
void SoundFadeManagerWave18::TickFades() {
    if (stream) {
        stream->FadeOutAndStop();
        stream->FadeDownHalf();
        stream->FadeUpSlight();
        stream->FadeDownSlight();
    }
}
#pragma code_seg()
