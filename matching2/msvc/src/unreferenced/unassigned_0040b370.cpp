// 0x0040B370: copy the argument vector into the +0x340 field.
//
// The receiver arrives in ECX and the source pointer in EAX, and the field
// offset is added as an integer, so the body is compiled as a single-function
// native-LTCG cluster.
struct Vec3_0040b370 {
    float x;                              // +0x0
    float y;                              // +0x4
    float z;                              // +0x8
};

struct ObjectAccessor_0040b370 {
    unsigned char pad_000[0x340];
    Vec3_0040b370 field;                          // +0x340
    __declspec(noinline) void CopyFrom(const Vec3_0040b370* src);
};

#pragma code_seg(".text$01accessor")
void ObjectAccessor_0040b370::CopyFrom(const Vec3_0040b370* src) {
    Vec3_0040b370* dst = (Vec3_0040b370*)((int)this + 0x340);
    *dst = *src;
}
#pragma code_seg()
