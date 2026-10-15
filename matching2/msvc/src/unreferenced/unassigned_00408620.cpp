// 0x00408620: squared distance between the receiver and the argument vector.
//
// The receiver arrives in EAX and the argument in ECX - a register pair no
// C++ declaration names - so the body is compiled as a single-function
// native-LTCG cluster.
struct Vec3_00408620 {
    float x;                              // +0x0
    float y;                              // +0x4
    float z;                              // +0x8
};

struct ObjectAccessor_00408620 {
    float x;                              // +0x0
    float y;                              // +0x4
    float z;                              // +0x8
    __declspec(noinline) float DistSq(const Vec3_00408620* other) const;
};

#pragma code_seg(".text$01accessor")
float ObjectAccessor_00408620::DistSq(const Vec3_00408620* other) const {
    float dy = y - other->y;
    float dx = x - other->x;
    return dx * dx + dy * dy;
}
#pragma code_seg()
