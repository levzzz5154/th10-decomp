// 0x00427E20: assign a two-float vector and return a copy of it.
struct Vec2_00427e20 {
    float x, y;
    Vec2_00427e20() {}
    Vec2_00427e20 Assign(const Vec2_00427e20& source);
};

#pragma code_seg(".text$01accessor")
__declspec(noinline) Vec2_00427e20 Vec2_00427e20::Assign(const Vec2_00427e20& source) {
    x = source.x;
    y = source.y;
    return *this;
}
#pragma code_seg()
