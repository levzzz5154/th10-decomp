// 0x004051F0: a vector divided by a scalar, through its reciprocal.
struct Vec3_004051f0 {
    float x, y, z;
    Vec3_004051f0(float x_value, float y_value, float z_value) : x(x_value), y(y_value), z(z_value) {}
};

#pragma code_seg(".text$01accessor")
__declspec(noinline) Vec3_004051f0 __stdcall Divided(const Vec3_004051f0* v, float divisor) {
    divisor = 1.0f / divisor;
    return Vec3_004051f0(v->x * divisor, v->y * divisor, v->z * divisor);
}
#pragma code_seg()
