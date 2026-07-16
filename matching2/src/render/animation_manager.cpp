// =============================================================================
// animation_manager.cpp - Handle lookup and position propagation
// Functions: 0x004489D0/0x00448A50/0x00448AC0/0x00448B40 (Register),
//            0x00448860/0x00448900 (Update), 0x00448980 (render bucket),
//            0x00448DB0 (player creation), 0x0043E710/0x0043E7E0
//            (LoadScript), 0x004491C0 (Find),
//            0x004492F0 (SetPosition), 0x00449950 (Allocate)
// =============================================================================
#include "th10/render/animation_manager.hpp"
#include "th10/game/entity.hpp"

extern "C" void* operator_new(unsigned int size);
extern "C" void _free(void* allocation);
extern void* g_pGameStateManager;
extern float _DAT_00470b48;
extern float _DAT_00470b4c;
extern unsigned int DAT_00476f78;

Entity* __fastcall Entity_Constructor(Entity* entity);
void __fastcall Entity_Destructor(Entity* entity);
void __fastcall Entity_Init(void* unused, Entity* entity);
int FUN_0043ee30(AnimationObject* animation);
void AnimationObject_Render(void* manager, AnimationObject* animation);

static AnimationListNode* AnimationManager_List(
    void* manager, unsigned int listIndex);
static void AnimationObject_SetPosition(
    AnimationObject* animation, const float* position);
static int* AnimationObject_RenderBucketSlot(AnimationObject* animation);

static unsigned int AnimationManager_NextPoolIndex(unsigned int index) {
    unsigned int next = (index + 1) & 0x80000FFFu;
    if ((int)next < 0) {
        next = ((next - 1) | 0xFFFFF000u) + 1;
    }
    return next;
}

// 0x004423C0 - Multiply two 7-bit-normalized color channels and saturate the
// result to the byte range used by the animation renderer.
uint32_t AnimationColor_MultiplyChannel(uint32_t left, uint32_t right) {
    uint32_t result = (left & 0xFF) * (right & 0xFF) >> 7;
    return result > 0xFF ? 0xFF : result;
}

// 0x0043EC70 - Read one of the animation interpreter's integer-valued
// variables. Float variables use the same truncating conversion as retail's
// x87 helper at 0x00463B2C.
int AnimationObject_ReadIntegerVariable(
    AnimationObject* animation, int variableId) {
    Entity* entity = (Entity*)animation;
    if (10000 <= variableId && variableId <= 10003) {
        return entity->ScriptIntegerVariables()[variableId - 10000];
    }
    if (10004 <= variableId && variableId <= 10007) {
        return (int)entity->ScriptFloatVariables()[variableId - 10004];
    }
    if (10008 <= variableId && variableId <= 10009) {
        return entity->ScriptExtraIntegerVariables()[variableId - 10008];
    }
    return variableId;
}

// 0x0043EDA0 - Resolve a writable integer-variable operand. The retail helper
// receives the candidate value in EAX and uses the instruction parameter mask
// to decide whether it is an encoded variable or a literal fallback address.
int* AnimationObject_ResolveIntegerVariable(
    AnimationObject* animation, int variableId, int* fallback,
    bool variableEncoded) {
    if (!variableEncoded) {
        return fallback;
    }
    Entity* entity = (Entity*)animation;
    if (10000 <= variableId && variableId <= 10003) {
        return &entity->ScriptIntegerVariables()[variableId - 10000];
    }
    if (10008 <= variableId && variableId <= 10009) {
        return &entity->ScriptExtraIntegerVariables()[variableId - 10008];
    }
    return fallback;
}

// 0x0043ED00 - Resolve a writable floating-point variable. IDs 10013..10015
// expose the base-position vector directly to animation scripts.
float* AnimationObject_ResolveFloatVariable(
    AnimationObject* animation, int variableId, float* fallback,
    bool variableEncoded) {
    if (!variableEncoded) {
        return fallback;
    }
    Entity* entity = (Entity*)animation;
    if (10004 <= variableId && variableId <= 10007) {
        return &entity->ScriptFloatVariables()[variableId - 10004];
    }
    if (10013 <= variableId && variableId <= 10015) {
        return &entity->BasePosition().x + (variableId - 10013);
    }
    return fallback;
}

