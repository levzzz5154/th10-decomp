#include "th10/game/score_runtime_ui_update.hpp"

namespace {

const uint32_t kActive = 1u;
const uint32_t kShowScore = 2u;
const uint32_t kWideLayout = 4u;
const uint32_t kFreezeDecay = 8u;
const int kDigitScriptBase = 30;
const int kHiddenScoreScript = 41;

void SetPair(int value, int first_slot, const ScoreRuntimeUiOps* ops) {
    if (value > 99) value = 99;
    ops->set_digit_script(ops->context, first_slot,
                          value / 10 + kDigitScriptBase);
    ops->set_digit_script(ops->context, first_slot + 1,
                          value % 10 + kDigitScriptBase);
}

}  // namespace

// 0x00408D60 - update score-panel animation, digits, layout, and the camera
// marker.  The direct PE32 caller 0x00409220 moves ECX to EDI before calling;
// the retail body has no stack arguments and treats EDI as the sole state
// pointer.  This conventional-ABI form makes that register binding explicit.
int ScoreRuntimeUi_Update(ScoreRuntimeUiState* state,
                          const ScoreRuntimeUiEnv* env,
                          const ScoreRuntimeUiOps* ops) {
    if ((state->flags & kActive) == 0) return 1;

    if (state->frame >= 60 && env->release_flags != 0)
        *env->release_flags &= ~1u;

    // The two fixed ANM panels at +0x10 and +0x3BC are advanced before any
    // timer/layout work in the retail body.
    ops->tick_panel(ops->context, 0);
    ops->tick_panel(ops->context, 1);

    if (state->frame >= 300 && (state->flags & kFreezeDecay) == 0) {
        const int duration = state->score_decay_end_frame - 300;
        if (duration != 0) {
            const int decrement =
                (state->target_score - state->target_score / 10) / duration;
            const int next = state->displayed_score - decrement;
            state->displayed_score = next - next % 10;
        }
    }

    state->previous_frame = state->frame;
    const float scale = state->frame_scale == 0 ? 1.0f : *state->frame_scale;
    if (scale <= 0.99f || scale >= 1.01f) {
        state->frame_accumulator += scale;
        state->frame = static_cast<int>(state->frame_accumulator);
    } else {
        ++state->frame;
        state->frame_accumulator += 1.0f;
    }

    if (state->frame >= 120) {
        int mode = 0;
        if ((state->flags & kWideLayout) == 0 && env->playfield_x < 96.0f) {
            state->flags |= kWideLayout;
            mode = 3;
        } else if ((state->flags & kWideLayout) != 0 &&
                   env->playfield_x > 128.0f) {
            state->flags &= ~kWideLayout;
            mode = 2;
        }
        if (mode != 0) {
            for (int index = 0; index < 3; ++index)
                ops->set_aux_mode(ops->context, index, mode);
            for (int index = 0; index < 8; ++index)
                state->stage_modes[index] = static_cast<int16_t>(mode);
            for (int index = 0; index < 5; ++index)
                state->effect_modes[index] = static_cast<int16_t>(mode);
        }
    }

    if ((state->flags & kShowScore) != 0) {
        int score = state->displayed_score;
        int divisor = 10000000;
        for (int slot = 0; slot < 8; ++slot) {
            ops->set_digit_script(ops->context, slot,
                                  score / divisor + kDigitScriptBase);
            score %= divisor;
            divisor /= 10;
            ops->tick_digit(ops->context, slot);
        }
    } else {
        ops->set_digit_script(ops->context, 8, kHiddenScoreScript);
        ops->tick_digit(ops->context, 8);
    }

    SetPair(env->metric_a, 9, ops);
    SetPair(env->metric_b, 11, ops);
    for (int slot = 9; slot < 14; ++slot)
        ops->tick_digit(ops->context, slot);

    for (int axis = 0; axis < 3; ++axis)
        state->camera_position[axis] +=
            (env->player_position[axis] - state->camera_position[axis]) * 0.05f;
    ops->publish_camera(ops->context, state->camera_position);
    return 1;
}
