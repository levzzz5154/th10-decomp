// 0x004187F0: move a playfield position into screen space (the playfield's
// origin is at (224, 16) on screen); z is copied unchanged.
struct Vec3_004187f0 {
    float x, y, z;
};

#pragma code_seg(".text$01accessor")
__declspec(noinline) void __stdcall PlayfieldToScreen_004187f0(const Vec3_004187f0* playfield, Vec3_004187f0* screen) {
    screen->x = playfield->x + 224.0f;
    screen->y = playfield->y + 16.0f;
    screen->z = playfield->z;
}
#pragma code_seg()
