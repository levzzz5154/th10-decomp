// 0x00427CE0..0x00427CFD: convert two integer components to a scaled vector.
struct IntPair2;
struct Vector310 {
    float x;
    float y;
    float z;

    Vector310(const IntPair2& value);
};

struct IntPair2 {
    int x;
    int y;

    __declspec(noinline) Vector310 ToVector() const;
};

Vector310::Vector310(const IntPair2& value)
    : x((float)value.x * 0.01f), y((float)value.y * 0.01f), z(0.0f) {
}

#pragma code_seg(".text$03convert")
Vector310 IntPair2::ToVector() const {
    return Vector310(*this);
}
#pragma code_seg()
