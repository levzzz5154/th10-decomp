// =============================================================================
// animation_manager.hpp - Animation lookup and shared-position operations
// =============================================================================
#pragma once

struct AnimationObject;
void AnimationObject_Render(void* manager, AnimationObject* animation);

struct AnimationTextureRecord {
    unsigned int texture;
    unsigned int reserved_004;
    unsigned int reserved_008;
    unsigned int bytes_per_pixel;
};

struct AnimationResourceBatchEntry {
    void* resource;
    void* allocation;
};

struct AnimationResourceBatch {
    void* active;
    AnimationResourceBatchEntry* entries;
    int entry_count;
    void* auxiliary_a;
    void* auxiliary_b;
    void* auxiliary_c;
};

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
void AnimationManager_StopAtFrame2(const int* animationHandle);
void AnimationManager_StopAtFrame3(const int* animationHandle);
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
int AnimationObject_ConfigureFromResource(
    void* animation, void* resource, int animationIndex);
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
void AnimationManager_ClearIndexedResources(void* manager, unsigned int index,
                                             void (*release)(void*),
                                             void (*free_memory)(void*));
void AnimationManager_ClearResourceSlot(void* manager, int index,
                                        void (*release)(void*),
                                        void (*free_memory)(void*));
void AnimationManager_ConfigureDigitTriplet(
    void* resource_manager, int value, int number,
    int (*configure)(void*, int));
void AnimationManager_RegisterResource(void* manager, unsigned int index,
                                       const char* name, int value,
                                       int flags);
void AnimationManager_QueueResource(void* manager, int resource_id,
                                    void* resource);
void AnimationManager_CopyPositionRecord(void* manager, unsigned int index,
                                         const float* source);
int AnimationTexture_Create(unsigned int width, unsigned int height,
                            unsigned int format_index,
                            AnimationTextureRecord* output);
void AnimationManager_ReleaseResourceBatch(
    AnimationResourceBatch* batch, void* context,
    void (*prepare)(void*, void*),
    void (*release)(void*), void (*free_memory)(void*));
