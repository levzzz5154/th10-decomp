// Compiler context only; never selected as recovered game code.
#include "../../../src/unreferenced/unassigned_412e40.cpp"
#pragma code_seg(".text$03context")
extern "C" __declspec(noinline) void __stdcall ScaleContext_00412e40(
        Vec23** values, float* scales, Vec23** out, int count) {
    for (int index = 0; index < count; ++index)
        values[index]->ScaleBy(scales[index], out[index]);
}
#pragma code_seg()
