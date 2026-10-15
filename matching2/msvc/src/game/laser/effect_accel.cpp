extern "C" float data_00470afc;
extern "C" float data_00470b64;
extern "C" float data_00470b68;
extern "C" float data_00470c58;
extern "C" float g_game_speed;
extern "C" int __cdecl asm_FUN_00463b2c_00463b2c();
#include <math.h>

extern "C" double __cdecl atan2(double, double);

struct EffectVector3_0041d2c0 {
    float x;
    float y;
    float z;

    EffectVector3_0041d2c0(float x_value, float y_value, float z_value)
        : x(x_value), y(y_value), z(z_value) {
    }

    EffectVector3_0041d2c0 operator*(float scale) const {
        return EffectVector3_0041d2c0(x * scale, y * scale, z * scale);
    }

    EffectVector3_0041d2c0& operator+=(const EffectVector3_0041d2c0& value) {
        x += value.x;
        y += value.y;
        z += value.z;
        return *this;
    }
};

struct EffectAccel_0041d2c0 {
    unsigned char reserved_000[0x30];
    EffectVector3_0041d2c0 velocity;
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
    EffectVector3_0041d2c0 acceleration;
    int duration;
    unsigned char reserved_0b8[0x404 - 0xb8];
    unsigned int flags;

    void Update();
};

#pragma code_seg(".text$04effect_accel")
void EffectAccel_0041d2c0::Update() {
    if (current >= duration) {
        flags &= ~0x10u;
    } else {
        auxiliary += g_game_speed * auxiliary_acceleration;
        velocity += acceleration * g_game_speed;
        if (fabs(velocity.x) > data_00470c58 ||
            fabs(velocity.y) > data_00470c58)
            angle = (float)atan2((double)velocity.y, (double)velocity.x);
    }

    previous = current;
    if (*time_scale > data_00470b68 && *time_scale < data_00470b64) {
        float next_elapsed = *(volatile float*)&elapsed + data_00470afc;
        ++current;
        elapsed = next_elapsed;
    } else {
        current = int(elapsed = *time_scale + elapsed);
    }
}
#pragma code_seg()
