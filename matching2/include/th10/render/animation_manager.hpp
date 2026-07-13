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
void AnimationManager_SetPosition(
    void* manager, int animationHandle, const float* position);
int PlayerAnimation_Create(
    void* resource, void* scratch, int animationIndex,
    const float* position);