void AnimationManager_InitializeStorage(void* manager) {
    uint8_t* bytes = (uint8_t*)manager;

    // GameStateInit's generated array constructors run before this clear.
    // Their observable state is discarded, so express the resulting state
    // directly and avoid reading uninitialized allocations.
    unsigned int* word = (unsigned int*)bytes;
    for (unsigned int count = 0x1CC918; count != 0; --count) {
        *word++ = 0;
    }

    // The first two words are reset-sensitive render-target handles.
    *(int*)(bytes + 0x00) = -1;
    *(int*)(bytes + 0x04) = -1;

    // Defaults established immediately before the pool initialization loop.
    *(unsigned int*)(bytes + 0x3ADA60) = 1;
    bytes[0x3ADA68] = 0;
    bytes[0x3ADA69] = 0;
    bytes[0x3ADA6A] = 0;
    bytes[0x3ADA6B] = 0;
    bytes[0x3ADA6C] = 0xFF;
    *(unsigned int*)(bytes + 0x3ADA64) = 0;
    *(unsigned int*)(bytes + 0x3ADA74) = 0;

    Entity* entity = (Entity*)(bytes + 0x68);
    for (unsigned int index = 0; index != 0x1000; ++index) {
        Entity_Init(0, entity);
        entity = (Entity*)((uint8_t*)entity + 0x3AC);
    }
}

// 0x00446220 - Drain both lists and destroy the render sentinels, manager-owned
// buffer, and complete 4,096-object pool.
void AnimationManager_DestroyStorage(void* manager) {
    uint8_t* bytes = (uint8_t*)manager;

    // Save the next node before removal because pooled objects are reset by
    // AnimationManager_RemoveObject and fallback objects are freed by it.
    for (unsigned int listIndex = 0; listIndex != 2; ++listIndex) {
        AnimationListNode* node = AnimationManager_List(manager, listIndex);
        while (node != 0) {
            AnimationListNode* next = node->next;
            AnimationManager_RemoveObject(manager, node->animation);
            node = next;
        }
    }

    Entity* sentinel = (Entity*)(bytes + 0x72DAE4);
    for (unsigned int index = 0; index != 20; ++index) {
        Entity_Destructor(sentinel);
        sentinel = (Entity*)((uint8_t*)sentinel + 0x3AC);
    }

    void** ownedBuffer = (void**)(bytes + 0x3AD488);
    if (*ownedBuffer != 0) {
        _free(*ownedBuffer);
    }
    *ownedBuffer = 0;

    Entity* pooled = (Entity*)(bytes + 0x68);
    for (unsigned int index = 0; index != 0x1000; ++index) {
        Entity_Destructor(pooled);
        pooled = (Entity*)((uint8_t*)pooled + 0x3AC);
    }
}

AnimationObject* AnimationManager_AllocateObject(void* manager) {
    uint8_t* bytes = (uint8_t*)manager;
    unsigned int* cursor = (unsigned int*)(bytes + 0x3AD068);
    unsigned int index = *cursor;

    if (bytes[0x3AC068 + index] != 0) {
        index = AnimationManager_NextPoolIndex(index);
        *cursor = index;
        if (bytes[0x3AC068 + index] != 0) {
            Entity* allocated = (Entity*)operator_new(0x3AC);
            if (allocated == 0) {
                return 0;
            }
            Entity_Constructor(allocated);
            Entity_Init(0, allocated);
            *cursor = AnimationManager_NextPoolIndex(*cursor);
            return (AnimationObject*)allocated;
        }
    }

    AnimationObject* animation =
        (AnimationObject*)(bytes + 0x68 + index * 0x3AC);
    bytes[0x3AC068 + index] = 1;
    *cursor = AnimationManager_NextPoolIndex(*cursor);
    return animation;
}

