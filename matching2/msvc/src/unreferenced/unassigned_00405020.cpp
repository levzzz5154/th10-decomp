// 0x00405020: copy the argument vector into the +0x18 field.
//
// The receiver arrives in ECX and the source pointer in EAX, and the field
// offset is added as an integer, so the body is compiled as a single-function
// native-LTCG cluster.
struct Vec3_00405020 {
    float x;                              // +0x0
    float y;                              // +0x4
    float z;                              // +0x8
};

struct ObjectAccessor_00405020 {
    unsigned char pad_000[0x18];
    Vec3_00405020 field;                          // +0x18
    __declspec(noinline) void CopyFrom(const Vec3_00405020* src);
};

#pragma code_seg(".text$01accessor")
void ObjectAccessor_00405020::CopyFrom(const Vec3_00405020* src) {
    Vec3_00405020* dst = (Vec3_00405020*)((int)this + 0x18);
    *dst = *src;
}
#pragma code_seg()
