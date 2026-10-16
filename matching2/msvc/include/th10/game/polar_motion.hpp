#ifndef TH10_GAME_POLAR_MOTION_HPP
#define TH10_GAME_POLAR_MOTION_HPP

#include <math.h>

extern "C" float __stdcall Angle_Normalize2(float value);

struct PolarVec3 {
    float x;
    float y;
    float z;

    // 0x0044C5D0: x = cos(angle) * radius, y = sin(angle) * radius.
    PolarVec3* SetPolar(float angle, float radius);

    void SnapToHundredths() {
        x = (float)floor(x * 100.0f) * 0.01f;
        y = (float)floor(y * 100.0f) * 0.01f;
    }

    PolarVec3& operator+=(const PolarVec3& other) {
        x += other.x;
        y += other.y;
        z += other.z;
        return *this;
    }

    PolarVec3 operator+(const PolarVec3& other) const {
        PolarVec3 sum;
        sum.x = x + other.x;
        sum.y = y + other.y;
        sum.z = z + other.z;
        return sum;
    }
};

// A position driven either by a plain velocity or by a turning heading.
struct PolarMotion {
    PolarVec3 position;                  // +0x00
    PolarVec3 velocity;                  // +0x0C
    float speed;                         // +0x18: also the turn rate when orbiting
    float angle;                         // +0x1C
    float radius;                        // +0x20
    float radius_step;                   // +0x24
    unsigned char flags;                 // +0x28: bit 0 orbits around the velocity

    void Update();
    __declspec(noinline) void Advance();
    __declspec(noinline) void Step();
};

inline void PolarMotion::Update() {
    if ((flags & 1) == 0) {
        velocity.SetPolar(angle, speed);
        velocity.z = 0.0f;
    } else {
        radius += radius_step;
        angle = Angle_Normalize2(speed + angle);
    }
}

#endif
