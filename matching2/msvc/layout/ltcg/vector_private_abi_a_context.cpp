// Compiler context only; never selected as recovered game code.
#include "../../src/unreferenced/unassigned_00404e70.cpp"

struct Vector3_00405240 {
    float x;
    float y;
    float z;
};
__declspec(noinline) Vector3_00405240 __fastcall VectorSubtract_00405240(
        const Vector3_00405240& left, const Vector3_00405240& right);

struct Vector3_00405260 {
    float x;
    float y;
    float z;

    __declspec(noinline) Vector3_00405260 operator+(
            const Vector3_00405260& right) const;
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
        *(Vector3_00404e70*)outputs[index] =
            ((VectorScale_00404e70*)scales[index])->Scale(scale);
    for (int index = 0; index < count; ++index)
        *(Vector3_00405240*)outputs[index] =
            VectorSubtract_00405240(
                *(Vector3_00405240*)left[index],
                *(Vector3_00405240*)right[index]);
    for (int index = 0; index < count; ++index)
        *(Vector3_00405260*)outputs[index] =
            (*(Vector3_00405260*)left[index]) +
            (*(Vector3_00405260*)right[index]);
}
#pragma code_seg()
