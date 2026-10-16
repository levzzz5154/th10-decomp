// 0x00441DD0: the vector from one point to another.
struct Vec26 {
    float x, y;
    Vec26(float x_value, float y_value) : x(x_value), y(y_value) {}
};

#pragma code_seg(".text$01accessor")
__declspec(noinline) Vec26 __stdcall Difference(const Vec26* to, const Vec26* from) {
    return Vec26(to->x - from->x, to->y - from->y);
}
#pragma code_seg()
