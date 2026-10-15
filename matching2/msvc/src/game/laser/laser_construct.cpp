// 0x0041C030..0x0041C091 (98 bytes): Laser_Construct
//
// Clears every per-record flag word, wipes the object and then sets up the
// score timer.  The object arrives in EDX; the first __fastcall argument is the
// unused ECX slot, so the whole-program pass drops that dead argument at every
// call site (retail's callers only set up EDX).  That is why this unit lives in
// the same native-LTCG link as the factory that calls it (see
// layout/ltcg/bullet_manager_load_scripts_0040ae70.json).
#include "th10/math/timer.hpp"

extern "C" unsigned char data_0046dab0;
extern "C" unsigned char data_00476f78;
extern "C" void *__cdecl memset(void *destination, int value, unsigned int size);

struct ScoreRecord {
    unsigned int flags;              // +0x00
    unsigned char unknown_04[0x30];
};
typedef char ScoreRecord_size_must_be_52[sizeof(ScoreRecord) == 0x34 ? 1 : -1];

struct LaserBaseView {
    void *vtable;                    // +0x000
    unsigned char unknown_004[0x0C];
    FrameTimer timer;                // +0x010
    unsigned char unknown_024[0x44];
    ScoreRecord records[18];         // +0x068
    FrameTimer tail_timer;           // +0x410
};
typedef char LaserBaseView_size_must_be_1060[sizeof(LaserBaseView) == 0x424 ? 1 : -1];

#pragma code_seg(".text$00fascoreobjinit")
__declspec(noinline) LaserBaseView *__fastcall
Laser_Construct(void *, LaserBaseView *self) {
    self->vtable = &data_0046dab0;
    // The clear goes through a typed pointer: the plain member form makes MSVC
    // schedule the read-modify-write ahead of the vtable store, which no longer
    // matches the retail bytes.
    FrameTimer *timer = &self->timer;
    timer->flags &= ~1u;
    for (int index = 0; index < 18; ++index)
        self->records[index].flags &= ~1u;
    self->tail_timer.flags &= ~1u;
    memset(self, 0, sizeof(LaserBaseView));
    unsigned int flags = self->timer.flags;
    if ((flags & 1) == 0) {
        self->timer.current = 0;
        self->timer.previous = -999999;
        self->timer.elapsed = 0.0f;
        self->timer.speed = (const float *)&data_00476f78;
        self->timer.flags = flags | 1u;
    }
    self->timer.current = 0;
    self->timer.elapsed = 0.0f;
    self->timer.previous = -1;
    return self;
}
#pragma code_seg()
