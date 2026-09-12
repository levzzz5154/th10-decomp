#pragma once

// Embedded-timer trajectory mode evaluation (retail 0x00412AC0 / 0x00404610).
// The ease callback receives the record's mode so it can dispatch through
// the full retail 0x0044C350 curve table.
struct TrajectoryEnv {
    const float* default_speed;
    float (*ease)(float elapsed, float duration, int mode);
};

// Retail function 0x00412AC0.  Record layout is byte-identical to the
// per-axis ECL movement records (entity transform +0x1D4/+0x210/+0x24C/
// +0x288): [0..1] p0, [2..3] velocity, [4..5] p2, [6..7] acceleration,
// [8] previous, [9] current, [10] elapsed, [11] speed pointer, [12] flags,
// [13] duration, [14] mode.
struct Trajectory2D {
    float p0[2], velocity[2], p2[2], acceleration[2];
    int previous, current;
    float elapsed;
    const float* speed;
    unsigned timer_flags;
    int duration, mode;
};
void Trajectory_Evaluate2D(Trajectory2D*, float[2], const TrajectoryEnv*);

// Retail function 0x00404610.  Record layout is byte-identical to the
// 0x119/0x11b per-axis sub-records (entity transform +0x13C/+0x188):
// [0..2] start triple, [3..5] target triple, [6..8] and [9..11] bezier
// control rows, [12] previous, [13] current, [14] elapsed, [15] speed
// pointer, [16] flags, [17] duration, [18] mode.
struct Trajectory3D {
    float p0[3];
    float velocity[3];
    float control_a[3];
    float control_b[3];
    int previous;
    int current;
    float elapsed;
    const float* speed;
    unsigned timer_flags;
    int duration;
    int mode;
};
void Trajectory_Evaluate3D(Trajectory3D*, float[3], const TrajectoryEnv*);

// Retail function 0x0044C350: mode-curve table over t = elapsed/duration.
float Trajectory_EaseFraction(float elapsed, float duration, int mode);
