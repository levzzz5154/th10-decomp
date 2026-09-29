// 0x00441DD0: the vector from one point to another.
struct Vec2_00441dd0 {
    float x, y;
    Vec2_00441dd0(float x_value, float y_value) : x(x_value), y(y_value) {}
};

#pragma code_seg(".text$01accessor")
__declspec(noinline) Vec2_00441dd0 __stdcall Difference_00441dd0(const Vec2_00441dd0* to, const Vec2_00441dd0* from) {
    return Vec2_00441dd0(to->x - from->x, to->y - from->y);
}
#pragma code_seg()
