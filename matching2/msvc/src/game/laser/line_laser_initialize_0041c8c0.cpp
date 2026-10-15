// 0x0041C8C0: initialize a moving line laser from its complete spawn parameters.
// Starts and steps its beam and origin flare, resets the 30-frame startup timer,
// and copies the initial geometry and polar velocity. Virtual thiscall entry:
// laser in ECX, parameters on the stack, result 0, RET 4.
#include "th10/game/entity_script_start.hpp"
#include "th10/math/timer.hpp"

struct LineVelocity_0041c8c0 {
    float x, y, z;
    __declspec(noinline) LineVelocity_0041c8c0* SetPolar(float angle, float speed);
};

struct AnimationResourceFile;
void __stdcall Entity_StartScript(AnimationResourceFile* resource,
                                           Entity* entity, int script);
extern "C" int __stdcall asm_FUN_0043ee30_0043ee30(Entity* entity);

struct LaserAnimationBank_0041e5c0 {
    unsigned char reserved_000[0x458];
    AnimationResourceFile* laser_animation;     // +0x458
};

struct LineLaserParams_0041c8c0 {
    Vector3 position;                   // +0x00
    float angle;                       // +0x0C
    unsigned char reserved_010[4];
    float length;                      // +0x14
    unsigned char reserved_018[4];
    float length_step;                 // +0x1C
    float speed;                       // +0x20
    short colour;                      // +0x24
    short script;                      // +0x26
    unsigned int flags;                // +0x28
    unsigned char reserved_02C[0x1DC - 0x2C];
};

struct LineStartupTimer_0041c8c0 : FrameTimer {
    // The startup reset stores elapsed before previous, as in the retail
    // line-laser initializer; FrameTimer::Set has the same final timer state.
    void Set(int frame) {
        if (!(flags & 1)) {
            current = 0;
            previous = -999999;
            elapsed = 0.0f;
            speed = &g_score_default_speed;
            flags |= 1;
        }
        current = frame;
        elapsed = (float)frame;
        previous = frame - 1;
    }
};

struct LineLaser_0041c8c0 {
    unsigned char reserved_000[0x0C];
    int state;                           // +0x0C
    unsigned char reserved_010[0x24 - 0x10];
    Vector3 position;                    // +0x24
    LineVelocity_0041c8c0 velocity;
    float angle;                         // +0x3C
    float length;                        // +0x40
    float length_step;                   // +0x44
    float speed;                         // +0x48
    float acceleration;                  // +0x4C
    unsigned char reserved_050[0x40C - 0x50];
    int track_count;                     // +0x40C
    LineStartupTimer_0041c8c0 startup_timer;
    LineLaserParams_0041c8c0 params;         // +0x424
    Entity beam;                         // +0x600
    Entity flare;                        // +0x9AC

    int Initialize(const LineLaserParams_0041c8c0* init);
};

typedef char LineLaserParamsSize_0041c8c0[sizeof(LineLaserParams_0041c8c0) == 0x1DC ? 1 : -1];
typedef char LineLaserBeamOffset_0041c8c0[offsetof(LineLaser_0041c8c0, beam) == 0x600 ? 1 : -1];
typedef char LineLaserFlareOffset_0041c8c0[offsetof(LineLaser_0041c8c0, flare) == 0x9AC ? 1 : -1];

extern "C" LaserAnimationBank_0041e5c0* g_laser_manager;
extern "C" int g_bullet_script_first[];          // first laser script of each colour

#pragma code_seg(".text$00zline")
__declspec(noinline) int LineLaser_0041c8c0::Initialize(const LineLaserParams_0041c8c0* init) {
    params = *init;
    state = 2;
    Entity* animation = &beam;
    Entity_StartScript(g_laser_manager->laser_animation, animation,
                                params.script + g_bullet_script_first[params.colour]);
    beam.StopFrame() = 2;
    asm_FUN_0043ee30_0043ee30(animation);
    if (params.flags & 1)
        animation->AnimationFlags() = (animation->AnimationFlags() & ~0x20) | 0x10;
    beam.AnimationFlags() = (beam.AnimationFlags() & 0xFC63FFFF) | 0x600000;
    animation = &flare;
    Entity_StartScript(g_laser_manager->laser_animation, animation, params.script + 0x103);
    flare.StopFrame() = 2;
    asm_FUN_0043ee30_0043ee30(animation);
    animation->AnimationFlags() = (animation->AnimationFlags() & ~0x20) | 0x10;
    flare.AnimationFlags() = (flare.AnimationFlags() & 0xFC7FFFFF) | 0x400000;
    startup_timer.Set(30);
    position = params.position;
    track_count = 0x18;
    length = params.length;
    length_step = params.length_step;
    speed = params.speed;
    angle = params.angle;
    if (length > 0.0f)
        acceleration = 0.01f;
    else
        acceleration = 0.0f;
    velocity.SetPolar(angle, speed);
    return 0;
}
#pragma code_seg()
