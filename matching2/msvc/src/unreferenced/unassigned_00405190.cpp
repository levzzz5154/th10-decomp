// 0x00405190: set the X scale and mark the transform dirty.
// The object arrives in EAX and the float on the stack (RET 4); the body is
// compiled in the native-LTCG cluster build_support/layout/ltcg/setscalex.json.
struct AnmVm_00405190 {
    unsigned char reserved_000[0x3C];
    float scale_x;                 // +0x3C
    unsigned char reserved_040[0x35C - 0x40];
    unsigned int flags;                 // +0x35C
    __declspec(noinline) void SetScaleX(float value);
};

#pragma code_seg(".text$01accessor")
void AnmVm_00405190::SetScaleX(float value) {
    scale_x = value;
    flags |= 8;
}
#pragma code_seg()
