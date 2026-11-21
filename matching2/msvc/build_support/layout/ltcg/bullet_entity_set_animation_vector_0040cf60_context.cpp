// Compiler context only; never selected as recovered game code.
#include "../../../src/game/enemy/enemy_set_animation_vector.cpp"

#pragma code_seg(".text$03context")
int __stdcall BulletEntitySetAnimationVectorCompilerContext(
        EnemyAnimVectorView** entities, int count,
        const AnimationVector* value) {
    while (count--) {
        (*entities++)->SetAnimationVector(*value);
    }
    return 0;
}
#pragma code_seg()
