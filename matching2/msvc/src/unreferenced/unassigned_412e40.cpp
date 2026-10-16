struct Vec23 {
    float x;
    float y;
    __declspec(noinline) void ScaleBy(float scale, Vec23* out) const;
};
#pragma code_seg(".text$01accessor")
void Vec23::ScaleBy(float scale, Vec23* out) const {
    float sx = scale * x;
    float sy = scale * y;
    out->x = sx;
    out->y = sy;
}
#pragma code_seg()
