struct Vec2_00441e00 {
    float x;
    float y;
    __declspec(noinline) void AddTo(const Vec2_00441e00* b, Vec2_00441e00* out) const;
};
#pragma code_seg(".text$01accessor")
void Vec2_00441e00::AddTo(const Vec2_00441e00* b, Vec2_00441e00* out) const {
    float sx = x + b->x;
    float sy = y + b->y;
    out->x = sx;
    out->y = sy;
}
#pragma code_seg()
