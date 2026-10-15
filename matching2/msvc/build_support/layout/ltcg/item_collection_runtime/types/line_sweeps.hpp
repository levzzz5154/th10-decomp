#pragma once
#include <stddef.h>
#include "item_spawn.hpp"
#include "animation_public.hpp"
struct LineSweepVector_0041e260 : Vector3 {
    LineSweepVector_0041e260() {}
    LineSweepVector_0041e260(float px,float py,float pz) {x=px;y=py;z=pz;}
};
// The retail step Z lives in memory and participates in every FP update.
// Keep that load observable, including the add-zero effect on signed zero.
struct LinePolarVelocity_0041f800 {
    float x,y;
    __declspec(noinline) LinePolarVelocity_0041f800* SetPolar(float angle,float speed);
};
struct LineSweepStep_0041e260 { LinePolarVelocity_0041f800 velocity; volatile float z; };
struct LineEffectSweep_0041e260 {
    unsigned char reserved_000[0xc];
    int retired;
    unsigned char reserved_010[0x24-0x10];
    LineSweepVector_0041e260 position;
    unsigned char reserved_030[0x3c-0x30];
    float angle;
    float length;
    unsigned char reserved_044[0x44a-0x44];
    short script_all;
    unsigned char reserved_44c[0x466-0x44c];
    short script_in_bounds;
    __declspec(noinline) int CreateAllSegments(int spawn_items);
    __declspec(noinline) int CreateSegmentsInBounds(int spawn_items);
};
struct LineAnimationResourceBank_0041e260 {
    unsigned char reserved_000[0x458];
    void* line_animation;
};
struct LineAnimationNode_0041e260 {
    Entity* object;
    LineAnimationNode_0041e260* next;
    LineAnimationNode_0041e260* previous;
};
struct LineAnimationRegistry_0041e260 {
    unsigned char reserved_000[0x72dad4];
    LineAnimationNode_0041e260* head;
    LineAnimationNode_0041e260* tail;
    unsigned char reserved_72dadc[0x732454-0x72dadc];
    int next_handle;
};
typedef char LinePositionCheck_0041e260[offsetof(LineEffectSweep_0041e260,position)==0x24?1:-1];
typedef char LineScriptCheck_0041e260[offsetof(LineEffectSweep_0041e260,script_all)==0x44a?1:-1];
typedef char LineScriptCheck_0041f400[offsetof(LineEffectSweep_0041e260,script_in_bounds)==0x466?1:-1];
extern "C" {
extern ItemSpawnManager_0041bb00* data_00477818;
extern LineAnimationResourceBank_0041e260* g_laser_manager;
extern float data_00470cd8;
extern float data_00470d1c;
extern float data_00470b4c;
extern float data_00470b48;
extern float data_00470bcc;
extern float data_00470b40;
extern float data_00470b3c;
extern float data_00470b04;
extern float data_00470b38;
}
struct AnimationResource_0043e710;
struct AnimationObject_0043e710;
extern "C" __declspec(noinline) void* __stdcall LoadScript_0043e710(
    AnimationResource_0043e710* resource,AnimationObject_0043e710* object,int index);
