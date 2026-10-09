// Compiler context only; never selected as recovered game code.
#include "../../src/game/fun_0044c350_0044c350.cpp"
#include "th10/math/interpolator.hpp"
#include "th10/math/vector.hpp"
#include "th10/math/trajectory_vector.hpp"
#include "th10/math/int3.hpp"
#include "th10/render/stage_fog.hpp"

struct InterpolatorSet {
    Interpolator<int> scalar;
    Interpolator<Vec2> planar;
    Interpolator<Vec3> spatial;
    Interpolator<Int3> colour;
    Interpolator<TrajectoryVec2> trajectory;
    Interpolator<StageFog> fog;
};

#pragma code_seg(".text$03context")
float __stdcall EvaluateCurveCompilerContext(const unsigned int* modes,
                                              const float* numerators,
                                              const float* denominators,
                                              int count,
                                              InterpolatorSet* sets) {
    float total = 0.0f;
    for (int index = 0; index < count; ++index) {
        total += sets[index].scalar.Step();
        total += sets[index].planar.Step().x;
        total += sets[index].spatial.Step().x;
        total += sets[index].colour.Step().x;
        total += sets[index].trajectory.Step().x;
        total += sets[index].fog.Step().start;
    }
    while (count--)
        total += EvaluateCurve_0044c350(*modes++, *numerators++, *denominators++);
    return total;
}
#pragma code_seg()
