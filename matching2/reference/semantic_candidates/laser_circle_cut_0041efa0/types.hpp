#pragma once
#include <stddef.h>
#include "animation_ids.hpp"
#include "th10/game/item_spawn_0041bb00.hpp"
#include "th10/game/laser_spawn_0041c510.hpp"
#include "th10/render/animation_public_callers.hpp"
struct CutVector : Vector3 {
 CutVector() {}
 CutVector(float px,float py,float pz) {x=px;y=py;z=pz;}
 __declspec(noinline) CutVector* SetPolar(float angle,float speed);
 CutVector operator+(const CutVector& rhs) const {return CutVector(x+rhs.x,y+rhs.y,z+rhs.z);}
 CutVector operator*(float factor) const {return CutVector(x*factor,y*factor,z*factor);}
 CutVector& operator+=(const CutVector& rhs) {x+=rhs.x;y+=rhs.y;z+=rhs.z;return *this;}
 CutVector& operator*=(float factor) {x*=factor;y*=factor;z*=factor;return *this;}
};
struct CutSpawnParameters : LaserSpawnParameters_0041c510 {
 CutVector position;
 float angle,length,length_limit,total_length,width,speed;
 short type,script;
 unsigned char reserved_028[0x1dc-0x28];
};
typedef char CutParametersSize[sizeof(CutSpawnParameters)==0x1dc?1:-1];
struct CutLaser {
 unsigned char reserved_000[0x24];
 CutVector position;
 unsigned char reserved_030[0xc];
 float angle,length,width;
 unsigned char reserved_048[0x444-0x48];
 float total_length;
 unsigned char reserved_448[0x464-0x448];
 short type,script;
 __declspec(noinline) int CutCircle(const CutVector* center,float radius,int spawn_items);
};
typedef char CutLengthOffset[offsetof(CutLaser,length)==0x40?1:-1];
typedef char CutScriptOffset[offsetof(CutLaser,script)==0x466?1:-1];
struct CutAnimationBank : LaserManager_0041c510 {
 unsigned char reserved_440[0x458-0x440];
 void* line_animation;
};
extern "C" {
 extern ItemSpawnManager_0041bb00* data_00477818;
 extern float data_00470b04;
}
struct AnimationResource_0043e710;
struct AnimationObject_0043e710;
extern "C" __declspec(noinline) void* __stdcall LoadScript_0043e710(AnimationResource_0043e710*,AnimationObject_0043e710*,int);
