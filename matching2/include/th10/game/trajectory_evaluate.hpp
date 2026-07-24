#pragma once

// Embedded-timer trajectory mode evaluation (retail 0x00412AC0).
// Retail function 0x00412AC0.
struct Trajectory2D{float p0[2],velocity[2],p2[2],acceleration[2];int previous,current;float elapsed;const float*speed;unsigned timer_flags;int duration,mode;};struct TrajectoryEnv{const float*default_speed;float(*ease)(float,float);};void Trajectory_Evaluate2D(Trajectory2D*,float[2],const TrajectoryEnv*);
