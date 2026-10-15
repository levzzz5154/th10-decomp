// 0x0041D170: LineLaser::Motion0040 (vtable 0x0046DA60 slot 0x30): repeated
// turn/speed steps with linear deceleration between them.
#include "th10/platform/sound_queue.hpp"
extern "C" float data_00470b68, data_00470b64, data_00476f78;
struct DecelerationVector2 {
    float x, y;
    void SetPolar(float angle, float speed);
};
struct LineLaser {
    char reserved_000[0x30];
    DecelerationVector2 velocity;
    float reserved_038;
    float angle;
    float base_speed;
    float reserved_044;
    // Preserve the speed store before examining the timer initialization flag.
    volatile float speed;
    char reserved_04c[0xF4 - 0x4C];
    int previous;
    int current;
    float elapsed;
    // Retain the time-scale load before adding the elapsed time.
    volatile float* time_scale;
    volatile unsigned int timer_flags;
    float next_speed;
    float angle_step;
    char reserved_110[12];
    int duration;
    int limit;
    int iteration;
    char reserved_128[0x404 - 0x128];
    unsigned int flags;
    int reserved_408;
    int sound_id;
    __declspec(noinline) void Motion0040();
};
#pragma code_seg(".text$03deceleration")
void LineLaser::Motion0040() {
    int length = duration;
    float magnitude;
    if (current >= length) {
        if (sound_id >= 0)
            data_00492590.Queue(sound_id, 0);
        if (++iteration >= limit)
            flags &= ~0x40u;
        angle = angle_step + angle;
        magnitude = speed = next_speed;
        unsigned int initial_flags = timer_flags;
        if (!(initial_flags & 1)) {
            current = 0;
            previous = -999999;
            elapsed = 0;
            time_scale = &data_00476f78;
            timer_flags = initial_flags | 1;
        }
        current = 0;
        elapsed = 0;
        previous = -1;
    } else {
        float initial_speed = speed;
        magnitude = initial_speed - initial_speed * elapsed / length;
    }
    velocity.SetPolar(angle, magnitude);
    previous = current;
    if (*time_scale > data_00470b68 && *time_scale < data_00470b64) {
        ++current;
        elapsed += 1.0f;
    } else {
        float step = *time_scale;
        current = int(elapsed = step + elapsed);
    }
}
#pragma code_seg()
