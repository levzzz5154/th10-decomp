// 0x0040CF60..0x0040CF76: copy an animation vector into an enemy.

struct AnimationVector {
    float x;
    float y;
    float z;
};

struct LaserVectorView {
    unsigned char unknown_000[0x430];
    AnimationVector animation_vector;

    __declspec(noinline) void SetVector(
        const AnimationVector& value);
};

#pragma code_seg(".text$01setanimation")
void LaserVectorView::SetVector(
    const AnimationVector& value) {
    animation_vector = value;
}
#pragma code_seg()
