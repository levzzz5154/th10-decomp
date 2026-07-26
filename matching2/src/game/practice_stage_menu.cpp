#include "th10/game/practice_stage_menu.hpp"

namespace {

int ClampRememberedSelection(int remembered, int count) {
    if (count == 0) return remembered;
    if (remembered >= count) return count - 1;
    return remembered < 0 ? 0 : remembered;
}

int FirstPressedShortcut(const int8_t* keys) {
    if (keys == 0) return 0;
    for (int index = 0; index < 9; ++index)
        if (keys[index] < 0) return index + 1;
    return 0;
}

}  // namespace

// 0x00430FF0 - practice-stage selection state machine.  IDA's userpurge
// prototype invents EAX/EDX inputs, but the PE32 body reads only the stack menu
// pointer; EBP is loaded from [esp+4].  The caller's ECX is preserved solely
// for the two register-bound close-view calls in phase 4.
int PracticeStageMenu_Update(PracticeStageMenuState* state,
                             PracticeStageMenuEnv* env,
                             const PracticeStageMenuOps* ops) {
    switch (state->phase) {
    case 0:
        state->selection_count = 6;
        state->selection = ClampRememberedSelection(
            env->remembered_selection, state->selection_count);
        ops->open_view(ops->context, 106);
        ops->open_view(ops->context, 107 + env->character);
        ops->set_phase(ops->context, 1);
        [[fallthrough]];
    case 1:
        if (state->phase_timer > 10) ops->set_phase(ops->context, 2);
        break;

    case 2: {
        state->previous_selection = state->selection;
        if ((env->held & 0x10u) != 0 || (env->pressed & 0x10u) != 0)
            ops->move_selection(ops->context, state, -1);
        if ((env->held & 0x20u) != 0 || (env->pressed & 0x20u) != 0)
            ops->move_selection(ops->context, state, 1);
        if (state->selection != state->previous_selection)
            ops->play_sound(ops->context, 12);

        if ((env->pressed & 0xau) != 0) {
            ops->set_phase(ops->context, 4);
            ops->play_sound(ops->context, 11);
            env->remembered_selection = state->selection;
            return 1;
        }
        if ((env->pressed & 0x1001u) != 0) {
            if (env->stage_unlocks != 0 &&
                env->stage_unlocks[state->selection] != 0) {
                ops->set_phase(ops->context, 3);
                ops->play_sound(ops->context, 10);
            } else {
                ops->play_sound(ops->context, 37);
            }
            env->remembered_selection = state->selection;
            env->shortcut_stage = FirstPressedShortcut(
                env->direct_poll_succeeded ? env->direct_keys
                                           : env->fallback_keys);
        }
        break;
    }

    case 3:
        if (state->phase_timer == 10) {
            ops->start_fade(ops->context, 480.0f, 384.0f);
            ops->play_sound(ops->context, 43);
        }
        if (state->phase_timer >= 40) {
            ops->reset_view(ops->context);
            ops->close_view(ops->context, 106);
            ops->set_phase(ops->context, 3);
            env->selected_stage = state->selection + 1;
            env->game_mode = env->selected_stage;
            ops->launch_stage(ops->context, 6.0f);
            env->launch_state = 7;
        }
        break;

    case 4:
        if (state->phase_timer >= 6) {
            ops->close_view(ops->context, 106);
            ops->close_view(ops->context, 107 + env->character);
            ops->set_phase(ops->context, 8);
            ops->reset_view(ops->context);
        }
        break;
    default:
        break;
    }
    return 1;
}
