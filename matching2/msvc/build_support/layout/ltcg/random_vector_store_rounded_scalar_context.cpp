// Compiler context only; never selected as recovered game code.
#include "../../../src/core/sprtanim/int3_scale.cpp"

#pragma code_seg(".text$03context")
int __stdcall RandomVectorCompilerContext(
        Int3* sources, Int3* results, int count, float scale) {
    for (int index = 0; index < count; ++index)
        Int3_ScaleTruncate(&sources[index], &results[index], scale);
    return 0;
}
#pragma code_seg()
