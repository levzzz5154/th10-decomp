#include "th10/game/menu_flow_updates.hpp"

#include <cstring>

namespace {

bool Back(const MenuFlowInput& input) {
    return (input.pressed & 0xau) != 0;
}

bool Confirm(const MenuFlowInput& input) {
    return (input.pressed & 0x1001u) != 0;
}

void ChangeSelection(MenuFlowState* state, const MenuFlowInput& input,
                     uint32_t previous_mask, uint32_t next_mask,
                     const MenuFlowHooks* hooks) {
    state->previous_selection = state->selection;
    if ((input.held & previous_mask) != 0 ||
        (input.pressed & previous_mask) != 0)
        hooks->move_selection(hooks->context, state, -1);
    if ((input.held & next_mask) != 0 ||
        (input.pressed & next_mask) != 0)
        hooks->move_selection(hooks->context, state, 1);
}

}  // namespace

// 0x0042F540 - Options menu update state machine.
int ConfigMenuFlow_Update(MenuFlowState* state, const ConfigMenuEnv* env,
                          const MenuFlowHooks* hooks) {
    switch (state->phase) {
    case 0:
        state->transition_kind = 7;
        state->selection = 0;
        hooks->reset_view(hooks->context);
        hooks->set_phase(hooks->context, 1);
        std::memcpy(state->saved_config, env->config,
                    sizeof(state->saved_config));
        hooks->refresh_selection(hooks->context, 0);
        [[fallthrough]];
    case 1:
        if (state->phase_timer > 6) {
            hooks->set_phase(hooks->context, 2);
            hooks->activate_view(hooks->context, 2);
        }
        break;
    case 2: {
        ChangeSelection(state, env->input, 0x10, 0x20, hooks);
        if (state->previous_selection != state->selection) {
            hooks->play_change(hooks->context);
            hooks->refresh_selection(hooks->context, 2);
            hooks->activate_view(hooks->context, 2);
        }
        for (int index = 0; index < 31; ++index) {
            if (env->availability[index] < 0 && state->selection < 5) {
                state->queued_values[state->queued_count++] = index;
                break;
            }
        }
        if (Back(env->input) && state->selection == 6) {
            std::memcpy(state->saved_config, env->config,
                        sizeof(state->saved_config));
            hooks->refresh_selection(hooks->context, 0);
            hooks->close_view(hooks->context, 2);
            hooks->set_phase(hooks->context, 4);
            return 1;
        }
        if (Confirm(env->input)) {
            if (state->selection == 5) {
                std::memcpy(state->saved_config, env->config,
                            sizeof(state->saved_config));
                hooks->refresh_selection(hooks->context, 0);
                hooks->play_change(hooks->context);
                return 1;
            }
            if (state->selection == 6) {
                hooks->commit_config(hooks->context, state->saved_config);
                hooks->play_change(hooks->context);
                hooks->close_view(hooks->context, 2);
                hooks->set_phase(hooks->context, 4);
                return 1;
            }
        }
        break;
    }
    case 4:
        if (state->phase_timer > 9) {
            hooks->close_view(hooks->context, 4);
            hooks->launch(hooks->context, 0, state->selection);
        }
        break;
    default:
        break;
    }
    return 1;
}

// 0x00430320 - Stage/difficulty menu update.
int StageMenuFlow_Update(MenuFlowState* state, StageMenuEnv* env,
                         const MenuFlowHooks* hooks) {
    const int view = env->stage > 3 ? 0x78 : 0x77;
    switch (state->phase) {
    case 0:
        state->transition_kind = env->stage > 3 ? 1 : 4;
        hooks->reset_view(hooks->context);
        hooks->refresh_selection(hooks->context, view);
        hooks->activate_view(hooks->context, view);
        hooks->set_phase(hooks->context, 1);
        [[fallthrough]];
    case 1:
        if (state->phase_timer > 6) hooks->set_phase(hooks->context, 2);
        break;
    case 2:
        if (env->stage < 4)
            ChangeSelection(state, env->input, 0x10, 0x20, hooks);
        if (Back(env->input)) {
            hooks->set_phase(hooks->context, 4);
            hooks->play_change(hooks->context);
            hooks->reset_view(hooks->context);
            return 1;
        }
        if (Confirm(env->input)) {
            hooks->activate_view(hooks->context, view);
            hooks->close_view(hooks->context, view);
            hooks->set_phase(hooks->context, 3);
            hooks->play_change(hooks->context);
            return 1;
        }
        break;
    case 3:
        if (state->phase_timer > 13) {
            hooks->reset_view(hooks->context);
            hooks->close_view(hooks->context, 7);
            if (env->stage < 4) env->stage = state->selection;
            hooks->launch(hooks->context, 2, env->stage);
        }
        break;
    case 4:
        if (state->phase_timer > 5) {
            hooks->reset_view(hooks->context);
            hooks->close_view(hooks->context, 0x5a);
            hooks->close_view(hooks->context, 0x5b);
            hooks->set_phase(hooks->context, 2);
            env->stage = env->stage < 4 ? state->selection
                                        : env->fallback_stage;
            hooks->launch(hooks->context, 0, env->stage);
        }
        break;
    }
    return 1;
}

// 0x004306A0 - Character/shot selection update.
int ShotMenuFlow_Update(MenuFlowState* state, ShotMenuEnv* env,
                        const MenuFlowHooks* hooks) {
    switch (state->phase) {
    case 0:
        state->transition_kind = 2;
        if (env->mode == 4) {
            for (int group = 0; group < 2; ++group) {
                const int base = group * 3;
                if (env->availability[base] == 0 &&
                    env->availability[base + 1] == 0 &&
                    env->availability[base + 2] == 0) {
                    if (state->selection == group)
                        state->selection = 1 - group;
                    state->queued_values[state->queued_count++] = group;
                }
            }
        }
        hooks->reset_view(hooks->context);
        hooks->refresh_selection(hooks->context, 0x7d);
        hooks->activate_view(hooks->context, 0x7d);
        hooks->set_phase(hooks->context, 1);
        [[fallthrough]];
    case 1:
        if (state->phase_timer > 6) hooks->set_phase(hooks->context, 2);
        break;
    case 2:
        ChangeSelection(state, env->input, 0x40, 0x80, hooks);
        if (state->selection != state->previous_selection) {
            hooks->play_change(hooks->context);
            hooks->refresh_selection(hooks->context, 0x7d);
            hooks->activate_view(hooks->context, 0x7d);
        }
        if (Back(env->input)) {
            hooks->set_phase(hooks->context, 4);
            hooks->play_change(hooks->context);
            return 1;
        }
        if (Confirm(env->input)) {
            hooks->close_view(hooks->context, 0x7d);
            hooks->set_phase(hooks->context, 3);
            hooks->play_change(hooks->context);
            return 1;
        }
        break;
    case 3:
        if (state->phase_timer > 13) {
            hooks->reset_view(hooks->context);
            hooks->close_view(hooks->context, 8);
            env->shot = state->selection;
            hooks->launch(hooks->context, 3, env->shot);
        }
        break;
    case 4:
        if (state->phase_timer > 5) {
            hooks->reset_view(hooks->context);
            hooks->close_view(hooks->context, 6);
            env->shot = state->selection;
            hooks->launch(hooks->context, 0, env->shot);
        }
        break;
    }
    return 1;
}
