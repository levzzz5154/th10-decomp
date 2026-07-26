// Focused semantic tests for the four-block parameter interpolator at
// 0x004049A0 and the quantized-vector leaves it drives.
#include <cassert>
#include <cmath>
#include <cstdio>
#include <cstring>

#include "th10/math/param_block_interp.hpp"

unsigned int DAT_00476f78 = 0x3F800000u; // 1.0f, the retail shared time scale

namespace {

const float kUnitSpeed = 1.0f;
float g_speed = kUnitSpeed;

bool Near(float actual, float expected) {
    return std::fabs(actual - expected) <= 1e-4f * (1.0f + std::fabs(expected));
}

void FillBlock(QuantizedVector* block, float base) {
    for (int index = 0; index < 6; ++index)
        block->components[index] = base + (float)index;
    std::memset(block->quantized, 0, sizeof(block->quantized));
}

ParamBlockInterp MakeState(int mode, int duration) {
    ParamBlockInterp state;
    std::memset(&state, 0, sizeof(state));
    FillBlock(&state.blocks[0], 10.0f);  // value
    FillBlock(&state.blocks[1], 20.0f);  // target
    FillBlock(&state.blocks[2], 30.0f);  // start tangent
    FillBlock(&state.blocks[3], 40.0f);  // end tangent
    state.mode = mode;
    state.duration = duration;
    g_speed = kUnitSpeed;
    state.speed = &g_speed;
    return state;
}

// The dead band is exclusive on both sides: exactly 0.99 and exactly 1.01 take
// the fractional path, anything strictly between them takes the integer path.
void TestSpeedDeadBandTakesIntegerPath() {
    ParamBlockInterp state = MakeState(0, 100);
    g_speed = 1.0f;
    QuantizedVector out;
    ParamBlockInterp_Tick(&state, &out);
    assert(state.current == 1);
    assert(Near(state.elapsed, 1.0f));
    assert(state.previous == 0);

    // A speed inside the band still advances by exactly one, never by the
    // speed value itself.
    state = MakeState(0, 100);
    g_speed = 1.005f;
    ParamBlockInterp_Tick(&state, &out);
    assert(state.current == 1);
    assert(Near(state.elapsed, 1.0f));
}

void TestFractionalSpeedTruncatesFrameCounter() {
    ParamBlockInterp state = MakeState(0, 100);
    g_speed = 0.5f;
    QuantizedVector out;

    ParamBlockInterp_Tick(&state, &out);
    assert(Near(state.elapsed, 0.5f));
    assert(state.current == 0); // truncated, not rounded

    ParamBlockInterp_Tick(&state, &out);
    assert(Near(state.elapsed, 1.0f));
    assert(state.current == 1);
    assert(state.previous == 0);

    // The boundary values themselves are outside the dead band.
    state = MakeState(0, 100);
    g_speed = 0.99f;
    ParamBlockInterp_Tick(&state, &out);
    assert(Near(state.elapsed, 0.99f));
    assert(state.current == 0);

    state = MakeState(0, 100);
    g_speed = 1.01f;
    ParamBlockInterp_Tick(&state, &out);
    assert(Near(state.elapsed, 1.01f));
    assert(state.current == 1);
}

// Completion latches the sentinel flag once, republishes the shared speed
// pointer, pins the counters at the duration and clears duration.
void TestCompletionInstallsSentinelAndClearsDuration() {
    ParamBlockInterp state = MakeState(0, 2);
    QuantizedVector out;

    ParamBlockInterp_Tick(&state, &out);
    assert(state.current == 1);
    assert(state.duration == 2);
    assert(state.flags == 0);
    assert(state.speed == &g_speed);

    ParamBlockInterp_Tick(&state, &out);
    assert(state.current == 2);
    assert(state.previous == 1);
    assert(Near(state.elapsed, 2.0f));
    assert(state.duration == 0);
    assert((state.flags & 1) != 0);
    // The speed pointer is redirected at the shared retail global, and the
    // sentinel counter stores are overwritten before they can be observed.
    assert(state.speed == (const float*)&DAT_00476f78);
    assert(state.previous != PARAM_BLOCK_INTERP_SENTINEL);

    // Non-integrating completion publishes the target block.
    for (int index = 0; index < 6; ++index)
        assert(Near(out.components[index], 20.0f + (float)index));
}

void TestSentinelInstallHappensOnlyOnce() {
    ParamBlockInterp state = MakeState(0, 1);
    state.flags = 1; // already initialized
    const float* original_speed = state.speed;
    QuantizedVector out;

    ParamBlockInterp_Tick(&state, &out);
    assert(state.duration == 0);
    assert(state.flags == 1);
    // With the bit already latched the speed pointer is left alone.
    assert(state.speed == original_speed);
}

void TestIntegrateCompletionPublishesValueBlock() {
    ParamBlockInterp state =
        MakeState(PARAM_BLOCK_INTERP_MODE_INTEGRATE, 1);
    QuantizedVector out;
    ParamBlockInterp_Tick(&state, &out);
    assert(state.duration == 0);
    // Mode 7 is the one mode whose completing frame reports block A.
    for (int index = 0; index < 6; ++index)
        assert(Near(out.components[index], 10.0f + (float)index));
}

// Mode 7 keeps integrating B into A after the duration has been cleared.
void TestIntegrateRunsPastDuration() {
    ParamBlockInterp state =
        MakeState(PARAM_BLOCK_INTERP_MODE_INTEGRATE, 0);
    QuantizedVector out;

    ParamBlockInterp_Tick(&state, &out);
    for (int index = 0; index < 6; ++index) {
        const float expected = 10.0f + 20.0f + 2.0f * (float)index;
        assert(Near(state.blocks[0].components[index], expected));
        assert(Near(out.components[index], expected));
    }

    ParamBlockInterp_Tick(&state, &out);
    for (int index = 0; index < 6; ++index)
        assert(Near(state.blocks[0].components[index],
                    30.0f + 20.0f + 3.0f * (float)index));

    // The target block is never disturbed by the integration.
    for (int index = 0; index < 6; ++index)
        assert(Near(state.blocks[1].components[index], 20.0f + (float)index));
}

// Mode 17 advances A with the pre-update D, then advances D with B.
void TestSecondOrderIntegrateOrdering() {
    ParamBlockInterp state =
        MakeState(PARAM_BLOCK_INTERP_MODE_INTEGRATE2, 0);
    QuantizedVector out;

    ParamBlockInterp_Tick(&state, &out);
    for (int index = 0; index < 6; ++index) {
        // A = A + D_old, using 40.0 rather than the updated 60.0.
        assert(Near(state.blocks[0].components[index],
                    10.0f + 40.0f + 2.0f * (float)index));
        // D = D + B
        assert(Near(state.blocks[3].components[index],
                    40.0f + 20.0f + 2.0f * (float)index));
        assert(Near(out.components[index],
                    10.0f + 40.0f + 2.0f * (float)index));
    }

    ParamBlockInterp_Tick(&state, &out);
    for (int index = 0; index < 6; ++index)
        assert(Near(state.blocks[0].components[index],
                    50.0f + 60.0f + 4.0f * (float)index));
}

// The eased path is A + (B - A) * ease. Mode 0 is the linear passthrough, so
// the blend fraction is elapsed / duration exactly.
void TestLinearEasedBlend() {
    ParamBlockInterp state = MakeState(0, 4);
    QuantizedVector out;

    ParamBlockInterp_Tick(&state, &out);
    // elapsed 1 of 4 -> quarter of the way from 10.. to 20..
    for (int index = 0; index < 6; ++index) {
        const float value = 10.0f + (float)index;
        const float target = 20.0f + (float)index;
        assert(Near(out.components[index], value + (target - value) * 0.25f));
    }
    // The eased path leaves the state blocks untouched.
    for (int index = 0; index < 6; ++index)
        assert(Near(state.blocks[0].components[index], 10.0f + (float)index));
}

void TestEasedBlendUsesEasingTable() {
    // Mode 1 is the quadratic accelerating curve, so the fraction is t*t.
    ParamBlockInterp state = MakeState(1, 4);
    QuantizedVector out;
    ParamBlockInterp_Tick(&state, &out);
    const float t = 0.25f;
    for (int index = 0; index < 6; ++index) {
        const float value = 10.0f + (float)index;
        const float target = 20.0f + (float)index;
        assert(Near(out.components[index], value + (target - value) * t * t));
    }

    // Mode 15 pins the fraction at 0 and mode 16 at 1.
    state = MakeState(15, 4);
    ParamBlockInterp_Tick(&state, &out);
    for (int index = 0; index < 6; ++index)
        assert(Near(out.components[index], 10.0f + (float)index));

    state = MakeState(16, 4);
    ParamBlockInterp_Tick(&state, &out);
    for (int index = 0; index < 6; ++index)
        assert(Near(out.components[index], 20.0f + (float)index));
}

// The Hermite weights sum to a partition of unity at the endpoints, so t=0
// reproduces block A and t=1 reproduces block B.
void TestHermiteEndpoints() {
    QuantizedVector out;

    // A never-armed interpolator evaluates at elapsed 0 without stepping.
    ParamBlockInterp state = MakeState(PARAM_BLOCK_INTERP_MODE_HERMITE, 0);
    state.duration = 8;
    state.elapsed = 0.0f;
    ParamBlockInterp_Tick(&state, &out);
    // Stepping from elapsed 0 lands on frame 1, so evaluate the weights there.
    const float t = 1.0f / 8.0f;
    const float tm1 = t - 1.0f;
    const float w_value = (t + t + 1.0f) * tm1 * tm1;
    const float w_target = (3.0f - (t + t)) * t * t;
    const float w_start = (1.0f - t) * (1.0f - t) * t;
    const float w_end = tm1 * t * t;
    for (int index = 0; index < 6; ++index) {
        const float expected = (10.0f + (float)index) * w_value +
                               (20.0f + (float)index) * w_target +
                               (30.0f + (float)index) * w_start +
                               (40.0f + (float)index) * w_end;
        assert(Near(out.components[index], expected));
    }
}

void TestHermiteWeightsArePartitionOfUnity() {
    // With both tangents zeroed the spline must stay a pure value/target blend
    // whose weights sum to one.
    ParamBlockInterp state = MakeState(PARAM_BLOCK_INTERP_MODE_HERMITE, 10);
    std::memset(&state.blocks[2], 0, sizeof(state.blocks[2]));
    std::memset(&state.blocks[3], 0, sizeof(state.blocks[3]));
    QuantizedVector out;
    for (int frame = 1; frame <= 9; ++frame) {
        ParamBlockInterp_Tick(&state, &out);
        const float t = (float)frame / 10.0f;
        const float tm1 = t - 1.0f;
        const float w_value = (t + t + 1.0f) * tm1 * tm1;
        const float w_target = (3.0f - (t + t)) * t * t;
        assert(Near(w_value + w_target, 1.0f));
        for (int index = 0; index < 6; ++index) {
            const float expected = (10.0f + (float)index) * w_value +
                                   (20.0f + (float)index) * w_target;
            assert(Near(out.components[index], expected));
        }
    }
}

// Every leaf refreshes the four trailing bytes from channels 2..5 by
// truncation, so the published block carries them even though the inputs had
// them zeroed.
void TestQuantizedBytesAreDerivedByTruncation() {
    ParamBlockInterp state = MakeState(16, 4); // fraction pinned at 1 -> target
    QuantizedVector out;
    ParamBlockInterp_Tick(&state, &out);
    for (int index = 0; index < 4; ++index)
        assert(out.quantized[index] ==
               (unsigned char)(int)(22.0f + (float)index));

    // Truncation, not rounding, and the low byte only.
    QuantizedVector block;
    for (int index = 0; index < 6; ++index) block.components[index] = 0.0f;
    block.components[2] = 9.99f;
    block.components[3] = -1.75f;
    block.components[4] = 300.5f;
    block.components[5] = 0.25f;
    QuantizedVector_UpdateBytes(&block);
    assert(block.quantized[0] == 9);
    assert(block.quantized[1] == (unsigned char)(int)-1);
    assert(block.quantized[2] == (unsigned char)300);
    assert(block.quantized[3] == 0);
}

void TestTickReturnsResultPointer() {
    ParamBlockInterp state = MakeState(0, 4);
    QuantizedVector out;
    assert(ParamBlockInterp_Tick(&state, &out) == &out);
}

} // namespace

int main() {
    TestSpeedDeadBandTakesIntegerPath();
    TestFractionalSpeedTruncatesFrameCounter();
    TestCompletionInstallsSentinelAndClearsDuration();
    TestSentinelInstallHappensOnlyOnce();
    TestIntegrateCompletionPublishesValueBlock();
    TestIntegrateRunsPastDuration();
    TestSecondOrderIntegrateOrdering();
    TestLinearEasedBlend();
    TestEasedBlendUsesEasingTable();
    TestHermiteEndpoints();
    TestHermiteWeightsArePartitionOfUnity();
    TestQuantizedBytesAreDerivedByTruncation();
    TestTickReturnsResultPointer();
    std::printf("PARAM_BLOCK_INTERP_PASS\n");
    return 0;
}