static int AnimationManager_CreateObject(
    void* manager, void* resource, int animationIndex, int renderBucket,
    AnimationManagerList list, AnimationListInsertion insertion) {
    AnimationObject* animation = AnimationManager_AllocateObject(manager);
    if (animation == 0) {
        return 0;
    }
    *AnimationObject_RenderBucketSlot(animation) = renderBucket;
    ((Entity*)animation)->AnimationFlags() |= 0x40000000u;
    AnimationObject_InitializeScriptState(animation, resource, animationIndex);
    return AnimationManager_RegisterObjectAt(
        manager, animation, list, insertion);
}

// 0x00448D00 - Allocate and append an object to the primary animation list.
int AnimationManager_CreatePrimaryBack(
    void* manager, void* resource, int animationIndex, int renderBucket) {
    return AnimationManager_CreateObject(
        manager, resource, animationIndex, renderBucket,
        AnimationManagerList_Primary, AnimationListInsertion_Back);
}

// 0x00448E30 - Allocate and prepend an object to the primary animation list.
int AnimationManager_CreatePrimaryFront(
    void* manager, void* resource, int animationIndex, int renderBucket) {
    return AnimationManager_CreateObject(
        manager, resource, animationIndex, renderBucket,
        AnimationManagerList_Primary, AnimationListInsertion_Front);
}

// 0x00448F60 - Allocate and append an object to the secondary animation list.
int AnimationManager_CreateSecondaryBack(
    void* manager, void* resource, int animationIndex, int renderBucket) {
    return AnimationManager_CreateObject(
        manager, resource, animationIndex, renderBucket,
        AnimationManagerList_Secondary, AnimationListInsertion_Back);
}

// 0x00449090 - Allocate and prepend an object to the secondary animation list.
int AnimationManager_CreateSecondaryFront(
    void* manager, void* resource, int animationIndex, int renderBucket) {
    return AnimationManager_CreateObject(
        manager, resource, animationIndex, renderBucket,
        AnimationManagerList_Secondary, AnimationListInsertion_Front);
}

// 0x00448D50 - Allocate a primary object whose initial position is supplied by
// the caller before its animation script is selected.
int AnimationManager_CreatePositionedPrimary(
    void* manager, void* resource, int animationIndex,
    const float* position) {
    AnimationObject* animation = AnimationManager_AllocateObject(manager);
    if (animation == 0) {
        return 0;
    }
    *AnimationObject_RenderBucketSlot(animation) = 0;
    ((Entity*)animation)->AnimationFlags() |= 0x40000000u;
    AnimationObject_SetPosition(animation, position);
    AnimationObject_LoadScript(animation, resource, animationIndex);
    return AnimationManager_RegisterObjectAt(
        manager, animation, AnimationManagerList_Primary,
        AnimationListInsertion_Back);
}

static AnimationListNode* AnimationManager_List(
    void* manager, unsigned int listIndex) {
    const unsigned int listOffset =
        0x72DAD4 + listIndex * 2 * sizeof(AnimationListNode*);
    return *(AnimationListNode**)((uint8_t*)manager + listOffset);
}

static AnimationListNode** AnimationManager_ListSlot(
    void* manager, unsigned int listIndex, bool tail) {
    const unsigned int slot = listIndex * 2 + (tail ? 1 : 0);
    return (AnimationListNode**)((uint8_t*)manager + 0x72DAD4 +
                                 slot * sizeof(AnimationListNode*));
}

// 0x004491C0 - Find a registered animation by its nonzero handle.
AnimationObject* AnimationManager_Find(
    void* manager, int animationHandle) {
    if (animationHandle == 0) {
        return 0;
    }

    AnimationListNode* node = AnimationManager_List(manager, 0);
    while (node != 0) {
        if (*(int*)node->animation == animationHandle) {
            return node->animation;
        }
        node = node->next;
    }

    node = AnimationManager_List(manager, 1);
    while (node != 0) {
        if (*(int*)node->animation == animationHandle) {
            return node->animation;
        }
        node = node->next;
    }
    return 0;
}

