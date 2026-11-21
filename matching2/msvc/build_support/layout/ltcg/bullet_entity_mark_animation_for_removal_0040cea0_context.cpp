// Compiler context only; never selected as recovered game code.
#include "../../../src/game/enemy/card_stop_animation.cpp"

#pragma code_seg(".text$03context")
int __stdcall BulletEntityMarkAnimationForRemovalCompilerContext(
        SprtCtrl* manager, CardStopAnimView* entity) {
    entity->StopAnimation(manager);
    return 0;
}
#pragma code_seg()
