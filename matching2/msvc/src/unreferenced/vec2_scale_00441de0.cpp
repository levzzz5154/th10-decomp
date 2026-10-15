// 0x00441DE0: a vector scaled by a factor.
struct Vec2_00441dd0 {
    float x, y;
    Vec2_00441dd0(float x_value, float y_value) : x(x_value), y(y_value) {}
};

#pragma code_seg(".text$01accessor")
__declspec(noinline) Vec2_00441dd0 __stdcall Scaled_00441de0(const Vec2_00441dd0* v, float factor) {
    return Vec2_00441dd0(v->x * factor, v->y * factor);
}
#pragma code_seg()
