// 0x00405110: copy the argument vector into the +0xC field.
//
// The receiver arrives in ECX and the source pointer in EAX, and the field
// offset is added as an integer, so the body is compiled as a single-function
// native-LTCG cluster.
struct Vec3_00405110 {
    float x;                              // +0x0
    float y;                              // +0x4
    float z;                              // +0x8
};

struct ObjectAccessor_00405110 {
    unsigned char pad_000[0xC];
    Vec3_00405110 field;                          // +0xC
    __declspec(noinline) void CopyFrom(const Vec3_00405110* src);
};

#pragma code_seg(".text$01accessor")
void ObjectAccessor_00405110::CopyFrom(const Vec3_00405110* src) {
    Vec3_00405110* dst = (Vec3_00405110*)((int)this + 0xC);
    *dst = *src;
}
#pragma code_seg()
