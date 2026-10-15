struct Vec2_00412e40 {
    float x;
    float y;
    __declspec(noinline) void ScaleBy(float scale, Vec2_00412e40* out) const;
};
#pragma code_seg(".text$01accessor")
void Vec2_00412e40::ScaleBy(float scale, Vec2_00412e40* out) const {
    float sx = scale * x;
    float sy = scale * y;
    out->x = sx;
    out->y = sy;
}
#pragma code_seg()
