// 0x00412E60..0x00412E6F: add two Vec2 values into an output record.
// Native LTCG caller context supplies the private EDX/EAX argument convention.
struct Vec2_00412e60 {
    float x;
    float y;
    __declspec(noinline) void AddTo(const Vec2_00412e60* b,
                                     Vec2_00412e60* out) const;
};

#pragma code_seg(".text$01accessor")
void Vec2_00412e60::AddTo(const Vec2_00412e60* b,
                          Vec2_00412e60* out) const {
    float dx = x + b->x;
    float dy = y + b->y;
    out->x = dx;
    out->y = dy;
}
#pragma code_seg()
