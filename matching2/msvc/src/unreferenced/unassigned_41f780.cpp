// 0x0041F780..0x0041F79E: scale a three-component vector into a destination.
struct Vector39 {
    float x;
    float y;
    float z;

    __declspec(noinline) void ScaleBy(float scale, Vector39* out) const;
};

#pragma code_seg(".text$01scale")
void Vector39::ScaleBy(float scale, Vector39* out) const {
    float sz = scale * z;
    float sy = scale * y;
    float sx = scale * x;
    out->x = sx;
    out->y = sy;
    out->z = sz;
}
#pragma code_seg()
