// 0x00405000: copy the argument vector into the +0x24 field.
//
// The receiver arrives in ECX and the source pointer in EAX, and the field
// offset is added as an integer, so the body is compiled as a single-function
// native-LTCG cluster.
struct Vec35 {
    float x;                              // +0x0
    float y;                              // +0x4
    float z;                              // +0x8
};

struct ObjectAccessor_00405000 {
    unsigned char pad_000[0x24];
    Vec35 field;                          // +0x24
    __declspec(noinline) void CopyFrom(const Vec35* src);
};

#pragma code_seg(".text$01accessor")
void ObjectAccessor_00405000::CopyFrom(const Vec35* src) {
    Vec35* dst = (Vec35*)((int)this + 0x24);
    *dst = *src;
}
#pragma code_seg()
