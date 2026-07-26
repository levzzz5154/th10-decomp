#pragma once
#include <cstdint>
struct StageFocusEntity { uint32_t handle; float scale_y, sprite_height; int suppress_focus_fade; unsigned char alpha, base_alpha; };
struct StageFocusNode { StageFocusEntity* entity; StageFocusNode* next; };
struct StageFocusSlot { uint32_t handle; float x,y,z,half_width; };
struct StageFocusState { int frame, secondary_frame, stage_id; void* selected; StageFocusSlot slots[10]; };
struct StageFocusEnv { int current_stage_id; float camera_x,camera_y; StageFocusNode* active; StageFocusNode* pending; void (*prepare)(StageFocusState*,void*,int); };
int StageFocus_UpdateFade(StageFocusState* state,const StageFocusEnv* env);
