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

enum AnimationManagerList {
    AnimationManagerList_Primary = 0,
    AnimationManagerList_Secondary = 1
};

enum AnimationListInsertion {
    AnimationListInsertion_Back = 0,
    AnimationListInsertion_Front = 1
};

typedef int (__fastcall *AnimationUpdateCallback)(AnimationObject* animation);
typedef int (__fastcall *AnimationDrawCallback)(AnimationObject* animation);
typedef int (*AnimationSpriteSelector)(
    AnimationObject* animation, void* resource, int spriteIndex);

// Storage lifecycle recovered from the animation-owned portions of
// GameStateInit (0x00445900) and the complete manager destructor (0x00446220).
void AnimationManager_InitializeStorage(void* manager);
void AnimationManager_DestroyStorage(void* manager);
AnimationObject* AnimationManager_AllocateObject(void* manager);
int AnimationManager_CreatePrimaryBack(
    void* manager, void* resource, int animationIndex, int renderBucket);
int AnimationManager_CreatePrimaryFront(
    void* manager, void* resource, int animationIndex, int renderBucket);
int AnimationManager_CreateSecondaryBack(
    void* manager, void* resource, int animationIndex, int renderBucket);
int AnimationManager_CreateSecondaryFront(
    void* manager, void* resource, int animationIndex, int renderBucket);
int AnimationManager_CreatePositionedPrimary(
    void* manager, void* resource, int animationIndex,
    const float* position);
AnimationObject* AnimationManager_Find(
    void* manager, int animationHandle);
int AnimationManager_RegisterObject(
    void* manager, AnimationObject* animation);
int AnimationManager_RegisterObjectAt(
    void* manager, AnimationObject* animation,
    AnimationManagerList list, AnimationListInsertion insertion);
void AnimationManager_RemoveObject(
    void* manager, AnimationObject* animation);
void AnimationManager_SetStopFrame(
    void* manager, int animationHandle, short frame);
void AnimationManager_SetStopFrameFromHandle(
    void* manager, const int* animationHandle, short frame);
int AnimationManager_SetStopFrameAndRun(
    void* manager, int animationHandle, short frame);
void AnimationManager_SetFlag(
    void* manager, int animationHandle, unsigned int flag);
void AnimationManager_ClearFlag(
    void* manager, int animationHandle, unsigned int flag);
void AnimationManager_MarkResourceForRemoval(
    void* manager, void* resource);
void AnimationObject_LoadScript(
    AnimationObject* animation, void* resource, int animationIndex);
void AnimationObject_LoadScriptPreservingState(
    AnimationObject* animation, void* resource, int animationIndex);
void AnimationObject_ChangeScript(
    AnimationObject* animation, void* resource, int animationIndex);
void AnimationManager_ChangeScript(
    void* manager, const int* animationHandle, int animationIndex);
void AnimationObject_InitializeScriptState(
    AnimationObject* animation, void* resource, int animationIndex);
void AnimationManager_SetPosition(
    void* manager, int animationHandle, const float* position);
void AnimationManager_SetTranslatedPosition(
    void* manager, int animationHandle, const float* position);
bool AnimationManager_ValidateHandle(void* manager, int* animationHandle);
void AnimationManager_MarkForRemovalAndClearHandle(
    void* manager, int* animationHandle);
int AnimationManager_SelectSpriteFromCurrentResource(
    void* manager, const int* animationHandle, int spriteIndex,
    AnimationSpriteSelector selector);
int AnimationManager_SelectSpriteFromResource(
    void* manager, const int* animationHandle, void* resource,
    int spriteIndex, AnimationSpriteSelector selector);
int AnimationManager_UpdatePrimary(void* manager);
int AnimationManager_UpdateSecondary(void* manager);
int AnimationManager_RenderBucket(void* manager, int bucketIndex);
int AnimationManager_FindChildByScriptIndex(
    void* manager, int animationHandle, short scriptIndex);
int PlayerAnimation_Create(
    void* resource, void* scratch, int animationIndex,
    const float* position);
int AnimationObject_ReadIntegerVariable(
    AnimationObject* animation, int variableId);
int* AnimationObject_ResolveIntegerVariable(
    AnimationObject* animation, int variableId, int* fallback,
    bool variableEncoded);
float* AnimationObject_ResolveFloatVariable(
    AnimationObject* animation, int variableId, float* fallback,
    bool variableEncoded);
unsigned int AnimationColor_MultiplyChannel(
    unsigned int left, unsigned int right);
