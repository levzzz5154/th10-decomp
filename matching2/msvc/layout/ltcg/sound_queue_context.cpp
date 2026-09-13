// Compiler context only; never recovered game code.
#include "../../src/game/fun_00407780_00407780.cpp"
#pragma code_seg(".text$07context")
int __stdcall SoundQueueMotionContext(BulletDeceleration** bullets, int count) {
    for (int i = 0; i < count; ++i) {
        bullets[i]->TurnStep();
        bullets[i]->AimStep();
        bullets[i]->Bounce();
    }
    return count;
}
#pragma code_seg()
