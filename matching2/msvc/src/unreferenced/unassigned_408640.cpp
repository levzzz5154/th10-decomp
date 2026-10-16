// 0x00408640: squared length of the two-component vector.
//
// The vector pointer arrives in EAX, a convention no C++ declaration names, so
// the body is compiled as a single-function native-LTCG cluster.
struct Vec312 {
    float x;                                  // +0x0
    float y;                                  // +0x4
    float z;                                  // +0x8
};

struct ObjectAccessor_00408640 {
    float x;                                  // +0x0
    float y;                                  // +0x4
    float z;                                  // +0x8
    __declspec(noinline) float LengthSq() const;
};

#pragma code_seg(".text$01accessor")
float ObjectAccessor_00408640::LengthSq() const {
    return y * y + x * x;
}
#pragma code_seg()
