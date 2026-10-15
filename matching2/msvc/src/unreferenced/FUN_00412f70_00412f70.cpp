// 0x00412F70: store a two-float vector.
// The object arrives in EAX and both floats on the stack (RET 8); the body is
// compiled in the native-LTCG cluster build_support/layout/ltcg/set_00412f70.json.
struct Float2_00412f70 {
    float x;                       // +0x0
    float y;                       // +0x4
    __declspec(noinline) void Set(float x_value, float y_value);
};

#pragma code_seg(".text$01accessor")
void Float2_00412f70::Set(float x_value, float y_value) {
    x = x_value;
    y = y_value;
}
#pragma code_seg()
