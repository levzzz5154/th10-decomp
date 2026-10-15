// 0x00428B10: steer a homing shot towards its target.
//
// Without a target the shot just accelerates. With one it turns a fifth of
// the way towards it each frame; for the first two seconds it brakes while the
// target is more than 45 degrees off course and accelerates once it is within
// 15 degrees. A target that has left play is dropped.
//
// It is reached through a table of update callbacks: the shot arrives in EDX
// and ECX is not used.
#include <math.h>

float __stdcall Angle_Normalize(float angle);
double __stdcall AngleDifference(float first, float second);

struct HomingTarget_00428b10 {
    unsigned char pad_0000[0x1068];
    float x;                             // +0x1068
    float y;                             // +0x106C
    unsigned char pad_1070[0x2480 - 0x1070];
    unsigned int flags;                  // +0x2480
};

struct HomingShot_00428b10 {
    int unknown_00;
    int frames;                          // +0x04
    unsigned char pad_08[0x14 - 0x08];
    float x;                             // +0x14
    float y;                             // +0x18
    unsigned char pad_1C[0x2C - 0x1C];
    float speed;                         // +0x2C
    float angle;                         // +0x30
    unsigned char pad_34[0x40 - 0x34];
    int state;                           // +0x40
    unsigned char pad_44[0x4C - 0x44];
    HomingTarget_00428b10* target;       // +0x4C
};

int __fastcall HomingShot_Update_00428b10(void* unused, HomingShot_00428b10* shot);

#pragma code_seg(".text$01homing")
int __fastcall HomingShot_Update_00428b10(void* unused, HomingShot_00428b10* shot) {
    if (shot->state == 2)
        return 0;
    HomingTarget_00428b10* target = shot->target;
    if (target && ((target->flags & 0x11) || (target->flags & 0xC0000))) {
        shot->target = 0;
        target = 0;
    }
    if (target) {
        float turn = AngleDifference((float)atan2(target->y - shot->y, target->x - shot->x),
                                  shot->angle);
        float speed = shot->speed;
        if (shot->frames < 120) {
            if (fabs(turn) >= 0.7853982f) {
                speed -= 0.3f;
                if (speed < 4.0f)
                    speed = 4.0f;
            } else if (fabs(turn) < 0.2617994f) {
                speed += 0.1f;
                if (speed > 16.0f)
                    speed = 16.0f;
            }
            shot->angle = Angle_Normalize(turn * 0.2f + shot->angle);
            shot->speed = speed;
            return 0;
        }
        shot->speed = speed + 0.2f;
        return 0;
    }
    float speed = shot->speed + 0.1f;
    if (speed > 16.0f)
        speed = 16.0f;
    shot->speed = speed;
    return 0;
}
#pragma code_seg()
