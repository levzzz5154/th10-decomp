// 0x00405220..0x0040523E: squared length of a three-component vector.
struct Vector3_00405220 {
    float x;
    float y;
    float z;

    __declspec(noinline) float LengthSquared() const;
};

#pragma code_seg(".text$01")
float Vector3_00405220::LengthSquared() const {
    return x * x + y * y + z * z;
}
#pragma code_seg()
