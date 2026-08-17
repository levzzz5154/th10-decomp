#include "th10/game/weather_pool.hpp"


// 0x0042B6F0 - Advance every live droplet in the weather pool (retail walks
// 0x2D3 slots with a 0x40-byte stride). Each live slot sinks by
// gravity * gravity_scale, latches the previous frame value, then advances
// its frame counter: while the shared control word stays inside
// (span_low, span_high) the counter increments by one and the timer gains one
// frame step; otherwise the timer absorbs the control value and the counter
// is retruncated from the timer (retail _ftol). Slots past frame 0x3C retire.
int EffectPool_UpdateDrops(RainDrop* drops, int count, float gravity,
                           float gravity_scale, float span_low,
                           float span_high, float frame_step,
                           long long (*float_to_long)(float value)) {
    for (int index = 0; index < count; ++index) {
        RainDrop* drop = drops + index;
        if (drop->active == 0) continue;
        drop->position = drop->position - gravity * gravity_scale;
        drop->previous_frame = drop->frame;
        float control = *drop->control;
        if (control <= span_low || span_high <= control) {
            drop->timer = drop->timer + control;
            drop->frame = (float)float_to_long(drop->timer);
        } else {
            drop->frame = (float)((int)drop->frame + 1);
            drop->timer = drop->timer + frame_step;
        }
        if (0x3C < (int)drop->frame) drop->active = 0;
    }
    return 1;
}