int AnimationManager_RegisterObject(
    void* manager, AnimationObject* animation) {
    return AnimationManager_RegisterObjectAt(
        manager, animation, AnimationManagerList_Primary,
        AnimationListInsertion_Back);
}

int AnimationManager_RegisterObjectAt(
    void* manager, AnimationObject* animation,
    AnimationManagerList list, AnimationListInsertion insertion) {
    uint8_t* bytes = (uint8_t*)manager;
    AnimationListNode* node =
        (AnimationListNode*)((uint8_t*)animation + 4);
    node->animation = animation;
    node->next = 0;
    node->previous = 0;

    AnimationListNode** head =
        AnimationManager_ListSlot(manager, (unsigned int)list, false);
    AnimationListNode** tail =
        AnimationManager_ListSlot(manager, (unsigned int)list, true);
    if (*head == 0) {
        *head = node;
        *tail = node;
    } else if (insertion == AnimationListInsertion_Front) {
        node->next = *head;
        (*head)->previous = node;
        *head = node;
    } else {
        if ((*tail)->next != 0) {
            node->next = (*tail)->next;
            (*tail)->next->previous = node;
        }
        (*tail)->next = node;
        node->previous = *tail;
        *tail = node;
    }

    int* nextHandle = (int*)(bytes + 0x732454);
    ++*nextHandle;
    if (*nextHandle == 0) {
        ++*nextHandle;
    }
    *(int*)animation = *nextHandle;
    return *nextHandle;
}

static void AnimationList_Unlink(AnimationListNode* node) {
    if (node->next != 0) {
        node->next->previous = node->previous;
    }
    if (node->previous != 0) {
        node->previous->next = node->next;
    }
    node->next = 0;
    node->previous = 0;
}

static AnimationListNode* AnimationObject_ChildMembership(
    AnimationObject* animation) {
    return (AnimationListNode*)((uint8_t*)animation + 4 +
                                sizeof(AnimationListNode));
}

static AnimationObject** AnimationObject_RenderChainSlot(
    AnimationObject* animation) {
    return (AnimationObject**)((uint8_t*)animation + 4 +
                               2 * sizeof(AnimationListNode));
}

static int* AnimationObject_RenderBucketSlot(AnimationObject* animation) {
    return (int*)((uint8_t*)AnimationObject_RenderChainSlot(animation) +
                  sizeof(AnimationObject*));
}

static AnimationUpdateCallback AnimationObject_UpdateCallback(
    AnimationObject* animation) {
    return *(AnimationUpdateCallback*)((uint8_t*)animation + 0x398);
}

static AnimationDrawCallback AnimationObject_DrawCallback(
    AnimationObject* animation) {
    return *(AnimationDrawCallback*)((uint8_t*)animation + 0x398 +
                                     sizeof(AnimationUpdateCallback));
}

// 0x00448BB0 - Unlink and retire a pooled or fallback animation object.
void AnimationManager_RemoveObject(
    void* manager, AnimationObject* animation) {
    if (animation == 0) {
        return;
    }

    uint8_t* managerBytes = (uint8_t*)manager;
    uint8_t* animationBytes = (uint8_t*)animation;
    AnimationListNode* node =
        (AnimationListNode*)(animationBytes + 4);
    AnimationListNode** primaryHead =
        (AnimationListNode**)(managerBytes + 0x72DAD4);
    AnimationListNode** primaryTail =
        (AnimationListNode**)(managerBytes + 0x72DAD4 +
                              sizeof(AnimationListNode*));
    AnimationListNode** secondaryHead =
        (AnimationListNode**)(managerBytes + 0x72DAD4 +
                              2 * sizeof(AnimationListNode*));
    AnimationListNode** secondaryTail =
        (AnimationListNode**)(managerBytes + 0x72DAD4 +
                              3 * sizeof(AnimationListNode*));

    if (*primaryTail == node) *primaryTail = node->previous;
    if (*primaryHead == node) *primaryHead = node->next;
    if (*secondaryTail == node) *secondaryTail = node->previous;
    if (*secondaryHead == node) *secondaryHead = node->next;
    AnimationList_Unlink(node);

    // The object also embeds a node at +0x10 when it belongs to a parent's
    // child list. The retail remover detaches both memberships.
    AnimationListNode* childMembership =
        AnimationObject_ChildMembership(animation);
    AnimationList_Unlink(childMembership);

    // The owned-resource pointer immediately precedes the 32-bit flags word.
    // Expressing it relative to the flags keeps host semantic tests valid
    // while producing retail +0x358 on the 32-bit target.
    void** resource = &((Entity*)animation)->OwnedResource();
    uint8_t* poolBegin = managerBytes + 0x68;
    uint8_t* poolEnd = managerBytes + 0x3AC068;
    if (poolBegin <= animationBytes && animationBytes < poolEnd) {
        unsigned int index =
            (unsigned int)(animationBytes - poolBegin) / 0x3AC;
        managerBytes[0x3AC068 + index] = 0;
        if (*resource != 0) {
            _free(*resource);
            *resource = 0;
        }
        Entity_Init(0, (Entity*)animation);
        return;
    }

    if (*resource != 0) {
        _free(*resource);
        *resource = 0;
    }
    _free(animation);
}

