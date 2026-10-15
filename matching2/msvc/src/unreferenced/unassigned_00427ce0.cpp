// 0x00427CE0..0x00427CFD: convert two integer components to a scaled vector.
struct IntPair_00427ce0;
struct Vector3_00427ce0 {
    float x;
    float y;
    float z;

    Vector3_00427ce0(const IntPair_00427ce0& value);
};

struct IntPair_00427ce0 {
    int x;
    int y;

    __declspec(noinline) Vector3_00427ce0 ToVector() const;
};

Vector3_00427ce0::Vector3_00427ce0(const IntPair_00427ce0& value)
    : x((float)value.x * 0.01f), y((float)value.y * 0.01f), z(0.0f) {
}

#pragma code_seg(".text$03convert")
Vector3_00427ce0 IntPair_00427ce0::ToVector() const {
    return Vector3_00427ce0(*this);
}
#pragma code_seg()
