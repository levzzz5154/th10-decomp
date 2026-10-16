// Compiler context only; never selected as recovered game code.
#include "../../../src/game/enemy/bullet_entity_mark_animation_for_removal.cpp"

#pragma code_seg(".text$03context")
int __stdcall BulletEntityMarkAnimationForRemovalCompilerContext(
        SprtCtrl* manager, BulletEntity4* entity) {
    entity->MarkAnimationForRemoval(manager);
    return 0;
}
#pragma code_seg()
