#pragma once
#include <stddef.h>
#include "th10/game/entity.hpp"
#include "th10/game/trigger_region_004267f0.hpp"
#include "th10/render/animation_public_callers.hpp"
#include "th10/platform/sound_queue.hpp"
struct LaserScheduler {
    int previous,current;
    float elapsed;
    const float* speed;
    unsigned int flags;
    __declspec(noinline) void Set(int frame);
};
struct GrowLaser;
struct LaserSprite {
    unsigned char reserved[0x30];
    float width,height;
};
// The first six existing virtual slots are not called by Update. Only the
// hit callback at vtable +0x18 is needed; no stand-in method bodies are defined.
struct GrowLaser {
    virtual void Slot00();
    virtual void Slot04();
    virtual void Slot08();
    virtual void Slot0c();
    virtual void Slot10();
    virtual void Slot14();
    virtual void OnPlayerHit(const Point3_OrientedRect* position,
        const Point3_OrientedRect* size,int mode);
    unsigned char reserved_004[8];
    int state;
    LaserScheduler timer;
    Point3_OrientedRect position;
    unsigned char reserved_030[0xc];
    float angle,length,width,length_growth,secondary_render_gate;
    unsigned char reserved_050[0x430-0x50];
    Point3_OrientedRect velocity;
    unsigned char reserved_43c[4];
    float angular_velocity,target_length;
    unsigned char reserved_448[4];
    float target_width;
    unsigned char reserved_450[4];
    int wait_frames,grow_frames,hold_frames,shrink_frames;
    unsigned int reserved_464;
    unsigned int flags;
    unsigned char reserved_46c[0x61c-0x46c];
    Entity primary_animation;
    Entity secondary_animation;
    __declspec(noinline) int Update();
};
struct LaserFollowTarget {
    unsigned char reserved[0x1068];
    Point3_OrientedRect position;
};
struct LaserFollowBank {
    unsigned char reserved[0x10];
    LaserFollowTarget* target;
};
struct LaserAnimationBank {
    unsigned char reserved[0x3e0b50];
    void* resource;
};
// Actual public 41F800 boundary. It writes only X/Y. Retail then reads the
// third stack word; that observed indeterminate Z is deliberately not zeroed.
struct LaserPolarPoint : Point3_OrientedRect {
    __declspec(noinline) LaserPolarPoint* SetPolar(float angle,float speed);
};
extern "C" {
extern float g_game_speed;
extern LaserFollowBank* g_enemy_ctrl;
extern LaserAnimationBank* data_004776f0;
float __stdcall NormalizeAngle_0044bc10(float angle,float increment);
void __stdcall RunLaserAnimation_0043ee30(Entity* object);
}
__declspec(noinline) void** __stdcall ItemAnimation_CreateOffset_00448db0(
    void* resource,void** output,int index,const Point3_OrientedRect* position);
typedef char LaserTimerOffset[offsetof(GrowLaser,timer)==0x10?1:-1];
typedef char LaserPositionOffset[offsetof(GrowLaser,position)==0x24?1:-1];
typedef char LaserVelocityOffset[offsetof(GrowLaser,velocity)==0x430?1:-1];
typedef char LaserFlagsOffset[offsetof(GrowLaser,flags)==0x468?1:-1];
typedef char LaserPrimaryOffset[offsetof(GrowLaser,primary_animation)==0x61c?1:-1];
typedef char LaserSecondaryOffset[offsetof(GrowLaser,secondary_animation)==0x9c8?1:-1];
typedef char LaserStateOffset[offsetof(GrowLaser,state)==0xc?1:-1];
typedef char LaserLengthOffset[offsetof(GrowLaser,length)==0x40?1:-1];
typedef char LaserTargetWidthOffset[offsetof(GrowLaser,target_width)==0x44c?1:-1];
typedef char LaserWaitOffset[offsetof(GrowLaser,wait_frames)==0x454?1:-1];
typedef char LaserShrinkOffset[offsetof(GrowLaser,shrink_frames)==0x460?1:-1];
