#include "th10/game/title_main_menu.hpp"

namespace {

// Retail's exit switch (0x0042D420 phase 4) routes selection 4 to title state
// 11, which is Player Data, and selection 5 to state 14, the music room. The
// on-screen order in retail is Game Start, Extra Start, Practice Start,
// Replay, Player Data, Music Room, Option, Quit.
TitleMenuAction ActionForSelection(int selection) {
    static const TitleMenuAction actions[8] = {
        TITLE_MENU_ACTION_START,
        TITLE_MENU_ACTION_EXTRA,
        TITLE_MENU_ACTION_PRACTICE,
        TITLE_MENU_ACTION_REPLAY,
        TITLE_MENU_ACTION_RESULTS,
        TITLE_MENU_ACTION_MUSIC_ROOM,
        TITLE_MENU_ACTION_OPTIONS,
        TITLE_MENU_ACTION_QUIT,
    };
    if (selection < 0 || selection > 7)
        return TITLE_MENU_ACTION_NONE;
    return actions[selection];
}

// Retail's `count ? (count > limit ? limit : count - 1) : limit` idiom, which
// appears three times in 0x0042D420 to land the cursor on a specific entry.
int ClampFromCount(int count, int limit) {
    if (count == 0)
        return limit;
    return count > limit ? limit : count - 1;
}

} // namespace

// 0x0044BEA0 - move the cursor by `delta`. a1[0] is the selection, a1[2] the
// item count, a1[52] the wrap flag and a1[53] the unavailable count, with the
// unavailable list at a1+36. A landing that hits an unavailable entry repeats
// the whole step, which is what carries the cursor past a locked entry in the
// direction it was already travelling.
void TitleMainMenu_MoveSelection(TitleMainMenuState* state, int delta) {
    const int count = state->item_count;
    if (count <= 0)
        return;
    // Retail bounds this loop only by the unavailable list shrinking the
    // reachable set; a full sweep is the most steps it can ever need.
    for (int guard = 0; guard <= count; ++guard) {
        state->selection += delta;
        while (state->selection >= count) {
            state->selection = state->wrap != 0 ? state->selection - count
                                                : count - 1;
        }
        while (state->selection < 0) {
            state->selection = state->wrap != 0 ? state->selection + count : 0;
        }
        bool blocked = false;
        for (int index = 0; index < state->unavailable_count && index < 16;
             ++index) {
            if (state->unavailable[index] == state->selection) {
                blocked = true;
                break;
            }
        }
        if (!blocked)
            return;
    }
}

void TitleMainMenu_Initialize(TitleMainMenuState* state) {
    state->phase = 0;
    state->selection = 0;
    state->previous_selection = 0;
    state->item_count = 8;
    state->phase_frame = 0;
    state->pending_action = TITLE_MENU_ACTION_NONE;
    state->wrap = 1;
    state->unavailable_count = 0;
    for (int index = 0; index < 16; ++index)
        state->unavailable[index] = 0;
}

