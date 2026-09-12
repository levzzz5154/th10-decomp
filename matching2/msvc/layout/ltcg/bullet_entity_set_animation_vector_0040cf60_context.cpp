// Compiler context only; never selected as recovered game code.
#include "../../src/game/bullet_entity_set_animation_vector_0040cf60.cpp"

#pragma code_seg(".text$03context")
int __stdcall BulletEntitySetAnimationVectorCompilerContext(
        BulletEntity_0040cf60** entities, int count,
        const AnimationVector_0040cf60* value) {
    while (count--) {
        (*entities++)->SetAnimationVector(*value);
    }
    return 0;
}
#pragma code_seg()
