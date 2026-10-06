#pragma once
#include <stddef.h>
#include "th10/game/entity.hpp"
#include "th10/math/timer.hpp"
#include "th10/game/trigger_region_004267f0.hpp"
#include "th10/render/animation_public_callers.hpp"
#include "th10/platform/sound_queue.hpp"
struct LaserSprite { unsigned char reserved[0x30]; float width,height; };
// SetPolar at 41F800 writes only X/Y; the original caller still reads Z.
// Outside testing uses only X/Y. Preserve those actual boundaries and reads.
struct LinePosition : Point3_OrientedRect {
    __declspec(noinline) LinePosition* SetPolar(float angle,float speed);
    __declspec(noinline) int IsPartiallyOutside(float horizontal,float vertical) const;
};
// Virtual declarations describe the existing vtable. Unused slots have no
// stand-in bodies, and this graph constructs no replacement vtable or object.
struct LineLaser {
    virtual void RunCommands();
    virtual void Slot04();
    __declspec(noinline) virtual int Update();
    virtual void Slot0c();
    virtual void Slot10();
    virtual void Slot14();
    virtual void OnPlayerHit(const Point3_OrientedRect*,const Point3_OrientedRect*,int);
    virtual void Slot1c();
    virtual void Slot20();
    virtual void Motion0001();
    virtual void Motion0010();
    virtual void Motion0020();
    virtual void Motion0040();
    virtual void Motion0100();
    virtual void Motion0080();
    virtual void Bounce();
    virtual void Motion100000();
    virtual void Motion200000();
    virtual void Motion4000000();
    unsigned char reserved_004[8];
    int state;
    FrameTimer age;
    LinePosition position;
    Point3_OrientedRect velocity;
    float angle,length,width,grow_speed,traveled;
    unsigned char reserved_050[0x15c-0x50];
    FrameTimer flash_timer;
    unsigned char reserved_170[0x404-0x170];
    unsigned int flags;
    unsigned char reserved_408[8];
    FrameTimer hold_timer;
    unsigned char reserved_424[0x434-0x424];
    float length_limit;
    unsigned char reserved_438[4];
    float total_length;
    unsigned char reserved_440[0x600-0x440];
    Entity primary_animation;
    Entity secondary_animation;
};
struct LaserAnimationBank {unsigned char reserved[0x3e0b50];void* resource;};
extern "C" {
extern float data_00476f78;
extern TriggerField_004267f0* data_00477834;
extern LaserAnimationBank* data_004776f0;
void __stdcall RunLaserAnimation_0043ee30(Entity* object);
}
__declspec(noinline) void** __stdcall ItemAnimation_CreateOffset_00448db0(
    void* resource,void** output,int index,const Point3_OrientedRect* position);
typedef char LinePositionOffset[offsetof(LineLaser,position)==0x24?1:-1];
typedef char LineVelocityOffset[offsetof(LineLaser,velocity)==0x30?1:-1];
typedef char LineFlashOffset[offsetof(LineLaser,flash_timer)==0x15c?1:-1];
typedef char LineFlagsOffset[offsetof(LineLaser,flags)==0x404?1:-1];
typedef char LineHoldOffset[offsetof(LineLaser,hold_timer)==0x410?1:-1];
typedef char LineLimitOffset[offsetof(LineLaser,length_limit)==0x434?1:-1];
typedef char LinePrimaryOffset[offsetof(LineLaser,primary_animation)==0x600?1:-1];
typedef char LineSecondaryOffset[offsetof(LineLaser,secondary_animation)==0x9ac?1:-1];
typedef char LineAgeOffset[offsetof(LineLaser,age)==0x10?1:-1];
typedef char LineLengthOffset[offsetof(LineLaser,length)==0x40?1:-1];
typedef char LineWidthOffset[offsetof(LineLaser,width)==0x44?1:-1];
typedef char LineTraveledOffset[offsetof(LineLaser,traveled)==0x4c?1:-1];
typedef char LineTotalLengthOffset[offsetof(LineLaser,total_length)==0x43c?1:-1];
