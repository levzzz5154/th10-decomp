#pragma once
#include "th10/render/animation_public_callers.hpp"
struct CutAnimationId {
 unsigned int value;
 CutAnimationId() {}
 CutAnimationId(unsigned int id):value(id) {}
 CutAnimationId& operator=(CutAnimationId other) {value=other.value;return *this;}
 CutAnimationId& operator++() {++value;return *this;}
 bool operator==(CutAnimationId other) const {return value==other.value;}
};
struct CutAnimationNode {Entity* object;CutAnimationNode* next;CutAnimationNode* previous;};
struct CutAnimationLists {
 unsigned char reserved_000[0x72dad4];
 CutAnimationNode* head;CutAnimationNode* tail;
 unsigned char reserved_72dadc[0x732454-0x72dadc];
 CutAnimationId next_id;
 __declspec(noinline) CutAnimationId RegisterPrimaryBack(Entity* object);
};
struct CutAnimationResource {
 __forceinline CutAnimationId CreateOffset(int index,const Vector3* point);
};

struct AnimationResource_0043e710;
struct AnimationObject_0043e710;
extern "C" __declspec(noinline) void* __stdcall LoadScript_0043e710(AnimationResource_0043e710*,AnimationObject_0043e710*,int);
extern "C" {extern float data_00470b4c;extern float data_00470b48;}

#pragma code_seg(".text$80create")
__forceinline CutAnimationId CutAnimationResource::CreateOffset(int index,const Vector3* position) {
 Entity* object=static_cast<AnimationPool*>(data_00491c10)->Allocate();
 object->flags_35C|=0x40000000u;
 object->render_bucket=0;
 object->position.x=position->x+data_00470b4c;
 object->position.y=position->y+data_00470b48;
 object->position.z=position->z;
 LoadScript_0043e710(reinterpret_cast<AnimationResource_0043e710*>(this),
   reinterpret_cast<AnimationObject_0043e710*>(object),index);
 return static_cast<CutAnimationLists*>(data_00491c10)->RegisterPrimaryBack(object);
}
#pragma code_seg()
