// Compiler context only; never selected as recovered game code.
#include "../../src/core/sprtanim/random_vector.cpp"

#pragma code_seg(".text$03context")
int __stdcall RandomVectorCompilerContext(
        RandomVectorSource* sources, RandomVectorResult* results, int count, float scale) {
    for (int index = 0; index < count; ++index)
        RandomVector_StoreRoundedScalar(&sources[index], &results[index], scale);
    return 0;
}
#pragma code_seg()
