// 0x0044D740..0x0044D847: per-frame steps of the four sound-buffer fades.
// Each counts its fade down one frame and sets the buffer volume along a
// straight line; the frame the count reaches zero ends the fade (the fade-out
// also stops the buffer) and returns 1.  Compiled in the 0x0044D4E0 native-LTCG
// cluster so SetOperationDeadline keeps its private entry (owner in EAX).
#include "th10/platform/sound_fade.hpp"

#pragma code_seg(".text$02layoutb")
int PlatformInterfaceState2::FadeOutAndStop() {
    if (fade_mode_01c == 1) {
        if (--fade_remaining_014 <= 0) {
            fade_mode_01c = 0;
            entries_004[0]->stop();
            return 1;
        }
        SetOperationDeadline(fade_remaining_014 * 5000 / fade_length_018 - 5000);
    }
    return 0;
}

#pragma code_seg(".text$02layoutc")
int PlatformInterfaceState2::FadeDownHalf() {
    if (fade_mode_01c == 2) {
        if (--fade_remaining_014 <= 0) {
            fade_mode_01c = 0;
            return 1;
        }
        SetOperationDeadline(fade_remaining_014 * -5000 / fade_length_018);
    }
    return 0;
}

#pragma code_seg(".text$02layoutd")
int PlatformInterfaceState2::FadeDownSlight() {
    if (fade_mode_01c == 3) {
        if (--fade_remaining_014 <= 0) {
            fade_mode_01c = 0;
            return 1;
        }
        SetOperationDeadline(fade_remaining_014 * -1000 / fade_length_018);
    }
    return 0;
}

#pragma code_seg(".text$02layoute")
int PlatformInterfaceState2::FadeUpSlight() {
    if (fade_mode_01c == 4) {
        if (--fade_remaining_014 <= 0) {
            fade_mode_01c = 0;
            return 1;
        }
        SetOperationDeadline(fade_remaining_014 * 1000 / fade_length_018 - 1000);
    }
    return 0;
}
#pragma code_seg()
