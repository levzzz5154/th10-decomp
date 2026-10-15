// 0x0042BA70: set the sprite width and mark the transform dirty.
// The object arrives in EAX and the float on the stack (RET 4); the body is
// compiled in the native-LTCG cluster build_support/layout/ltcg/setspritewidth.json.
struct AnmVm_0042ba70 {
    unsigned char reserved_000[0x4C];
    float sprite_width;                // +0x4C
    unsigned char reserved_050[0x35C - 0x50];
    unsigned int flags;                 // +0x35C
    __declspec(noinline) void SetSpriteWidth(float value);
};

#pragma code_seg(".text$01accessor")
void AnmVm_0042ba70::SetSpriteWidth(float value) {
    sprite_width = value;
    flags |= 8;
}
#pragma code_seg()
