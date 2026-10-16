// 0x004087E0: add the argument vector componentwise.
//
// The destination vector arrives in EAX and the source vector in ECX - a
// register pair no C++ declaration names - so the body is compiled as a
// single-function native-LTCG cluster.
struct Vec314 {
    float x;                              // +0x0
    float y;                              // +0x4
    float z;                              // +0x8
};

struct ObjectAccessor_004087e0 {
    float x;                              // +0x0
    float y;                              // +0x4
    float z;                              // +0x8
    __declspec(noinline) void Apply(const Vec314* other);
};

#pragma code_seg(".text$01accessor")
void ObjectAccessor_004087e0::Apply(const Vec314* other) {
    x = x + other->x;
    y = y + other->y;
    z = z + other->z;
}
#pragma code_seg()
