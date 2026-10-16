// 0x00441DE0: a vector scaled by a factor.
struct Vec26 {
    float x, y;
    Vec26(float x_value, float y_value) : x(x_value), y(y_value) {}
};

#pragma code_seg(".text$01accessor")
__declspec(noinline) Vec26 __stdcall Scaled2(const Vec26* v, float factor) {
    return Vec26(v->x * factor, v->y * factor);
}
#pragma code_seg()
