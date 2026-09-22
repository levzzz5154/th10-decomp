// 0x00405260..0x00405278: add two three-component vectors.
//
// Native LTCG keeps the first vector in ECX, the second in EDX, and the
// hidden result object in EAX.  The constructor temporary retains retail's
// z/y/x x87 order and direct stores.
struct Vector3_00405260 {
    float x;
    float y;
    float z;

    Vector3_00405260(float x_value, float y_value, float z_value)
        : x(x_value), y(y_value), z(z_value) {}

    __declspec(noinline) Vector3_00405260 operator+(
            const Vector3_00405260& right) const;
};

#pragma code_seg(".text$05add")
Vector3_00405260 Vector3_00405260::operator+(
        const Vector3_00405260& right) const {
    return Vector3_00405260(x + right.x, y + right.y, z + right.z);
}
#pragma code_seg()
