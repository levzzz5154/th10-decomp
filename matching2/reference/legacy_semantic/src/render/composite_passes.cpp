#include "th10/render/composite_passes.hpp"

namespace {

const unsigned int kDrawOverlay = 1;
const unsigned int kRetireAfterFade = 2;
const unsigned int kFadeActive = 4;
const unsigned int kFinished = 8;

void SetAlphaBlendState(int enabled, const CompositeEnv* env) {
    if (env->global->alpha_blend_state != enabled) {
        env->flush();
        env->global->alpha_blend_state = enabled;
        env->set_render_state(28, enabled);
    }
}

}  // namespace

// 0x00402CA0 - Draw the staged composite passes, update overlay globals, and
// advance the fade state. The repeated flushes and state writes preserve the
// retail ordering rather than folding apparently redundant operations.
int CompositeEffect_Draw(CompositeState* state,
                         const CompositeEnv* env) {
    if (state->flags & kFinished) {
        return 1;
    }

    if (!(state->flags & kFadeActive) || state->counter < 60) {
        env->flush();
        env->publish_snapshot(state->snapshot);
        env->setup_snapshot();
        SetAlphaBlendState(1, env);

        env->flush();
        env->set_render_state(14, 0);
        env->flush();
        env->set_render_state(23, 8);
        env->draw_staged();

        env->flush();
        env->set_render_state(23, 4);
        SetAlphaBlendState(0, env);
        env->draw_staged();

        env->flush();
        env->set_render_state(23, 4);
        env->flush();
        env->set_render_state(34, state->state_34);
        env->flush();
        env->set_render_state(36, state->state_36);
        env->flush();
        env->set_render_state(37, state->state_37);
    }

    if ((state->flags & kFadeActive) && state->counter > 29) {
        state->visibility = 0;
    }

    if (state->flags & kDrawOverlay) {
        env->flush();
        env->set_render_state(14, 0);
        SetAlphaBlendState(1, env);
        for (int index = 0; index < 4; ++index) {
            env->draw_quad(state);
        }
        env->flush();
    }

    env->global->overlay_enabled = state->overlay_enabled ? 1 : 0;
    env->global->overlay_color =
        state->overlay_enabled ? 0xff404040u : 0x80808080u;

    env->flush();
    env->set_render_state(14, 0);
    env->flush();
    env->set_render_state(23, 8);

    if (state->counter > 0) {
        env->tick_fade(state, -1.0f);
        if (state->counter < 1) {
            state->visibility = 0xff;
            if (state->flags & kRetireAfterFade) {
                state->flags |= kFinished;
            }
            state->end_color = 0xffffff;
            state->flags &= ~(kRetireAfterFade | kFadeActive);
        }
    }

    env->flush();
    env->set_render_state(14, 0);
    env->flush();
    env->set_render_state(23, 8);
    SetAlphaBlendState(0, env);
    return 1;
}
