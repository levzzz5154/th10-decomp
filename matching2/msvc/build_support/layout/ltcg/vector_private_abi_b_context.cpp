// Compiler context only; never selected as recovered game code.
#include "../../../src/unreferenced/unassigned_41f780.cpp"

struct Vector310 {
    float x;
    float y;
    float z;
};
struct IntPair2 {
    int x;
    int y;
    __declspec(noinline) Vector310 ToVector() const;
};

#pragma code_seg(".text$05context")
extern "C" __declspec(noinline) void __stdcall VectorPrivateAbiCompilerContext(
        Vector39** scale_values, float* scales, Vector39** scale_out,
        IntPair2** convert_values, Vector310* convert_out, int count) {
    for (int index = 0; index < count; ++index)
        scale_values[index]->ScaleBy(scales[index], scale_out[index]);
    for (int index = 0; index < count; ++index)
        convert_out[index] = convert_values[index]->ToVector();
}
#pragma code_seg()
