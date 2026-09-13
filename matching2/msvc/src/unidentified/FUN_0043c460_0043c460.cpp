#include "th10/math/timer.hpp"

extern "C" int data_004918a4;  // 0x004918A4

// Animation cursor update at 0x0043C460.  The record embeds the scheduler and
// the FrameTimer at +0x30; native LTCG supplies the retail EAX receiver for
// the scheduler store and the ESI receiver for the embedded timer, exactly as
// for the 0x0043C230 cursor.
struct PlayerSchedulerRecord {
    int field_00;    // +0x00, stored one below the raw value
    int field_04;    // +0x04
    float field_08;  // +0x08, value converted to float
    int field_0C;    // +0x0C, default marker
    int flags_10;    // +0x10, initialised flag

    __declspec(noinline) void SetSchedulerValue(int value);
};

struct AnimationCursor_0043c460 {
    unsigned char pad_00[0x18];
    int value;                 // +0x18
    int length;                // +0x1C
    int countdown;             // +0x20
    unsigned char pad_24[0xC];
    int previous;              // +0x30, embedded FrameTimer::previous
    int frame;                 // +0x34, embedded FrameTimer::current
    float elapsed;             // +0x38, embedded FrameTimer::elapsed
    const float* delta;        // +0x3C, embedded FrameTimer::speed

    __declspec(noinline) int Tick();
};

typedef char AnimationCursor_0043c460_size_must_fit[
    sizeof(AnimationCursor_0043c460) == 0x40 ? 1 : -1];

#pragma code_seg(".text$11c460")
int AnimationCursor_0043c460::Tick() {
    int mode = *(unsigned char*)((unsigned char*)this + 0x27);
    if (data_004918a4 != 0)
        return 0;

    int divisor = length;
    if (frame < divisor) {
        unsigned int amount = (unsigned int)mode;
        int scaled = int(float(amount) * elapsed / divisor);
        value = mode - scaled;
        if (value < 0)
            value = 0;
    } else {
        value = 0;
        if (--countdown <= 0)
            return 0;
        reinterpret_cast<PlayerSchedulerRecord*>(reinterpret_cast<unsigned char*>(this) + 0x30)
            ->SetSchedulerValue(0);
    }

    reinterpret_cast<FrameTimer*>(reinterpret_cast<unsigned char*>(this) + 0x30)->Tick();
    return 1;
}
#pragma code_seg()
