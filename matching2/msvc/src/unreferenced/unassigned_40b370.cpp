// 0x0040B370: copy the argument vector into the +0x340 field.
//
// The receiver arrives in ECX and the source pointer in EAX, and the field
// offset is added as an integer, so the body is compiled as a single-function
// native-LTCG cluster.
struct Vec316 {
    float x;                              // +0x0
    float y;                              // +0x4
    float z;                              // +0x8
};

struct ObjectAccessor_0040b370 {
    unsigned char pad_000[0x340];
    Vec316 field;                          // +0x340
    __declspec(noinline) void CopyFrom(const Vec316* src);
};

#pragma code_seg(".text$01accessor")
void ObjectAccessor_0040b370::CopyFrom(const Vec316* src) {
    Vec316* dst = (Vec316*)((int)this + 0x340);
    *dst = *src;
}
#pragma code_seg()
