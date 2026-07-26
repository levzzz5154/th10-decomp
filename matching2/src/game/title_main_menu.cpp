#include "th10/game/title_main_menu.hpp"

namespace {

TitleMenuAction ActionForSelection(int selection) {
    static const TitleMenuAction actions[8] = {
        TITLE_MENU_ACTION_START,
        TITLE_MENU_ACTION_EXTRA,
        TITLE_MENU_ACTION_PRACTICE,
        TITLE_MENU_ACTION_REPLAY,
        // Retail's fifth entry is Player Data and its sixth is Music Room -
        // 0x0042D420 sends selection 4 to title state 11 and selection 5 to
        // state 14. These two were the wrong way round, so choosing Player
        // Data ran Music Room and vice versa.
        TITLE_MENU_ACTION_RESULTS,
        TITLE_MENU_ACTION_MUSIC_ROOM,
        TITLE_MENU_ACTION_OPTIONS,
        TITLE_MENU_ACTION_QUIT,
    };
    return actions[selection];
}

} // namespace

// Semantic reconstruction of the main-menu portion of retail 0x0042D420.
// Retail phases 0/1/2/4 are initialization, entry wait, input, and exit wait.
void TitleMainMenu_Initialize(TitleMainMenuState* state) {
    state->phase = 0;
    state->selection = 0;
    state->previous_selection = 0;
    state->item_count = 8;
    state->phase_frame = 0;
    state->pending_action = TITLE_MENU_ACTION_NONE;
}

TitleMenuAction TitleMainMenu_Update(TitleMainMenuState* state,
                                     uint32_t input_flags) {
    if (state->phase == 0) {
        state->selection = 0;
        state->previous_selection = 0;
        state->item_count = 8;
        state->phase_frame = 0;
        state->phase = 1;
        return TITLE_MENU_ACTION_NONE;
    }
    if (state->phase == 1) {
        if (++state->phase_frame > 10) {
            state->phase = 2;
            state->phase_frame = 0;
        }
        return TITLE_MENU_ACTION_NONE;
    }
    if (state->phase == 2) {
        state->previous_selection = state->selection;
        if ((input_flags & TITLE_MENU_UP) != 0)
            state->selection =
                (state->selection + state->item_count - 1) % state->item_count;
        if ((input_flags & TITLE_MENU_DOWN) != 0)
            state->selection = (state->selection + 1) % state->item_count;

        if ((input_flags & TITLE_MENU_CANCEL) != 0) {
            state->selection = state->item_count - 1;
            state->pending_action = TITLE_MENU_ACTION_QUIT;
            state->phase = 4;
            state->phase_frame = 0;
        } else if ((input_flags & TITLE_MENU_CONFIRM) != 0) {
            state->pending_action = ActionForSelection(state->selection);
            state->phase = 4;
            state->phase_frame = 0;
        }
        return TITLE_MENU_ACTION_NONE;
    }
    if (state->phase == 4 && ++state->phase_frame >= 20) {
        TitleMenuAction action = state->pending_action;
        state->pending_action = TITLE_MENU_ACTION_NONE;
        return action;
    }
    return TITLE_MENU_ACTION_NONE;
}
