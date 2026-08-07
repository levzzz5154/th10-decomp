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

// The manager keeps two independent intrusive lists at +0x72DAD4 and
// +0x72DADC.  Keep membership typed so gameplay does not treat a nonzero
// handle as live without asking the retail layout.
enum AnimationManagerHandleMembership {
    AnimationManagerHandle_Absent = 0,
    AnimationManagerHandle_Primary = 1,
    AnimationManagerHandle_Secondary = 2
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
// Link a registered object as a child of another registered object.  The
// host twin of the retail child-list insert (the second node at retail
// +0x10 / host +0x1C): the child's membership node is head-inserted into
// the parent's chain so that AnimationManager_FindChildByScriptIndex can
// resolve it.  The retail builders inline this insert (e.g. sub_40B070's
// creation family); the standalone uses this function at the creation
// sites.  Head-insert matches the retail's newest-first ordering; the tag
// lookup is order-insensitive (tags are unique per parent).
void AnimationManager_AttachChild(void* parent, void* child);

// Typed host adapter for gameplay callers that need the retail manager
// without exposing AnimationObject's late fields in their own layouts. The
// adapter is a function table so gameplay-only tests do not acquire a link
// dependency on the full renderer when no manager is bound.
struct AnimationManagerAdapter {
    typedef AnimationManagerHandleMembership (*MembershipFn)(void*, int);
    typedef bool (*SetFlagFn)(void*, int, unsigned int);
    typedef bool (*SetFrameFn)(void*, int, short);
    typedef int (*FindChildFn)(void*, int, short);
    typedef bool (*AttachChildFn)(void*, int, int);
    typedef int (*CreateFn)(void*, void*, int, int, const float*);

    void* manager;
    void* resource;
    int render_bucket;
    MembershipFn membership_fn;
    SetFlagFn set_flag_fn;
    SetFrameFn set_frame_fn;
    FindChildFn find_child_fn;
    AttachChildFn attach_child_fn;
    CreateFn refetch_fn;
    CreateFn create_fn;

    AnimationManagerAdapter(void* manager_ = 0, void* resource_ = 0,
                            int render_bucket_ = 15)
        : manager(manager_), resource(resource_),
          render_bucket(render_bucket_), membership_fn(0), set_flag_fn(0),
          set_frame_fn(0), find_child_fn(0), attach_child_fn(0),
          refetch_fn(0), create_fn(0) {}

    bool HasManager() const {
        return manager != 0 && membership_fn != 0;
    }
    bool HasResourceBinding() const {
        return resource != 0 && refetch_fn != 0 && create_fn != 0;
    }
    AnimationManagerHandleMembership Membership(int handle) const {
        return HasManager() ? membership_fn(manager, handle) :
                              AnimationManagerHandle_Absent;
    }
    bool IsPrimary(int handle) const {
        return Membership(handle) == AnimationManagerHandle_Primary;
    }
    bool IsSecondary(int handle) const {
        return Membership(handle) == AnimationManagerHandle_Secondary;
    }
    bool IsLive(int handle) const {
        return Membership(handle) != AnimationManagerHandle_Absent;
    }
    bool SetFlag(int handle, unsigned int flag) const {
        return HasManager() && set_flag_fn != 0 &&
               set_flag_fn(manager, handle, flag);
    }
    bool SetHighPathFlag(int handle) const {
        return SetFlag(handle, 0x04000000u);
    }
    bool SetFrame(int handle, short frame) const {
        return HasManager() && set_frame_fn != 0 &&
               set_frame_fn(manager, handle, frame);
    }
    bool SetLowPathFrame(int handle, short frame = 1) const {
        return SetFrame(handle, frame);
    }
    int FindChild(int parent_handle, short script_index) const {
        return HasManager() && find_child_fn != 0 ?
            find_child_fn(manager, parent_handle, script_index) : 0;
    }
    bool AttachChild(int parent_handle, int child_handle) const {
        return HasManager() && attach_child_fn != 0 &&
               attach_child_fn(manager, parent_handle, child_handle);
    }
    int Refetch(int sprite_index, int layer = 15) const {
        return HasResourceBinding() ?
            refetch_fn(manager, resource, sprite_index,
                       layer >= 0 ? layer : render_bucket, 0) : 0;
    }
    int Create(int animation_index, int layer = 15,
               const float* position = 0) const {
        return HasResourceBinding() ?
            create_fn(manager, resource, animation_index,
                      layer >= 0 ? layer : render_bucket, position) : 0;
    }
};

typedef AnimationManagerAdapter AnimationManager_Adapter;
AnimationManagerAdapter AnimationManager_BindAdapter(
    void* manager, void* resource, int render_bucket = 15);
AnimationManagerHandleMembership AnimationManager_ClassifyHandle(
    void* manager, int animation_handle);
bool AnimationManager_HandleInList(void* manager, int animation_handle,
                                   AnimationManagerList list);
bool AnimationManager_IsPrimaryHandle(void* manager, int animation_handle);
bool AnimationManager_IsSecondaryHandle(void* manager, int animation_handle);


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
