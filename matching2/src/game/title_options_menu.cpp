#include "th10/game/title_options_menu.hpp"

namespace {


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
        // Retail 0x0042D920's phase 2, exactly. The three adjustable rows are
        // 0 = the hint mode in byte_491D6A, 1 = BGM volume in byte_491D68 and
        // 2 = SE volume in byte_491D69; retail selects between the two volumes
        // with `v30 = selection - 1`, taking BGM when it is zero and SE when
        // it is one.
        if ((input_flags & TITLE_OPTIONS_LEFT) != 0) {
            if (state->selection == 0) {
                // Left clamps at zero. It does NOT wrap - only right does.
                //   if ( byte_491D6A ) { v31 = byte_491D6A - 1; ... }
                if (config->bgm_mode > 0)
                    config->bgm_mode -= 1;
            } else if (state->selection == 1) {
                //   if ( byte_491D68 >= 5 ) byte_491D68 -= 5; else = 0;
                config->music_volume =
                    config->music_volume >= 5 ? config->music_volume - 5 : 0;
            } else if (state->selection == 2) {
                config->sound_volume =
                    config->sound_volume >= 5 ? config->sound_volume - 5 : 0;
            }
            if (state->selection <= 2)
                action = TITLE_OPTIONS_ACTION_VALUE_CHANGED;
        }
        if ((input_flags & TITLE_OPTIONS_RIGHT) != 0) {
            if (state->selection == 0) {
                //   if ( byte_491D6A >= 2 ) byte_491D6A = 0; else ++;
                config->bgm_mode =
                    config->bgm_mode >= 2 ? 0 : config->bgm_mode + 1;
            } else if (state->selection == 1) {
                //   byte_491D68 += 5; if ( byte_491D68 > 100 ) = 100;
                config->music_volume += 5;
                if (config->music_volume > 100)
                    config->music_volume = 100;
            } else if (state->selection == 2) {
                config->sound_volume += 5;
                if (config->sound_volume > 100)
                    config->sound_volume = 100;
            }
            if (state->selection <= 2)
                action = TITLE_OPTIONS_ACTION_VALUE_CHANGED;
        }

        if ((input_flags & TITLE_OPTIONS_CANCEL) != 0) {
            // Retail 0x0042D920 does not leave on the first cancel. Unless the
            // cursor is already on the last entry it only carries it there and
            // returns; a second cancel is what commits. This is the same idiom
            // 0x0042D420 uses on the main menu:
            //   if (selection != 5) { sound 11; selection = clamp(count, 5);
            //                         ...; return 1; }
            if (state->selection != 5) {
                state->selection = 5;
                return TITLE_OPTIONS_ACTION_NONE;
            }
            state->pending_action = TITLE_OPTIONS_ACTION_RETURN;
            state->phase = 4;
            state->phase_frame = 0;
        } else if ((input_flags & TITLE_OPTIONS_CONFIRM) != 0) {
            if (state->selection == 3) {
                state->pending_action = TITLE_OPTIONS_ACTION_KEY_CONFIG;
                state->phase = 4;
                state->phase_frame = 0;
            } else if (state->selection == 4) {
                // byte_491D68 = 100; byte_491D69 = 80; byte_491D6A = 0;
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
