// =============================================================================
// param_block_interp.cpp - Four-block parameter interpolator
// Functions: 0x004049A0
// =============================================================================
#include "th10/math/param_block_interp.hpp"
#include "th10/math/easing.hpp"

// Retail's shared time scale. The completion path republishes the interpolator's
// speed pointer here, exactly as the timer helpers in math_utils.cpp do.
extern unsigned int DAT_00476f78;

namespace {

// Retail immediates: _DAT_00470B68 = 0.99, _DAT_00470B64 = 1.01,
// _DAT_00470AFC = 1.0, _DAT_00470BD4 = 3.0.
const float kSpeedLowerBound = 0.99f;
const float kSpeedUpperBound = 1.01f;

} // namespace

// 0x004049A0 - Advance a four-block parameter interpolator one frame.
//
// The frame step is speed-aware: when the referenced time scale sits inside the
// (0.99, 1.01) dead band retail takes the integer fast path, bumping the frame
// counter by one and the accumulator by 1.0. Outside the band the accumulator
// takes the fractional speed and the frame counter is re-derived from it by
// truncation (retail routes that through the float-to-integer helper at
// 0x00463B2C).
//
// Reaching the duration completes the run. Retail first lazily installs the
// sentinel state - frame 0, previous -999999, accumulator 0, the shared speed
// pointer - and latches bit 0 of the flags so that only happens once, then
// immediately overwrites the counters with the completed duration values. The lasting
// effects of that block are therefore the republished speed pointer and the
// flag bit; the counter stores are dead. Duration is then cleared, which makes
// every later call fall through to the evaluation half, and the completing
// frame publishes block A for the integrating mode or block B otherwise.
QuantizedVector* ParamBlockInterp_Tick(ParamBlockInterp* state,
                                       QuantizedVector* result) {
    if (state->duration > 0) {
        const int current = state->current;
        const float speed = *state->speed;
        state->previous = current;
        if (speed <= kSpeedLowerBound || speed >= kSpeedUpperBound) {
            const float elapsed = speed + state->elapsed;
            state->elapsed = elapsed;
            state->current = (int)elapsed;
        } else {
            state->current = current + 1;
            state->elapsed = state->elapsed + 1.0f;
        }

        const int duration = state->duration;
        if (state->current >= duration) {
            const int flags = state->flags;
            if ((flags & 1) == 0) {
                state->current = 0;
                state->previous = PARAM_BLOCK_INTERP_SENTINEL;
                // Retail stores an integer zero over this float field; the bit
                // pattern is identical to 0.0f.
                state->elapsed = 0.0f;
                state->speed = (const float*)&DAT_00476f78;
                state->flags = flags | 1;
            }
            state->current = duration;
            state->previous = duration - 1;
            state->elapsed = (float)duration;

            const int mode = state->mode;
            state->duration = 0;
            *result = (mode == PARAM_BLOCK_INTERP_MODE_INTEGRATE)
                          ? state->blocks[0]
                          : state->blocks[1];
            return result;
        }
    }

    // Evaluation half. A completed or never-armed interpolator lands here too,
    // which is what keeps the two integrating modes running past their
    // duration.
    const int mode = state->mode;
    const QuantizedVector* source;
    QuantizedVector scratch;

    if (mode == PARAM_BLOCK_INTERP_MODE_INTEGRATE) {
        // A += B, evaluated through a copy of A because retail stages the sum
        // in a stack temporary before writing it back.
        const QuantizedVector previous = state->blocks[0];
        Vec_Add(&scratch, &state->blocks[1], &previous);
        state->blocks[0] = scratch;
        source = &state->blocks[0];
    } else if (mode == PARAM_BLOCK_INTERP_MODE_INTEGRATE2) {
        // Second order: A picks up the current D, then D picks up B. A is
        // advanced with the pre-update D, matching retail's ordering.
        const QuantizedVector previous_value = state->blocks[0];
        Vec_Add(&scratch, &state->blocks[3], &previous_value);
        state->blocks[0] = scratch;

        const QuantizedVector previous_rate = state->blocks[3];
        Vec_Add(&scratch, &state->blocks[1], &previous_rate);
        state->blocks[3] = scratch;
        source = &state->blocks[0];
    } else if (mode == PARAM_BLOCK_INTERP_MODE_HERMITE) {
        // Cubic Hermite basis over value, target, start tangent, end tangent:
        //   h00 = (2t + 1)(t - 1)^2   applied to block A
        //   h01 = (3 - 2t)t^2         applied to block B
        //   h10 = (1 - t)^2 t         applied to block C
        //   h11 = (t - 1)t^2          applied to block D
        const float t = state->elapsed / (float)state->duration;
        const float t_minus_one = t - 1.0f;
        const float weight_value = (t + t + 1.0f) * t_minus_one * t_minus_one;
        const float weight_target = (3.0f - (t + t)) * t * t;
        const float weight_start = (1.0f - t) * (1.0f - t) * t;
        const float weight_end = t_minus_one * t * t;

        QuantizedVector scaled_end;
        QuantizedVector scaled_start;
        QuantizedVector scaled_target;
        QuantizedVector scaled_value;
        Vec_Scale(&scaled_end, &state->blocks[3], weight_end);
        Vec_Scale(&scaled_start, &state->blocks[2], weight_start);
        Vec_Scale(&scaled_target, &state->blocks[1], weight_target);
        Vec_Scale(&scaled_value, &state->blocks[0], weight_value);

        QuantizedVector partial;
        Vec_Add(&partial, &scaled_target, &scaled_value);
        QuantizedVector partial_with_start;
        Vec_Add(&partial_with_start, &scaled_start, &partial);
        Vec_Add(&scratch, &scaled_end, &partial_with_start);
        source = &scratch;
    } else {
        // Eased blend: A + (B - A) * ease(mode, elapsed / duration). Retail
        // subtracts the EAX operand from the ECX operand, so the delta really
        // is target minus value.
        const float eased = Easing_Evaluate(mode, state->elapsed,
                                            (float)state->duration);
        QuantizedVector delta;
        Vec_Subtract(&delta, &state->blocks[1], &state->blocks[0]);
        QuantizedVector weighted;
        Vec_Scale(&weighted, &delta, eased);
        Vec_Add(&scratch, &state->blocks[0], &weighted);
        source = &scratch;
    }

    *result = *source;
    return result;
}
