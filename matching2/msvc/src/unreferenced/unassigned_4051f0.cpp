// 0x004051F0: a vector divided by a scalar, through its reciprocal.
struct Vec38 {
    float x, y, z;
    Vec38(float x_value, float y_value, float z_value) : x(x_value), y(y_value), z(z_value) {}
};

#pragma code_seg(".text$01accessor")
__declspec(noinline) Vec38 __stdcall Divided(const Vec38* v, float divisor) {
    divisor = 1.0f / divisor;
    return Vec38(v->x * divisor, v->y * divisor, v->z * divisor);
}
#pragma code_seg()
