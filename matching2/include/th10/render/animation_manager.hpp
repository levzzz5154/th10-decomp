// =============================================================================
// animation_manager.hpp - Animation lookup and shared-position operations
// =============================================================================
#pragma once

struct AnimationObject;

struct AnimationListNode {
    AnimationObject* animation;
    AnimationListNode* next;
    AnimationListNode* previous;
};

AnimationObject* AnimationManager_AllocateObject(void* manager);
AnimationObject* AnimationManager_Find(
    void* manager, int animationHandle);
int AnimationManager_RegisterObject(
    void* manager, AnimationObject* animation);
void AnimationManager_RemoveObject(
    void* manager, AnimationObject* animation);
void AnimationManager_SetStopFrame(
    void* manager, int animationHandle, short frame);
int AnimationManager_SetStopFrameAndRun(
    void* manager, int animationHandle, short frame);
void AnimationManager_SetFlag(
    void* manager, int animationHandle, unsigned int flag);
void AnimationManager_ClearFlag(
    void* manager, int animationHandle, unsigned int flag);
void AnimationManager_MarkResourceForRemoval(
    void* manager, void* resource);
void AnimationManager_SetPosition(
    void* manager, int animationHandle, const float* position);
void AnimationManager_SetTranslatedPosition(
    void* manager, int animationHandle, const float* position);
bool AnimationManager_ValidateHandle(void* manager, int* animationHandle);
int AnimationManager_FindChildByScriptIndex(
    void* manager, int animationHandle, short scriptIndex);
int PlayerAnimation_Create(
    void* resource, void* scratch, int animationIndex,
    const float* position);
