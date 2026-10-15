// 0x00404E70..0x00404E8E: scale a three-component vector.
//
// Native LTCG keeps the source object in ECX, the hidden result object in EAX,
// and the scalar on the stack.  Returning a constructor temporary preserves
// retail's z/y/x x87 evaluation and direct result stores.
struct Vector3_00404e70 {
    float x;
    float y;
    float z;

    Vector3_00404e70(float x_value, float y_value, float z_value)
        : x(x_value), y(y_value), z(z_value) {}
};

struct VectorScale {
    float x;
    float y;
    float z;

    __declspec(noinline) Vector3_00404e70 Scale(float value) const;
};

#pragma code_seg(".text$01scale")
Vector3_00404e70 VectorScale::Scale(float value) const {
    return Vector3_00404e70(x * value, y * value, z * value);
}
#pragma code_seg()
