// 0x0041E5C0: set a laser up from its creation parameters.
//
// The parameters are kept whole. The beam and its origin flare each get their
// animation started and stepped once, and the laser's position, angle, length
// and width are taken from the parameters.
//
// It is a virtual method: the laser in ECX, the parameters on the stack.
#include "th10/game/entity_script_start.hpp"

struct AnimationResource_0043e710;
void __stdcall Entity_StartScript_00404f30(AnimationResource_0043e710* resource,
                                           Entity* entity, int script);
extern "C" int __stdcall asm_FUN_0043ee30_0043ee30(Entity* entity);

struct LaserAnimationBank_0041e5c0 {
    unsigned char reserved_000[0x458];
    AnimationResource_0043e710* laser_animation;     // +0x458
};

struct LaserParams_0041e5c0 {
    Vector3 position;                    // +0x00
    unsigned char reserved_00C[0x18 - 0x0C];
    float angle;                         // +0x18
    unsigned char reserved_01C[0x24 - 0x1C];
    float length;                        // +0x24
    unsigned char reserved_028[0x2C - 0x28];
    float width;                         // +0x2C
    unsigned char reserved_030[0x40 - 0x30];
    short colour;                        // +0x40
    short script;                        // +0x42
    unsigned int flags;                  // +0x44
    unsigned char reserved_048[0x1F8 - 0x48];
};

struct Laser_0041e5c0 {
    unsigned char reserved_000[0x0C];
    int state;                           // +0x0C
    unsigned char reserved_010[0x24 - 0x10];
    Vector3 position;                    // +0x24
    unsigned char reserved_030[0x3C - 0x30];
    float angle;                         // +0x3C
    float length;                        // +0x40
    float unknown_44;                    // +0x44
    float width;                         // +0x48
    unsigned char reserved_04C[0x40C - 0x4C];
    int unknown_40c;                     // +0x40C
    unsigned char reserved_410[0x424 - 0x410];
    LaserParams_0041e5c0 params;         // +0x424
    Entity beam;                         // +0x61C
    Entity flare;                        // +0x9C8

    int Initialize(const LaserParams_0041e5c0* init);
};

extern "C" LaserAnimationBank_0041e5c0* g_laser_manager;
extern "C" int data_00474170[];          // first beam script of each colour

#pragma code_seg(".text$00zza_laser")
__declspec(noinline) int Laser_0041e5c0::Initialize(const LaserParams_0041e5c0* init) {
    params = *init;
    state = 3;
    Entity* animation = &beam;
    Entity_StartScript_00404f30(g_laser_manager->laser_animation, animation,
                                params.script + data_00474170[params.colour]);
    beam.StopFrame() = 2;
    asm_FUN_0043ee30_0043ee30(animation);
    if (params.flags & 2)
        animation->AnimationFlags() = (animation->AnimationFlags() & ~0x20) | 0x10;
    beam.AnimationFlags() = (beam.AnimationFlags() & 0xFC63FFFF) | 0x600000;
    animation = &flare;
    Entity_StartScript_00404f30(g_laser_manager->laser_animation, animation, params.script + 0x103);
    flare.StopFrame() = 2;
    asm_FUN_0043ee30_0043ee30(animation);
    animation->AnimationFlags() = (animation->AnimationFlags() & ~0x20) | 0x10;
    flare.AnimationFlags() = (flare.AnimationFlags() & 0xFC7FFFFF) | 0x400000;
    position = params.position;
    unknown_40c = 0x18;
    length = params.length;
    unknown_44 = 2.0f;
    width = params.width;
    angle = params.angle;
    return 0;
}
#pragma code_seg()