// 0x0042D420 - the main-menu portion of the title state machine. Phases are
// a3[8]: 0 initializes, 1 waits out the entry animation, 2 takes input and 4
// waits out the exit animation before the choice takes effect.
TitleMenuAction TitleMainMenu_Update(TitleMainMenuState* state,
                                     uint32_t input_flags,
                                     const TitleMainMenuEnv* env) {
    void* context = env != nullptr ? env->context : nullptr;

    switch (state->phase) {
    case 0: {
        state->item_count = 8;
        // A locked Extra is not removed from the list, it is made
        // unselectable, and 0x0044BEA0 steps the cursor over it.
        if (env != nullptr && env->extra_unlocked != nullptr &&
            env->extra_unlocked(context) == 0 &&
            state->unavailable_count < 16) {
            state->unavailable[state->unavailable_count] = 1;
            state->unavailable_count += 1;
        }
        // Returning from practice puts the cursor back on Practice Start and
        // consumes the flag. Retail does not otherwise touch the selection
        // here, so re-entering the menu keeps the cursor where it was.
        if (env != nullptr && env->take_practice_flag != nullptr &&
            env->take_practice_flag(context) != 0) {
            state->selection = ClampFromCount(state->item_count, 2);
        }
        if (env != nullptr && env->broadcast != nullptr) {
            env->broadcast(context, 88, -1);  // start the menu scripts
            env->broadcast(context, 0, -1);
        }
        state->phase = 1;
        state->phase_frame = 0;
    }
        // Retail falls straight into the phase 1 body on the same frame.
        [[fallthrough]];

    case 1:
        if (state->phase_frame <= 10) {
            state->phase_frame += 1;
            return TITLE_MENU_ACTION_NONE;
        }
        state->phase = 2;
        state->phase_frame = 0;
        if (env != nullptr && env->broadcast != nullptr)
            env->broadcast(context, 0, state->selection + 17);
        return TITLE_MENU_ACTION_NONE;

    case 2: {
        state->previous_selection = state->selection;
        if ((input_flags & TITLE_MENU_UP) != 0)
            TitleMainMenu_MoveSelection(state, -1);
        if ((input_flags & TITLE_MENU_DOWN) != 0)
            TitleMainMenu_MoveSelection(state, 1);
        if (state->previous_selection != state->selection && env != nullptr) {
            if (env->play_sound != nullptr)
                env->play_sound(context, 12);
            if (env->broadcast != nullptr)
                env->broadcast(context, 0, state->selection + 7);
        }

        if ((input_flags & TITLE_MENU_CANCEL) != 0) {
            if (env != nullptr && env->play_sound != nullptr)
                env->play_sound(context, 11);
            if (state->selection == 7) {
                // Already on Quit: cancel commits it.
                state->phase = 4;
                state->phase_frame = 0;
                state->pending_action = TITLE_MENU_ACTION_QUIT;
                return TITLE_MENU_ACTION_NONE;
            }
            // Otherwise cancel only carries the cursor down to Quit. Retail
            // then falls through to the confirm test on the same frame.
            state->selection = ClampFromCount(state->item_count, 7);
            if (env != nullptr) {
                if (env->broadcast_and_run != nullptr)
                    env->broadcast_and_run(context, 0, 3);
                if (env->broadcast != nullptr)
                    env->broadcast(context, 0, state->selection + 7);
            }
        }

        if ((input_flags & TITLE_MENU_CONFIRM) != 0) {
            if (env != nullptr && env->broadcast != nullptr)
                env->broadcast(context, 0, 6);
            state->pending_action = ActionForSelection(state->selection);
            if (env != nullptr) {
                if (state->selection == 7) {
                    if (env->play_sound != nullptr)
                        env->play_sound(context, 11);
                } else {
                    if (env->play_sound != nullptr)
                        env->play_sound(context, 10);
                    if (state->selection <= 5) {
                        // Selections 0..5 leave the two menu overlays running
                        // through the transition; Option closes them instead.
                        if (env->broadcast != nullptr) {
                            env->broadcast(context, 90, 7);
                            env->broadcast(context, 91, 7);
                        }
                    } else if (env->broadcast_and_run != nullptr) {
                        env->broadcast_and_run(context, 90, 3);
                        env->broadcast_and_run(context, 91, 3);
                    }
                }
            }
            state->phase = 4;
            state->phase_frame = 0;
        }
        return TITLE_MENU_ACTION_NONE;
    }

    case 4:
        // Retail gates on a3[173] < 20, so the choice lands on the frame the
        // exit animation finishes.
        state->phase_frame += 1;
        if (state->phase_frame < 20)
            return TITLE_MENU_ACTION_NONE;
        {
            const TitleMenuAction action = state->pending_action;
            state->pending_action = TITLE_MENU_ACTION_NONE;
            return action;
        }

    default:
        return TITLE_MENU_ACTION_NONE;
    }
}
