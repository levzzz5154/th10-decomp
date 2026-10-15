// 0x0040CEE0: copy the argument vector into the +0x24 field.
//
// The receiver arrives in ECX and the source pointer in EAX, and the field
// offset is added as an integer, so the body is compiled as a single-function
// native-LTCG cluster.
struct Vec3_0040cee0 {
    float x;                              // +0x0
    float y;                              // +0x4
    float z;                              // +0x8
};

struct ObjectAccessor_0040cee0 {
    unsigned char pad_000[0x24];
    Vec3_0040cee0 field;                          // +0x24
    __declspec(noinline) void CopyFrom(const Vec3_0040cee0* src);
};

#pragma code_seg(".text$01accessor")
void ObjectAccessor_0040cee0::CopyFrom(const Vec3_0040cee0* src) {
    Vec3_0040cee0* dst = (Vec3_0040cee0*)((int)this + 0x24);
    *dst = *src;
}
#pragma code_seg()
