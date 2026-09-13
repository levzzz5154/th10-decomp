#ifndef TH10_BULLET_DECELERATION_HPP
#define TH10_BULLET_DECELERATION_HPP
struct BulletDecelerationVector2 {
    float x, y;
    void SetPolar(float angle, float speed);
};
// Motion fields used by the recovered ESI-entry bullet callbacks.
// Volatile speed/timer accesses preserve their observed x87 and reset ordering.
struct BulletDeceleration {
    char reserved_000[0x3B4];
    float position_x, position_y, position_z;
    BulletDecelerationVector2 velocity;
    char reserved_3c8[0x3D8 - 0x3C8];
    volatile float speed;
    char reserved_3dc[8];
    float angle;
    char reserved_3e8[0x43C - 0x3E8];
    unsigned int flags;
    char reserved_440[0x458 - 0x440];
    int sound_id;
    char reserved_45c[0x6B0 - 0x45C];
    int previous;
    int current;
    float elapsed;
    volatile float* time_scale;
    volatile unsigned int timer_flags;
    float next_speed;
    float angle_step;
    char reserved_6cc[12];
    int duration;
    int limit;
    int iteration;
    char reserved_6e4[0x14];
    float rebound_speed;
    char reserved_6fc[0x10];
    int bounce_count;
    int bounce_limit;
    __declspec(noinline) void TurnStep();
    __declspec(noinline) void AimStep();
    __declspec(noinline) void Bounce();
};
#endif
