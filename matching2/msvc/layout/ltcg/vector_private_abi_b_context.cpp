// Compiler context only; never selected as recovered game code.
#include "../../src/unidentified/unassigned_0041f780.cpp"

struct Vector3_00427ce0 {
    float x;
    float y;
    float z;
};
struct IntPair_00427ce0 {
    int x;
    int y;
    __declspec(noinline) Vector3_00427ce0 ToVector() const;
};

#pragma code_seg(".text$05context")
extern "C" __declspec(noinline) void __stdcall VectorPrivateAbiCompilerContext(
        Vector3_0041f780** scale_values, float* scales, Vector3_0041f780** scale_out,
        IntPair_00427ce0** convert_values, Vector3_00427ce0* convert_out, int count) {
    for (int index = 0; index < count; ++index)
        scale_values[index]->ScaleBy(scales[index], scale_out[index]);
    for (int index = 0; index < count; ++index)
        convert_out[index] = convert_values[index]->ToVector();
}
#pragma code_seg()
