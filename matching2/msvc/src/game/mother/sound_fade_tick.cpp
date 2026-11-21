#include "th10/platform/sound_fade_manager.hpp"
#pragma code_seg(".text$00e_fade")
void SoundFadeManager::TickFades() {
    if (stream) {
        stream->FadeOutAndStop();
        stream->FadeDownHalf();
        stream->FadeUpSlight();
        stream->FadeDownSlight();
    }
}
#pragma code_seg()
