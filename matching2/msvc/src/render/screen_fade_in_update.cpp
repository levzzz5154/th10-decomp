#include "th10/math/timer.hpp"

extern "C" int data_004918a4;  // 0x004918A4
extern "C" float data_00470bf8;  // 0x00470BF8

// 0x0043BD40: the fade-in update task (ScreenEffectController modes 0 and 3):
// the alpha falls from 255 to 0 over the length. The object embeds a FrameTimer at
// +0x30; native LTCG supplies the retail internal ESI receiver for that call.
struct ScreenFadeIn {
    unsigned char pad_00[0x18];
    int value;                   // +0x18
    int length;                  // +0x1C
    unsigned char pad_20[0x10];
    int previous;                // +0x30, owned by the embedded timer
    int frame;                   // +0x34
    volatile float elapsed;      // +0x38; preserves retail x87 load order
    const float* delta;          // +0x3C

    __declspec(noinline) int Tick();
};

typedef char AnimationCursor_0043bd40_size_must_be_40[
    sizeof(ScreenFadeIn) == 0x40 ? 1 : -1];

#pragma code_seg(".text$07bd40")
int ScreenFadeIn::Tick() {
    if (data_004918a4 != 0)
        return 7;

    int divisor = length;
    if (divisor != 0) {
        int next = int(data_00470bf8 - elapsed * data_00470bf8 / divisor);
        value = next;
        if (next < 0)
            value = 0;
    }

    if (frame >= divisor)
        return 7;

    reinterpret_cast<FrameTimer*>(reinterpret_cast<unsigned char*>(this) + 0x30)->Tick();
    return 1;
}
#pragma code_seg()
