// 0x00408730: subtract the argument vector componentwise.
//
// The destination vector arrives in EAX and the source vector in ECX - a
// register pair no C++ declaration names - so the body is compiled as a
// single-function native-LTCG cluster.
struct Vec313 {
    float x;                              // +0x0
    float y;                              // +0x4
    float z;                              // +0x8
};

struct ObjectAccessor_00408730 {
    float x;                              // +0x0
    float y;                              // +0x4
    float z;                              // +0x8
    __declspec(noinline) void Apply(const Vec313* other);
};

#pragma code_seg(".text$01accessor")
void ObjectAccessor_00408730::Apply(const Vec313* other) {
    x = x - other->x;
    y = y - other->y;
    z = z - other->z;
}
#pragma code_seg()
