struct Vec27 {
    float x;
    float y;
    __declspec(noinline) void AddTo(const Vec27* b, Vec27* out) const;
};
#pragma code_seg(".text$01accessor")
void Vec27::AddTo(const Vec27* b, Vec27* out) const {
    float sx = x + b->x;
    float sy = y + b->y;
    out->x = sx;
    out->y = sy;
}
#pragma code_seg()
