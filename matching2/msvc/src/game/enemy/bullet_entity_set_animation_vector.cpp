// 0x0040CF60..0x0040CF76: copy an animation vector into a bullet.

struct AnimationVector {
    float x;
    float y;
    float z;
};

struct BulletEntity5 {
    unsigned char unknown_000[0x430];
    AnimationVector animation_vector;

    __declspec(noinline) void SetAnimationVector(
        const AnimationVector& value);
};

#pragma code_seg(".text$01setanimation")
void BulletEntity5::SetAnimationVector(
    const AnimationVector& value) {
    animation_vector = value;
}
#pragma code_seg()
