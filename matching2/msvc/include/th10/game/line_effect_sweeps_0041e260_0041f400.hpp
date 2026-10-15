#pragma once
#include <stddef.h>
#include "th10/game/item_spawn_0041bb00.hpp"
#include "th10/render/animation_public_callers.hpp"
struct LineSweepVector {
    float x,y,z;
    LineSweepVector() {}
    LineSweepVector(float px,float py,float pz):x(px),y(py),z(pz) {}
};
// The retail step Z lives in memory and participates in every FP update.
// Keep that load observable, including the add-zero effect on signed zero.
struct LineSweepStep { float x,y; volatile float z; };
struct LinePolarVelocity_0041f800 {
    float x,y;
    __declspec(noinline) LinePolarVelocity_0041f800* SetPolar(float angle,float speed);
};
struct LineEffectSweep {
    unsigned char reserved_000[0xc];
    int retired;
    unsigned char reserved_010[0x24-0x10];
    LineSweepVector position;
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
struct LineAnimationResourceBank {
    unsigned char reserved_000[0x458];
    void* line_animation;
};
struct LineAnimationNode {
    Entity* object;
    LineAnimationNode* next;
    LineAnimationNode* previous;
};
struct LineAnimationRegistry {
    unsigned char reserved_000[0x72dad4];
    LineAnimationNode* head;
    LineAnimationNode* tail;
    unsigned char reserved_72dadc[0x732454-0x72dadc];
    int next_handle;
};
typedef char LinePositionCheck[offsetof(LineEffectSweep,position)==0x24?1:-1];
typedef char LineScriptCheck_0041e260[offsetof(LineEffectSweep,script_all)==0x44a?1:-1];
typedef char LineScriptCheck_0041f400[offsetof(LineEffectSweep,script_in_bounds)==0x466?1:-1];
extern "C" {
extern ItemSpawnManager* g_item_manager;
extern LineAnimationResourceBank* g_laser_manager;
extern float flt_12;
extern float flt_6;
extern float flt_224;
extern float flt_16;
extern float flt_32;
extern float flt_neg192;
extern float flt_192;
extern float flt_0;
extern float flt_448;
}
struct AnimationResourceFile;
struct AnimationObjectFile;
extern "C" __declspec(noinline) void __stdcall LoadScript_0043e710(
    AnimationResourceFile* resource,AnimationObjectFile* object,int index);
