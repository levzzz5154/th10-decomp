// 0x00427E20: assign a two-float vector and return a copy of it.
struct Vec25 {
    float x, y;
    Vec25() {}
    Vec25 Assign(const Vec25& source);
};

#pragma code_seg(".text$01accessor")
__declspec(noinline) Vec25 Vec25::Assign(const Vec25& source) {
    x = source.x;
    y = source.y;
    return *this;
}
#pragma code_seg()
