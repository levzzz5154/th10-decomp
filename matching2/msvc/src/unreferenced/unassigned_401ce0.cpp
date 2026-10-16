// 0x00401CE0: set the sprite size and mark the transform dirty.
// The object arrives in EAX and both floats on the stack (RET 8): native LTCG
// never gives a float argument an integer register. Nothing in retail calls it.
struct AnmVm2 {
    unsigned char reserved_000[0x4C];
    float sprite_width;            // +0x4C
    float sprite_height;           // +0x50
    unsigned char reserved_054[0x35C - 0x54];
    unsigned int flags;                 // +0x35C
    __declspec(noinline) void SetSpriteSize(float sprite_width_value, float sprite_height_value);
};

#pragma code_seg(".text$01accessor")
void AnmVm2::SetSpriteSize(float sprite_width_value, float sprite_height_value) {
    sprite_width = sprite_width_value;
    sprite_height = sprite_height_value;
    flags |= 8;
}
#pragma code_seg()
