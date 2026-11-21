// 0x0041D2C0: LaserExAccelerate::Update — laser Ex-transform acceleration step
// (flags +0x404 bit 4): accelerates velocity and auxiliary speed over duration
// frames, recomputing angle via atan2, then clears bit 4.
extern "C" float flt_1;
extern "C" float flt_1_01;
extern "C" float flt_0_99;
extern "C" float flt_0_0001;
extern "C" float g_game_speed;
extern "C" int __cdecl crt_ftol2();
#include <math.h>

extern "C" double __cdecl atan2(double, double);

struct LaserAccelVec3 {
    float x;
    float y;
    float z;

    LaserAccelVec3(float x_value, float y_value, float z_value)
        : x(x_value), y(y_value), z(z_value) {
    }

    LaserAccelVec3 operator*(float scale) const {
        return LaserAccelVec3(x * scale, y * scale, z * scale);
    }

    LaserAccelVec3& operator+=(const LaserAccelVec3& value) {
        x += value.x;
        y += value.y;
        z += value.z;
        return *this;
    }
};

struct LaserExAccelerate {
    unsigned char reserved_000[0x30];
    LaserAccelVec3 velocity;
    float angle;
    unsigned char reserved_040[8];
    float auxiliary;
    unsigned char reserved_04c[0x8c - 0x4c];
    int previous;
    int current;
    float elapsed;
    float* time_scale;
    unsigned int timer_flags;
    float auxiliary_acceleration;
    unsigned char reserved_0a4[4];
    LaserAccelVec3 acceleration;
    int duration;
    unsigned char reserved_0b8[0x404 - 0xb8];
    unsigned int flags;

    void Update();
};

#pragma code_seg(".text$04effect_accel")
void LaserExAccelerate::Update() {
    if (current >= duration) {
        flags &= ~0x10u;
    } else {
        auxiliary += g_game_speed * auxiliary_acceleration;
        velocity += acceleration * g_game_speed;
        if (fabs(velocity.x) > flt_0_0001 ||
            fabs(velocity.y) > flt_0_0001)
            angle = (float)atan2((double)velocity.y, (double)velocity.x);
    }

    previous = current;
    if (*time_scale > flt_0_99 && *time_scale < flt_1_01) {
        float next_elapsed = *(volatile float*)&elapsed + flt_1;
        ++current;
        elapsed = next_elapsed;
    } else {
        current = int(elapsed = *time_scale + elapsed);
    }
}
#pragma code_seg()
