// 0x004087A0: set the Z rotation and mark the rotation dirty.
// The object arrives in EAX and the float on the stack (RET 4); the body is
// compiled in the native-LTCG cluster build_support/layout/ltcg/setrotationz.json.
struct AnmVm6 {
    unsigned char reserved_000[0x2C];
    float rotation_z;              // +0x2C
    unsigned char reserved_030[0x35C - 0x30];
    unsigned int flags;                 // +0x35C
    __declspec(noinline) void SetRotationZ(float value);
};

#pragma code_seg(".text$01accessor")
void AnmVm6::SetRotationZ(float value) {
    rotation_z = value;
    flags |= 4;
}
#pragma code_seg()
