// Compiler context only; never selected as recovered game code.
#include "../../../src/game/enemy/laser_set_vector.cpp"

#pragma code_seg(".text$03context")
int __stdcall BulletEntitySetAnimationVectorCompilerContext(
        LaserVectorView** entities, int count,
        const AnimationVector* value) {
    while (count--) {
        (*entities++)->SetVector(*value);
    }
    return 0;
}
#pragma code_seg()
