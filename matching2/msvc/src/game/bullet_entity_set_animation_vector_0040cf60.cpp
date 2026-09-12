// 0x0040CF60..0x0040CF76: copy an animation vector into a bullet.

struct AnimationVector_0040cf60 {
    float x;
    float y;
    float z;
};

struct BulletEntity_0040cf60 {
    unsigned char unknown_000[0x430];
    AnimationVector_0040cf60 animation_vector;

    __declspec(noinline) void SetAnimationVector(
        const AnimationVector_0040cf60& value);
};

#pragma code_seg(".text$01setanimation")
void BulletEntity_0040cf60::SetAnimationVector(
    const AnimationVector_0040cf60& value) {
    animation_vector = value;
}
#pragma code_seg()
