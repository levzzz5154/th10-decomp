// Compiler context only; never selected as recovered game code.
#include "../../../src/game/enemy/enemy_mark_animation_for_removal.cpp"

#pragma code_seg(".text$03context")
int __stdcall BulletEntityMarkAnimationForRemovalCompilerContext(
        SprtCtrl* manager, EnemyAnimRetireView* entity) {
    entity->MarkAnimationForRemoval(manager);
    return 0;
}
#pragma code_seg()
