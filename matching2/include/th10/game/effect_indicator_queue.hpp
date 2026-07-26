#pragma once
struct EffectIndicatorNode{EffectIndicatorNode*next,*previous;int countdown,owner_tag;float x,intensity;int anchor_mode;char text[72];float offset;int vm_value,vm_flags;};
struct EffectIndicatorState{int slot,handles[10];float positions[10][3],values[10];};
struct EffectIndicatorSpawn{int handle;float position[3];};
struct EffectIndicatorOps{void*context;void(*retire_handle)(void*,int);EffectIndicatorSpawn(*spawn)(void*,const EffectIndicatorNode*,int script,int alpha,float scale_a,float scale_b);void(*format_text)(void*,int handle,int anchor,const char*text);void(*release_node)(void*,EffectIndicatorNode*);};
// 0x00419120; queue head is EAX, state/free flag are the two stack arguments.
int EffectIndicatorQueue_Drain(EffectIndicatorNode*,EffectIndicatorState*,int current_owner,bool release_nodes,const EffectIndicatorOps*);
