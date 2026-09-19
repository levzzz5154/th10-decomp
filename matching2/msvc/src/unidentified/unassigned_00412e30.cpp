struct Vec2_00412e30 {
    float x;
    float y;
    __declspec(noinline) void SubtractTo(const Vec2_00412e30* b, Vec2_00412e30* out) const;
};
#pragma code_seg(".text$01accessor")
void Vec2_00412e30::SubtractTo(const Vec2_00412e30* b, Vec2_00412e30* out) const {
    float dx = x - b->x;
    float dy = y - b->y;
    out->x = dx;
    out->y = dy;
}
#pragma code_seg()