static void AnimationObject_SetPosition(
    AnimationObject* animation, const float* position) {
    Entity* entity = (Entity*)animation;
    entity->Position().x = position[0];
    entity->Position().y = position[1];
    entity->Position().z = position[2];
}

typedef void (*AnimationObjectOperation)(AnimationObject*, void* context);

static void AnimationObject_ApplyToRootAndChildren(
    AnimationObject* animation, AnimationObjectOperation operation,
    void* context) {
    operation(animation, context);
    AnimationListNode* childMembership =
        AnimationObject_ChildMembership(animation);
    if (childMembership->previous != 0) {
        return;
    }
    AnimationListNode* child = childMembership->next;
    while (child != 0) {
        operation(child->animation, context);
        child = child->next;
    }
}

static void AnimationObject_WriteStopFrame(
    AnimationObject* animation, void* context) {
    ((Entity*)animation)->StopFrame() = *(short*)context;
}

// 0x00449210 - Set the root stop frame and propagate it to direct children.
void AnimationManager_SetStopFrame(
    void* manager, int animationHandle, short frame) {
    AnimationObject* animation =
        AnimationManager_Find(manager, animationHandle);
    if (animation != 0) {
        AnimationObject_ApplyToRootAndChildren(
            animation, AnimationObject_WriteStopFrame, &frame);
    }
}

// 0x00449470 - Pointer-handle form used by gameplay owners.
void AnimationManager_SetStopFrameFromHandle(
    void* manager, const int* animationHandle, short frame) {
    AnimationManager_SetStopFrame(manager, *animationHandle, frame);
}

// 0x00449250 - Set a stop frame and immediately advance root and child scripts.
int AnimationManager_SetStopFrameAndRun(
    void* manager, int animationHandle, short frame) {
    AnimationObject* animation =
        AnimationManager_Find(manager, animationHandle);
    if (animation == 0) {
        return 0;
    }

    AnimationManager_SetStopFrame(manager, animationHandle, frame);
    int result = FUN_0043ee30(animation);
    AnimationListNode* childMembership =
        AnimationObject_ChildMembership(animation);
    if (childMembership->previous == 0) {
        AnimationListNode* child = childMembership->next;
        while (child != 0) {
            result = FUN_0043ee30(child->animation);
            child = child->next;
        }
    }
    return result;
}

struct AnimationFlagChange {
    unsigned int flag;
    bool set;
};

static void AnimationObject_ChangeFlag(
    AnimationObject* animation, void* context) {
    AnimationFlagChange* change = (AnimationFlagChange*)context;
    unsigned int* flags = &((Entity*)animation)->AnimationFlags();
    if (change->set) {
        *flags |= change->flag;
    } else {
        *flags &= ~change->flag;
    }
}

