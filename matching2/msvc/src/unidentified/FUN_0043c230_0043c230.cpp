#include "th10/math/timer.hpp"

// 0x0043C230..0x0043C2B4: animation-cursor progress callback.
// The cursor owns a FrameTimer at +0x30.  Its retail caller supplies that
// timer in ESI; the native-LTCG frame_timer cluster selects the same private
// convention when both definitions are visible to one link.
extern "C" int data_004918a4;
extern "C" void* data_00477810;
extern "C" float data_00470bf8;

struct AnimationCursor_0043c230 {
    unsigned char pad_00[0x18];
    int value;
    int length;
    unsigned char pad_20[0x10];
    int previous;
    int frame;
    volatile float elapsed;
    const float* delta;

    __declspec(noinline) int Tick();
};

typedef char AnimationCursor_0043c230_size_must_fit[
    sizeof(AnimationCursor_0043c230) == 0x40 ? 1 : -1];

#pragma code_seg(".text$09c230")
int AnimationCursor_0043c230::Tick() {
    if (data_004918a4 != 0)
        return 7;

    int divisor = length;
    if (divisor != 0) {
        if (frame < divisor) {
            value = (int)(elapsed * data_00470bf8 / divisor);
        } else {
            value = 255;
        }
        if (value < 0)
            value = 0;
    }

    if (frame >= divisor + 2)
        return 7;

    void* state = data_00477810;
    if (state == 0 || (((*(unsigned int*)((char*)state + 0x58) >> 2) |
                        *(unsigned int*)((char*)state + 0x58)) & 1) == 0) {
        reinterpret_cast<FrameTimer*>(reinterpret_cast<unsigned char*>(this) +
                                      0x30)->Tick();
    }
    return 1;
}
#pragma code_seg()
