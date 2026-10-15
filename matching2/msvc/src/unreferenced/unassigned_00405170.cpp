// 0x00405170: set the Y scale and mark the transform dirty.
// The object arrives in EAX and the float on the stack (RET 4); the body is
// compiled in the native-LTCG cluster build_support/layout/ltcg/setscaley.json.
struct AnmVm_00405170 {
    unsigned char reserved_000[0x40];
    float scale_y;                 // +0x40
    unsigned char reserved_044[0x35C - 0x44];
    unsigned int flags;                 // +0x35C
    __declspec(noinline) void SetScaleY(float value);
};

#pragma code_seg(".text$01accessor")
void AnmVm_00405170::SetScaleY(float value) {
    scale_y = value;
    flags |= 8;
}
#pragma code_seg()
