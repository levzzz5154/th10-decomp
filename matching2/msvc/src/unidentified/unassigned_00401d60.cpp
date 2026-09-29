// 0x00401D60: set both scales and mark the transform dirty.
// The object arrives in EAX and both floats on the stack (RET 8): native LTCG
// never gives a float argument an integer register. Nothing in retail calls it.
struct AnmVm_00401d60 {
    unsigned char reserved_000[0x3C];
    float scale_x;                 // +0x3C
    float scale_y;                 // +0x40
    unsigned char reserved_044[0x35C - 0x44];
    unsigned int flags;                 // +0x35C
    __declspec(noinline) void SetScale(float scale_x_value, float scale_y_value);
};

#pragma code_seg(".text$01accessor")
void AnmVm_00401d60::SetScale(float scale_x_value, float scale_y_value) {
    scale_x = scale_x_value;
    scale_y = scale_y_value;
    flags |= 8;
}
#pragma code_seg()
