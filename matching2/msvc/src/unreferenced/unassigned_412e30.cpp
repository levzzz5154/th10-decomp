struct Vec22 {
    float x;
    float y;
    __declspec(noinline) void SubtractTo(const Vec22* b, Vec22* out) const;
};
#pragma code_seg(".text$01accessor")
void Vec22::SubtractTo(const Vec22* b, Vec22* out) const {
    float dx = x - b->x;
    float dy = y - b->y;
    out->x = dx;
    out->y = dy;
}
#pragma code_seg()