// 0x004492A0 - Set an animation flag on a root and its direct children.
// 0x00449590 - The fixed-flag entry point uses this operation with bit 1.
void AnimationManager_SetFlag(
    void* manager, int animationHandle, unsigned int flag) {
    AnimationObject* animation =
        AnimationManager_Find(manager, animationHandle);
    if (animation != 0) {
        AnimationFlagChange change = {flag, true};
        AnimationObject_ApplyToRootAndChildren(
            animation, AnimationObject_ChangeFlag, &change);
    }
}

// 0x004495E0 - Clear an animation flag on a root and its direct children.
void AnimationManager_ClearFlag(
    void* manager, int animationHandle, unsigned int flag) {
    AnimationObject* animation =
        AnimationManager_Find(manager, animationHandle);
    if (animation != 0) {
        AnimationFlagChange change = {flag, false};
        AnimationObject_ApplyToRootAndChildren(
            animation, AnimationObject_ChangeFlag, &change);
    }
}

// 0x004493E0 - Mark objects using a retired script resource for removal.
void AnimationManager_MarkResourceForRemoval(
    void* manager, void* resource) {
    for (unsigned int listIndex = 0; listIndex != 2; ++listIndex) {
        AnimationListNode* node =
            AnimationManager_List(manager, listIndex);
        while (node != 0) {
            AnimationObject* animation = node->animation;
            node = node->next;
            Entity* entity = (Entity*)animation;
            if (entity->ScriptResource() == resource) {
                entity->AnimationFlags() |= 0x04000000u;
            }
        }
    }
}

static void AnimationObject_LoadScriptInternal(
    AnimationObject* animation, void* resource, int animationIndex,
    bool resetEntity) {
    uint8_t* animationBytes = (uint8_t*)animation;
    uint8_t* resourceBytes = (uint8_t*)resource;
    Entity* entity = (Entity*)animation;
    void** scripts = *(void***)(resourceBytes + 0x11C);
    void* script = scripts[animationIndex];

    if (script == 0 || *(int*)(resourceBytes + 0x124) != 0) {
        unsigned int* destination = (unsigned int*)animation;
        for (int count = 0xEB; count != 0; --count) {
            *destination++ = 0;
        }
        return;
    }

    if (resetEntity) {
        Entity_Init(0, (Entity*)animation);
    }
    entity->ScriptIndex() = (short)animationIndex;
    entity->ScriptResourceId() = *(unsigned short*)resourceBytes;
    entity->ScriptResource() = resource;
    entity->AnimationFlags() &= 0xFFFFF9FFu;
    entity->ScriptBase() = script;
    entity->ScriptCursor() = script;

    unsigned int* timerFlags =
        (unsigned int*)(animationBytes + 0x6C);
    if ((*timerFlags & 1) == 0) {
        *(int*)(animationBytes + 0x60) = 0;
        *(unsigned int*)(animationBytes + 0x5C) = 0xFFF0BDC1u;
        *(int*)(animationBytes + 0x64) = 0;
        *(unsigned int**)(animationBytes + 0x68) = &DAT_00476f78;
        *timerFlags |= 1;
    }
    *(int*)(animationBytes + 0x60) = 0;
    *(int*)(animationBytes + 0x64) = 0;
    *(int*)(animationBytes + 0x5C) = -1;
    entity->AnimationFlags() &= ~1u;

    FUN_0043ee30(animation);
    ++*(int*)((uint8_t*)g_pGameStateManager + 0x4C);
}

void AnimationObject_LoadScript(
    AnimationObject* animation, void* resource, int animationIndex) {
    AnimationObject_LoadScriptInternal(
        animation, resource, animationIndex, true);
}

void AnimationObject_LoadScriptPreservingState(
    AnimationObject* animation, void* resource, int animationIndex) {
    AnimationObject_LoadScriptInternal(
        animation, resource, animationIndex, false);
}

