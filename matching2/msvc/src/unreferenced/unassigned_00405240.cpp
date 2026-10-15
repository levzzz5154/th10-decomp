// 0x00405240..0x00405258: subtract two three-component vectors.
//
// Native LTCG keeps the first vector in ECX, the second in EDX, and the
// hidden result object in EAX.  The constructor temporary retains retail's
// z/y/x x87 order and direct stores.
struct Vector3_00405240 {
    float x;
    float y;
    float z;

    Vector3_00405240(float x_value, float y_value, float z_value)
        : x(x_value), y(y_value), z(z_value) {}
};

#pragma code_seg(".text$03sub")
__declspec(noinline) Vector3_00405240 __fastcall VectorSubtract(
        const Vector3_00405240& left, const Vector3_00405240& right) {
    return Vector3_00405240(left.x - right.x,
                            left.y - right.y,
                            left.z - right.z);
}
#pragma code_seg()
