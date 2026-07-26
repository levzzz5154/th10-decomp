#include "th10/game/gameplay_render_pass.hpp"

namespace {

void Flush(const GameplayRenderHooks* hooks) {
    hooks->flush_state(hooks->context);
}

}  // namespace

// 0x00402850 - Gameplay render pass and transition overlay. The sole owner
// argument is pushed by the 0x00403060 ECX trampoline and loaded into EBP by
// the retail prologue; all state accesses in the body are relative to it.
int GameplayRenderPass_Run(GameplayRenderState* state,
                           GameplayRenderGlobals* globals,
                           const GameplayRenderHooks* hooks) {
    if ((state->flags & 8u) != 0) return 1;

    if ((state->flags & 4u) == 0 || state->transition_timer < 60) {
        Flush(hooks);
        state->render_seed_a = globals->seed_a;
        state->render_seed_b = globals->seed_b;
        hooks->apply_snapshot(hooks->context, state->render_snapshot);

        Flush(hooks);
        hooks->set_render_state(hooks->context, 14, 1);
        Flush(hooks);
        hooks->set_render_state(hooks->context, 23, 4);
        Flush(hooks);
        hooks->set_render_state(hooks->context, 34,
                                state->render_state_22);
        Flush(hooks);
        hooks->set_render_state(hooks->context, 36,
                                state->render_state_24);
        Flush(hooks);
        hooks->set_render_state(hooks->context, 37,
                                state->render_state_25);
        hooks->clear_target(hooks->context, 0);

        const GameplayRenderRect rect = {32, 16, 416, 464};
        uint32_t color = state->render_state_22 & 0x00ffffffu;
        if ((state->flags & 4u) != 0 && state->transition_frame < 34)
            color = 0;
        hooks->draw_rect(hooks->context, &rect, color);
    }

    if ((state->flags & 4u) != 0) {
        if (state->transition_timer < 30) {
            hooks->create_transition_text(hooks->context);
            state->flags |= 1u;
            hooks->start_transition(hooks->context, 1);
        } else {
            state->tint_active = 0;
            state->flags &= ~1u;
        }
    }

    if (state->tint_active != 0) {
        globals->tint_enabled = 1;
        globals->tint_color = state->tint_color;
    }

    state->transient[0] = 0;
    state->transient[1] = 0;
    state->transient[2] = 0;

    if ((state->flags & 1u) != 0) {
        if (state->render_resources != 0) {
            hooks->stop_runtime(hooks->context);
            hooks->reset_audio(hooks->context);
            Flush(hooks);
            Flush(hooks);
            hooks->set_render_state(hooks->context, 14, 0);
            for (int index = 0; index < 8; ++index) {
                if (state->layer_active[index] != 0)
                    hooks->draw_resource(hooks->context, index);
            }
            Flush(hooks);
            hooks->set_render_state(hooks->context, 14, 1);
            hooks->apply_snapshot(hooks->context, state->render_snapshot);
        }
        if (globals->mode_28_initialized != 1) {
            Flush(hooks);
            globals->mode_28_initialized = 1;
            hooks->set_render_state(hooks->context, 28, 1);
        }
        for (int index = 0; index < 8; ++index)
            hooks->draw_layer(hooks->context, index);
        Flush(hooks);
        if (state->activity_counter != 0) ++state->activity_counter;
    }

    globals->tint_enabled = 0;
    globals->tint_color = 0x80808080u;
    if (state->secondary_tint != 0) {
        globals->tint_enabled = 1;
        globals->tint_color = 0xff404040u;
    }
    Flush(hooks);
    hooks->set_render_state(hooks->context, 14, 0);
    Flush(hooks);
    hooks->set_render_state(hooks->context, 23, 8);
    return 1;
}
