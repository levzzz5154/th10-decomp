#include "th10/game/trajectory_evaluate.hpp"
#include <cmath>
#include <cstdio>
static float one = 1;
static float E(float a, float b, int) { return a / b; }
int main() {
    Trajectory2D s = {};
    s.p0[0] = 1;
    s.velocity[0] = 3;
    s.speed = &one;
    s.duration = 10;
    s.mode = 7;
    float o[2];
    TrajectoryEnv e = {&one, E};
    Trajectory_Evaluate2D(&s, o, &e);
    if (o[0] != 4 || s.current != 1) return 1;
    s.mode = 0;
    s.current = 9;
    s.elapsed = 9;
    s.velocity[0] = 8;
    Trajectory_Evaluate2D(&s, o, &e);
    if (s.duration || o[0] != 8) return 1;

    // 3D linear-increment hold (mode 7).
    Trajectory3D t3 = {};
    t3.velocity[0] = 5;
    t3.speed = &one;
    t3.duration = 10;
    t3.mode = 7;
    float o3[3];
    Trajectory_Evaluate3D(&t3, o3, &e);
    if (o3[0] != 5 || o3[1] != 0 || t3.current != 1) return 1;

    // 3D accelerating increment (mode 0x11).
    Trajectory3D a3 = {};
    a3.velocity[0] = 2;
    a3.speed = &one;
    a3.duration = 10;
    a3.mode = 0x11;
    Trajectory_Evaluate3D(&a3, o3, &e);
    if (o3[0] != 0 || a3.control_b[0] != 2) return 1;

    // 3D ease through the retail curve table: pre-tick elapsed 4 ->
    // t = 5/10 = 0.5, mode 1 gives t^2 = 0.25 over the 8-wide span.
    TrajectoryEnv curve_env = {&one, Trajectory_EaseFraction};
    Trajectory3D e3 = {};
    e3.velocity[0] = 8;
    e3.speed = &one;
    e3.duration = 10;
    e3.mode = 1;
    e3.current = 4;
    e3.elapsed = 4;
    Trajectory_Evaluate3D(&e3, o3, &curve_env);
    if (std::fabs(o3[0] - 2.0f) > 1e-5f) return 1;

    // Completion publishes the target row (mode != 7) and disarms.
    e3.current = 9;
    e3.elapsed = 10;
    Trajectory_Evaluate3D(&e3, o3, &curve_env);
    if (e3.duration != 0 || o3[0] != 8) return 1;

    // Curve table sanity: mode 4 at t=0.5 -> 0.75, 15 -> 0, 16 -> 1.
    if (std::fabs(Trajectory_EaseFraction(5, 10, 4) - 0.75f) > 1e-6f)
        return 1;
    if (Trajectory_EaseFraction(5, 10, 15) != 0.0f) return 1;
    if (Trajectory_EaseFraction(5, 10, 16) != 1.0f) return 1;

    std::puts("recovery_batch38_test passed");
}
