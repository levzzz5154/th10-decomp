#include "th10/game/title_options_menu.hpp"

namespace {

int ClampStep(int value, int delta) {
    value += delta;
    if (value < 0)
        return 0;
    if (value > 100)
        return 100;
    return value;
}

} // namespace

// Semantic reconstruction of retail Options handler 0x0042D920. The six
// entries are BGM mode, music volume, SFX volume, key configuration,
// defaults, and return. Retail phases 0/1/2/4 are init, entry, input, exit.
void TitleOptions_Initialize(TitleOptionsState* state) {
    state->phase = 0;
    state->selection = 0;
    state->previous_selection = 0;
    state->phase_frame = 0;
    state->pending_action = TITLE_OPTIONS_ACTION_NONE;
}

TitleOptionsAction TitleOptions_Update(TitleOptionsState* state,
                                       TitleOptionsConfig* config,
                                       uint32_t input_flags) {
    if (state->phase == 0) {
        state->selection = 0;
        state->previous_selection = 0;
        state->phase_frame = 0;
        state->phase = 1;
        return TITLE_OPTIONS_ACTION_NONE;
    }
    if (state->phase == 1) {
        if (++state->phase_frame > 6) {
            state->phase = 2;
            state->phase_frame = 0;
        }
        return TITLE_OPTIONS_ACTION_NONE;
    }
    if (state->phase == 2) {
        state->previous_selection = state->selection;
        if ((input_flags & TITLE_OPTIONS_UP) != 0)
            state->selection = (state->selection + 5) % 6;
        if ((input_flags & TITLE_OPTIONS_DOWN) != 0)
            state->selection = (state->selection + 1) % 6;

        TitleOptionsAction action = TITLE_OPTIONS_ACTION_NONE;
        if ((input_flags & TITLE_OPTIONS_LEFT) != 0) {
            if (state->selection == 0)
                config->bgm_mode =
                    (config->bgm_mode + 2) % 3;
            else if (state->selection == 1)
                config->music_volume =
                    ClampStep(config->music_volume, -5);
            else if (state->selection == 2)
                config->sound_volume =
                    ClampStep(config->sound_volume, -5);
            if (state->selection <= 2)
                action = TITLE_OPTIONS_ACTION_VALUE_CHANGED;
        }
        if ((input_flags & TITLE_OPTIONS_RIGHT) != 0) {
            if (state->selection == 0)
                config->bgm_mode = (config->bgm_mode + 1) % 3;
            else if (state->selection == 1)
                config->music_volume =
                    ClampStep(config->music_volume, 5);
            else if (state->selection == 2)
                config->sound_volume =
                    ClampStep(config->sound_volume, 5);
            if (state->selection <= 2)
                action = TITLE_OPTIONS_ACTION_VALUE_CHANGED;
        }

        if ((input_flags & TITLE_OPTIONS_CANCEL) != 0) {
            state->selection = 5;
            state->pending_action = TITLE_OPTIONS_ACTION_RETURN;
            state->phase = 4;
            state->phase_frame = 0;
        } else if ((input_flags & TITLE_OPTIONS_CONFIRM) != 0) {
            if (state->selection == 3) {
                state->pending_action = TITLE_OPTIONS_ACTION_KEY_CONFIG;
                state->phase = 4;
                state->phase_frame = 0;
            } else if (state->selection == 4) {
                config->bgm_mode = 0;
                config->music_volume = 100;
                config->sound_volume = 80;
                action = TITLE_OPTIONS_ACTION_DEFAULTS;
            } else if (state->selection == 5) {
                state->pending_action = TITLE_OPTIONS_ACTION_RETURN;
                state->phase = 4;
                state->phase_frame = 0;
            }
        }
        return action;
    }
    if (state->phase == 4 && ++state->phase_frame >= 10) {
        TitleOptionsAction action = state->pending_action;
        state->pending_action = TITLE_OPTIONS_ACTION_NONE;
        return action;
    }
    return TITLE_OPTIONS_ACTION_NONE;
}
