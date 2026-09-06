#include "th10/game/trajectory_evaluate.hpp"
#include "th10/math/easing.hpp"
#include "th10/math/retail_numeric.hpp"

namespace {

const float kNormalSpeedLow = 0.99000001f;
const float kNormalSpeedHigh = 1.01f;
const int kLinearIncrementMode = 7;
const int kAcceleratingIncrementMode = 17;
const int kHermiteMode = 8;

void FinishTrajectory(Trajectory2D* state, float output[2],
                      const TrajectoryEnv* env, int duration) {
    if (!(state->timer_flags & 1)) {
        state->current = 0;
        state->previous = -999999;
        state->elapsed = 0.0f;
        state->speed = env->default_speed;
        state->timer_flags |= 1;
    }

    state->current = duration;
    state->previous = duration - 1;
    state->elapsed = static_cast<float>(duration);
    state->duration = 0;

    float* final_value = state->mode == kLinearIncrementMode
        ? state->p0 : state->velocity;
    output[0] = final_value[0];
    output[1] = final_value[1];
}

}  // namespace

// 0x00412AC0 - Advance the embedded timer and evaluate one of the retail
// trajectory modes. Completion publishes the terminal value and disables the
// active duration while preserving the timer's sentinel initialization.
void Trajectory_Evaluate2D(Trajectory2D* state, float output[2],
                           const TrajectoryEnv* env) {
    const int duration = state->duration;
    if (duration > 0) {
        state->previous = state->current;
        const float speed = *state->speed;
        if (speed <= kNormalSpeedLow || speed >= kNormalSpeedHigh) {
            const long double elapsed = static_cast<long double>(speed) + state->elapsed;
            state->elapsed = static_cast<float>(elapsed);
            state->current = Retail_TruncateI32(elapsed);
        } else {
            state->elapsed += 1.0f;
            state->current = Retail_AddI32(state->current, 1);
        }

        if (duration <= state->current) {
            FinishTrajectory(state, output, env, duration);
            return;
        }
    }

    if (state->mode == kLinearIncrementMode) {
        for (int axis = 0; axis < 2; ++axis) {
            state->p0[axis] += state->velocity[axis];
            output[axis] = state->p0[axis];
        }
    } else if (state->mode == kAcceleratingIncrementMode) {
        for (int axis = 0; axis < 2; ++axis) {
            state->p0[axis] += state->acceleration[axis];
            output[axis] = state->p0[axis];
            state->acceleration[axis] += state->velocity[axis];
        }
    } else if (state->mode == kHermiteMode) {
        const float time = state->elapsed / duration;
        const float time_minus_one = time - 1.0f;
        const float h00 = (1.0f + 2.0f * time) *
                          time_minus_one * time_minus_one;
        const float h01 = (3.0f - 2.0f * time) * time * time;
        const float h10 = (1.0f - time) * (1.0f - time) * time;
        const float h11 = time_minus_one * time * time;
        for (int axis = 0; axis < 2; ++axis) {
            output[axis] = h00 * state->p0[axis] +
                           h01 * state->velocity[axis] +
                           h10 * state->p2[axis] +
                           h11 * state->acceleration[axis];
        }
    } else {
        const float factor =
            env->ease(state->elapsed, static_cast<float>(duration),
                      state->mode);
        for (int axis = 0; axis < 2; ++axis) {
            output[axis] =
                (state->velocity[axis] - state->p0[axis]) * factor +
                state->p0[axis];
        }
    }
}

// 0x0044C350 - the retail ease curve table.  t = elapsed/duration; modes
// 1-3 are accelerating powers, 4-6 decelerating powers, 9-14 the 2t
// smooth-step pairs, 15 the zero curve, 16 the hold curve, and everything
// else (0, 7, ...) the linear default.
float Trajectory_EaseFraction(float elapsed, float duration, int mode) {
    return Easing_Evaluate(mode, elapsed, duration);
}

// 0x00404610 - advance the embedded timer and evaluate a three-component
// trajectory record (the 0x119/0x11b per-axis sub-records).  Mode 7 adds
// the target row every frame, mode 0x11 integrates the control-B row, mode
// 8 evaluates the cubic bezier through both control rows, and every other
// mode eases between the start and target rows.  Completion publishes the
// terminal value and disarms the duration.
void Trajectory_Evaluate3D(Trajectory3D* state, float output[3],
                           const TrajectoryEnv* env) {
    const int duration = state->duration;
    if (duration > 0) {
        state->previous = state->current;
        const float speed = *state->speed;
        if (speed <= kNormalSpeedLow || speed >= kNormalSpeedHigh) {
            const long double elapsed = static_cast<long double>(speed) + state->elapsed;
            state->elapsed = static_cast<float>(elapsed);
            state->current = Retail_TruncateI32(elapsed);
        } else {
            state->elapsed += 1.0f;
            state->current = Retail_AddI32(state->current, 1);
        }

        if (duration <= state->current) {
            if (!(state->timer_flags & 1)) {
                state->current = 0;
                state->previous = -999999;
                state->elapsed = 0.0f;
                state->speed = env->default_speed;
                state->timer_flags |= 1;
            }
            state->current = duration;
            state->previous = duration - 1;
            state->elapsed = static_cast<float>(duration);
            state->duration = 0;

            const float* final_value =
                state->mode == kLinearIncrementMode ? state->p0
                                                    : state->velocity;
            for (int axis = 0; axis < 3; ++axis)
                output[axis] = final_value[axis];
            return;
        }
    }

    if (state->mode == kLinearIncrementMode) {
        for (int axis = 0; axis < 3; ++axis) {
            state->p0[axis] += state->velocity[axis];
            output[axis] = state->p0[axis];
        }
    } else if (state->mode == kAcceleratingIncrementMode) {
        for (int axis = 0; axis < 3; ++axis) {
            state->p0[axis] += state->control_b[axis];
            output[axis] = state->p0[axis];
            state->control_b[axis] += state->velocity[axis];
        }
    } else if (state->mode == kHermiteMode) {
        const float time = state->elapsed / duration;
        const float time_minus_one = time - 1.0f;
        const float h00 = (1.0f + 2.0f * time) *
                          time_minus_one * time_minus_one;
        const float h01 = (3.0f - 2.0f * time) * time * time;
        const float h10 = (1.0f - time) * (1.0f - time) * time;
        const float h11 = time_minus_one * time * time;
        for (int axis = 0; axis < 3; ++axis) {
            output[axis] = h00 * state->p0[axis] +
                           h01 * state->velocity[axis] +
                           h10 * state->control_a[axis] +
                           h11 * state->control_b[axis];
        }
    } else {
        const float factor =
            env->ease(state->elapsed, static_cast<float>(duration),
                      state->mode);
        for (int axis = 0; axis < 3; ++axis) {
            output[axis] = (state->velocity[axis] - state->p0[axis]) *
                               factor +
                           state->p0[axis];
        }
    }
}
