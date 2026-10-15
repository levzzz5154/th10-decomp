// Compiler context only; never selected as recovered game code.
#include "../../../src/script/sptlib/ecl_pop_scratch_value_004506d0.cpp"

#pragma code_seg(".text$03context")
int __stdcall EclFramePopContext_004506d0(EclFrame_00450690* frames, int count) {
    int result = 0;
    for (int i = 0; i < count; ++i)
        result += frames[i].Pop();
    return result;
}
#pragma code_seg()
