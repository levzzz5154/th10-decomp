// Compiler context only; never recovered game code.
#include "../../src/game/bullet/fun_00407780_00407780.cpp"
#include "th10/platform/sound_queue.hpp"
#pragma code_seg(".text$07context")
int __stdcall SoundQueueMotionContext(BulletDeceleration** bullets, int count) {
    for (int i = 0; i < count; ++i) {
        bullets[i]->TurnStep();
        bullets[i]->AimStep();
        bullets[i]->Bounce();
        data_00492590.QueuePan(i, bullets[i]->position_x);
    }
    return count;
}
#pragma code_seg()
