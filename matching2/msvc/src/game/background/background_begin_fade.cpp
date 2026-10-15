#include "th10/game/background_fade.hpp"
#include "th10/render/screen_effect_controller.hpp"
extern "C" float data_00476f78;
extern "C" void _ReadWriteBarrier();
#pragma intrinsic(_ReadWriteBarrier)
#pragma code_seg(".text$00bFade")
void BackGround::BeginFade() {
    CreateScreenEffect_0043c8b0(15, 2, 30, 0, 0, 0);
    if (!(timer.flags & 1u)) {
        timer.current = 0;
        timer.previous = -999999;
        timer.elapsed = 0;
        timer.speed = &data_00476f78;
        timer.flags |= 1u;
    }
    timer.current = 30;
    timer.elapsed = 30.0f;
    timer.previous = 29;
    // Preserve the original order: finish the timer stores before touching
    // the adjacent owner flags word. This intrinsic emits no instructions.
    _ReadWriteBarrier();
    flags |= 2u;
}
#pragma code_seg()
