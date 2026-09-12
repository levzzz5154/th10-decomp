#include "th10/platform/sound_fade.hpp"

namespace {

// Shared decrement helper: returns true when the fade finished this
// frame; otherwise the volume step callback runs.
bool StepFade(SoundFadeState* fade, void (*step_volume)()) {
    fade->counter -= 1;
    if (fade->counter < 1) {
        fade->mode = 0;
        return true;
    }
    if (step_volume != 0) {
        step_volume();
    }
    return false;
}

}  // namespace

// 0x00421E00 - Tick the active sound fade. Retail re-reads the fade
// pointer from the manager between the mode checks, but the sequence is
// equivalent to testing modes 1, 2, 4, and 3 in order on the same
// object; a mode that just reset to 0 fails the remaining checks.
void SoundFade_Tick(SoundFadeState* fade, void (*stop_buffer)(),
                    void (*step_volume)()) {
    if (fade == 0) {
        return;
    }
    if (fade->mode == 1) {
        if (StepFade(fade, step_volume) && stop_buffer != 0) {
            stop_buffer();
        }
    }
    if (fade->mode == 2) {
        StepFade(fade, step_volume);
    }
    if (fade->mode == 4) {
        StepFade(fade, step_volume);
    }
    if (fade->mode == 3) {
        StepFade(fade, step_volume);
    }
}