// 0x00449870 - Initialize position/script state before selecting a script.
void AnimationObject_InitializeScriptState(
    AnimationObject* animation, void* resource, int animationIndex) {
    uint8_t* bytes = (uint8_t*)animation;
    Entity* entity = (Entity*)animation;
    entity->Position().x = 0.0f;
    entity->Position().y = 0.0f;
    entity->Position().z = 0.0f;
    entity->BasePosition().x = 0.0f;
    entity->BasePosition().y = 0.0f;
    entity->BasePosition().z = 0.0f;
    entity->RenderOffset().x = 0.0f;
    entity->RenderOffset().y = 0.0f;
    entity->AnimationFlags() |= 0x40000000u;
    entity->ScriptIndex() = (short)animationIndex;
    entity->RenderOffset().z = 0.0f;
    bytes[0x3A0] = 0x10;
    bytes[0x3A1] = 0x10;
    AnimationObject_LoadScriptPreservingState(
        animation, resource, animationIndex);
}

void AnimationManager_SetPosition(
    void* manager, int animationHandle, const float* position) {
    AnimationObject* animation =
        AnimationManager_Find(manager, animationHandle);
    if (animation == 0) {
        return;
    }

    AnimationObject_SetPosition(animation, position);
    AnimationListNode* childMembership =
        AnimationObject_ChildMembership(animation);
    if (childMembership->previous != 0) {
        return;
    }

    AnimationListNode* child = childMembership->next;
    while (child != 0) {
        AnimationObject_SetPosition(child->animation, position);
        child = child->next;
    }
}

// 0x00449350 - Apply the gameplay-to-render translation and propagate it.
void AnimationManager_SetTranslatedPosition(
    void* manager, int animationHandle, const float* position) {
    float translated[3] = {
        position[0] + _DAT_00470b4c,
        position[1] + _DAT_00470b48,
        position[2]
    };
    AnimationManager_SetPosition(manager, animationHandle, translated);
}

// 0x00449450 - Clear a stale animation handle after a failed lookup.
bool AnimationManager_ValidateHandle(
    void* manager, int* animationHandle) {
    if (AnimationManager_Find(manager, *animationHandle) != 0) {
        return true;
    }
    *animationHandle = 0;
    return false;
}

// 0x00449630 - Mark an object tree for removal and invalidate its owner handle.
void AnimationManager_MarkForRemovalAndClearHandle(
    void* manager, int* animationHandle) {
    AnimationManager_SetFlag(
        manager, *animationHandle, 0x04000000u);
    *animationHandle = 0;
}


// 0x00449670 - Select a sprite from the object's current script resource.
int AnimationManager_SelectSpriteFromCurrentResource(
    void* manager, const int* animationHandle, int spriteIndex,
    AnimationSpriteSelector selector) {
    AnimationObject* animation =
        AnimationManager_Find(manager, *animationHandle);
    if (animation == 0) {
        return -1;
    }
    return selector(
        animation, ((Entity*)animation)->ScriptResource(), spriteIndex);
}

// 0x004496A0 - Select a sprite from an explicitly supplied resource.
int AnimationManager_SelectSpriteFromResource(
    void* manager, const int* animationHandle, void* resource,
    int spriteIndex, AnimationSpriteSelector selector) {
    AnimationObject* animation =
        AnimationManager_Find(manager, *animationHandle);
    if (animation == 0) {
        return -1;
    }
    return selector(animation, resource, spriteIndex);
}

static AnimationObject** AnimationManager_RenderBucketHead(
    void* manager, unsigned int bucketIndex) {
    AnimationObject* sentinel =
        (AnimationObject*)((uint8_t*)manager + 0x72DAE4 +
                           bucketIndex * 0x3AC);
    return AnimationObject_RenderChainSlot(sentinel);
}

static bool AnimationManager_UpdateObject(
    void* manager, AnimationObject* animation) {
    if ((((Entity*)animation)->AnimationFlags() & 0x04000000u) != 0) {
        AnimationManager_RemoveObject(manager, animation);
        return false;
    }

    AnimationUpdateCallback callback =
        AnimationObject_UpdateCallback(animation);
    if (callback != 0) {
        callback(animation);
    }
    if (FUN_0043ee30(animation) != 0) {
        AnimationManager_RemoveObject(manager, animation);
        return false;
    }
    return true;
}

