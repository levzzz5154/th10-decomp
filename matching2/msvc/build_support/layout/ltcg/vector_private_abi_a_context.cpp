// Compiler context only; never selected as recovered game code.
#include "../../../src/unreferenced/unassigned_404e70.cpp"

struct Vector34 {
    float x;
    float y;
    float z;
};
__declspec(noinline) Vector34 __fastcall VectorSubtract(
        const Vector34& left, const Vector34& right);

struct Vector35 {
    float x;
    float y;
    float z;

    __declspec(noinline) Vector35 operator+(
            const Vector35& right) const;
};

#pragma code_seg(".text$07context")
extern "C" __declspec(noinline) void __stdcall VectorPrivateAbiAContext(
        void* const* scales,
        void* const* left,
        void* const* right,
        void* const* outputs,
        float scale,
        int count) {
    for (int index = 0; index < count; ++index)
        *(Vector32*)outputs[index] =
            ((VectorScale*)scales[index])->Scale(scale);
    for (int index = 0; index < count; ++index)
        *(Vector34*)outputs[index] =
            VectorSubtract(
                *(Vector34*)left[index],
                *(Vector34*)right[index]);
    for (int index = 0; index < count; ++index)
        *(Vector35*)outputs[index] =
            (*(Vector35*)left[index]) +
            (*(Vector35*)right[index]);
}
#pragma code_seg()
