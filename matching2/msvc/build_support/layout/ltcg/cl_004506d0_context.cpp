// Compiler context only; never selected as recovered game code.
#include "../../../src/script/sptlib/ecl_pop_scratch_value.cpp"

#pragma code_seg(".text$03context")
int __stdcall EclFramePopContext_004506d0(EclFrame4* frames, int count) {
    int result = 0;
    for (int i = 0; i < count; ++i)
        result += frames[i].Pop();
    return result;
}
#pragma code_seg()
