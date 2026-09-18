#pragma once

#include "th10/math/timer.hpp"

// Recovered prefix of the score record. Values stored in score and gauge use
// tenths of the units accepted by their update methods.
struct ScoreState {
    int unknown_00;
    int score;
    unsigned char unknown_08[4];
    int gauge;
    int gauge_decay;
    FrameTimer gauge_timer;
    unsigned char unknown_28[40];
    int capped_count;

    __declspec(noinline) void AddScore(int amount);
    __declspec(noinline) void ReduceGauge(int amount);
    __declspec(noinline) void IncrementCappedCount();
    __declspec(noinline) void SetGauge(int amount);
    __declspec(noinline) void AddGauge(int amount);
    __declspec(noinline) void DecayGauge();
};

typedef char ScoreState_score_offset_must_be_4[offsetof(ScoreState, score) == 4 ? 1 : -1];
typedef char ScoreState_gauge_offset_must_be_12[offsetof(ScoreState, gauge) == 12 ? 1 : -1];
typedef char ScoreState_timer_offset_must_be_20[offsetof(ScoreState, gauge_timer) == 20 ? 1 : -1];
typedef char ScoreState_count_offset_must_be_80[offsetof(ScoreState, capped_count) == 80 ? 1 : -1];

// Clamp a requested signed counter value against the active upper bound.
// The fastcall ABI reflects the retail entry: requested arrives in ECX and
// the counter record in EDX.
unsigned int __fastcall UpdateBoundedCounter(
    unsigned int requested, unsigned int* counter);
