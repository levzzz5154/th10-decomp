#include "th10/game/laser_spawn_0041c510.hpp"
extern "C" unsigned char data_0046dab0;
extern "C" unsigned char data_00476f78;
#pragma code_seg(".text$f0041c030F")
__declspec(noinline) LaserBase_0041c030 *__fastcall
LaserBase_Construct_0041c030(void *, LaserBase_0041c030 *self) {
    self->vtable = &data_0046dab0;
    // The clear goes through a typed pointer: the plain member form makes MSVC
    // schedule the read-modify-write ahead of the vtable store, which no longer
    // matches the retail bytes.
    FrameTimer *timer = &self->timer;
    timer->flags &= ~1u;
    for (int index = 0; index < 18; ++index)
        self->tracks[index].flags &= ~1u;
    self->tail_timer.flags &= ~1u;
    memset(self, 0, sizeof(LaserBase_0041c030));
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
