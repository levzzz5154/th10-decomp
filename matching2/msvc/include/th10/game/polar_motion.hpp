#ifndef TH10_GAME_POLAR_MOTION_HPP
#define TH10_GAME_POLAR_MOTION_HPP

#include <math.h>

extern "C" float __stdcall Angle_Normalize_0044bc70(float value);
extern "C" float data_00470b44;  // 100.0f
extern "C" float data_00470b00;  // 0.01f

struct PolarVec3 {
    float x;
    float y;
    float z;

    // 0x0044C5D0: x = cos(angle) * radius, y = sin(angle) * radius.
    PolarVec3* SetPolar(float angle, float radius);

    void SnapToHundredths() {
        x = (float)floor(x * data_00470b44) * data_00470b00;
        y = (float)floor(y * data_00470b44) * data_00470b00;
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
        angle = Angle_Normalize_0044bc70(speed + angle);
    }
}

#endif