int AnimationManager_UpdatePrimary(void* manager) {
    AnimationObject* tails[19];
    for (unsigned int index = 0; index != 19; ++index) {
        AnimationObject* sentinel =
            (AnimationObject*)((uint8_t*)manager + 0x72DAE4 +
                               index * 0x3AC);
        tails[index] = sentinel;
        *AnimationObject_RenderChainSlot(sentinel) = 0;
    }

    AnimationListNode* node = AnimationManager_List(manager, 0);
    while (node != 0) {
        AnimationObject* animation = node->animation;
        node = node->next;
        if (AnimationManager_UpdateObject(manager, animation)) {
            int bucket = *AnimationObject_RenderBucketSlot(animation);
            *AnimationObject_RenderChainSlot(tails[bucket]) = animation;
            tails[bucket] = animation;
            *AnimationObject_RenderChainSlot(animation) = 0;
        }
        ++*(unsigned int*)((uint8_t*)manager + 0x64);
    }
    return 1;
}

int AnimationManager_UpdateSecondary(void* manager) {
    AnimationObject* sentinel =
        (AnimationObject*)((uint8_t*)manager + 0x72DAE4 + 19 * 0x3AC);
    AnimationObject* tail = sentinel;
    *AnimationObject_RenderChainSlot(sentinel) = 0;
    *(unsigned int*)((uint8_t*)manager + 0x64) = 0;

    AnimationListNode* node = AnimationManager_List(manager, 1);
    while (node != 0) {
        AnimationObject* animation = node->animation;
        node = node->next;
        if (AnimationManager_UpdateObject(manager, animation)) {
            *AnimationObject_RenderChainSlot(tail) = animation;
            tail = animation;
            *AnimationObject_RenderChainSlot(animation) = 0;
        }
        ++*(unsigned int*)((uint8_t*)manager + 0x64);
    }
    return 1;
}

int AnimationManager_RenderBucket(void* manager, int bucketIndex) {
    AnimationObject* animation =
        *AnimationManager_RenderBucketHead(manager, (unsigned int)bucketIndex);
    while (animation != 0) {
        if ((((Entity*)animation)->AnimationFlags() & 0x04000000u) == 0) {
            AnimationDrawCallback callback =
                AnimationObject_DrawCallback(animation);
            if (callback != 0) {
                callback(animation);
            }
            AnimationObject_Render(manager, animation);
        }
        animation = *AnimationObject_RenderChainSlot(animation);
    }
    return 1;
}

// 0x004497D0 - Resolve a direct child by script index.
int AnimationManager_FindChildByScriptIndex(
    void* manager, int animationHandle, short scriptIndex) {
    AnimationObject* animation =
        AnimationManager_Find(manager, animationHandle);
    if (animation == 0) {
        return 0;
    }

    AnimationListNode* child =
        AnimationObject_ChildMembership(animation)->next;
    while (child != 0) {
        AnimationObject* childAnimation = child->animation;
        if (((Entity*)childAnimation)->ScriptIndex() == scriptIndex) {
            return *(int*)childAnimation;
        }
        child = child->next;
    }
    return 0;
}

int PlayerAnimation_Create(
    void* resource, void* scratch, int animationIndex,
    const float* position) {
    AnimationObject* animation =
        AnimationManager_AllocateObject(g_pGameStateManager);
    if (animation == 0) {
        return 0;
    }

    uint8_t* bytes = (uint8_t*)animation;
    *(unsigned int*)(bytes + 0x20) = 0;
    ((Entity*)animation)->AnimationFlags() |= 0x40000000u;
    float translated[3] = {
        position[0] + _DAT_00470b4c,
        position[1] + _DAT_00470b48,
        position[2]
    };
    AnimationObject_SetPosition(animation, translated);
    AnimationObject_LoadScript(animation, resource, animationIndex);

    int handle =
        AnimationManager_RegisterObject(g_pGameStateManager, animation);
    *(int*)scratch = handle;
    return handle;
}
