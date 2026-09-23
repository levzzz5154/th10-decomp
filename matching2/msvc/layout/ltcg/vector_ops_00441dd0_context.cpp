// Compiler context only; never selected as recovered game code.
#include "../../src/unidentified/unassigned_00441dd0.cpp"

#pragma code_seg(".text$04context")
extern "C" __declspec(noinline) int __stdcall VectorOpsCompilerContext(
        Vec2_00441dd0* difference_outputs,
        Vec2_00441dd0* scale_outputs,
        const Vec2_00441dd0* const* lefts,
        const Vec2_00441dd0* const* rights,
        const float* scales,
        int count) {
    for (int index = 0; index < count; ++index) {
        difference_outputs[index] = *lefts[index] - *rights[index];
    }
    for (int index = 0; index < count; ++index) {
        scale_outputs[index] = *lefts[index] * scales[index];
    }
    return 0;
}
#pragma code_seg()
