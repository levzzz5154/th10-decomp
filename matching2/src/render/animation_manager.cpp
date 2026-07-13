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
void __fastcall Entity_Init(void* unused, Entity* entity);
int FUN_0043ee30(AnimationObject* animation);
void AnimationObject_Render(void* manager, AnimationObject* animation);

static unsigned int AnimationManager_NextPoolIndex(unsigned int index) {
    unsigned int next = (index + 1) & 0x80000FFFu;
    if ((int)next < 0) {
        next = ((next - 1) | 0xFFFFF000u) + 1;
    }
    return next;
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
    void** resource =
        (void**)(animationBytes + 0x35C - sizeof(void*));
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
    float* destination = (float*)((uint8_t*)animation + 0x340);
    destination[0] = position[0];
    destination[1] = position[1];
    destination[2] = position[2];
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
    *(short*)((uint8_t*)animation + 0x304) = *(short*)context;
}

void AnimationManager_SetStopFrame(
    void* manager, int animationHandle, short frame) {
    AnimationObject* animation =
        AnimationManager_Find(manager, animationHandle);
    if (animation != 0) {
        AnimationObject_ApplyToRootAndChildren(
            animation, AnimationObject_WriteStopFrame, &frame);
    }
}

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
    unsigned int* flags =
        (unsigned int*)((uint8_t*)animation + 0x35C);
    if (change->set) {
        *flags |= change->flag;
    } else {
        *flags &= ~change->flag;
    }
}

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

void AnimationManager_MarkResourceForRemoval(
    void* manager, void* resource) {
    for (unsigned int listIndex = 0; listIndex != 2; ++listIndex) {
        AnimationListNode* node =
            AnimationManager_List(manager, listIndex);
        while (node != 0) {
            AnimationObject* animation = node->animation;
            node = node->next;
            uint8_t* bytes = (uint8_t*)animation;
            if (*(void**)(bytes + 0x308) == resource) {
                *(unsigned int*)(bytes + 0x35C) |= 0x04000000u;
            }
        }
    }
}

static void AnimationObject_LoadScriptInternal(
    AnimationObject* animation, void* resource, int animationIndex,
    bool resetEntity) {
    uint8_t* animationBytes = (uint8_t*)animation;
    uint8_t* resourceBytes = (uint8_t*)resource;
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
    *(short*)(animationBytes + 0x38A) = (short)animationIndex;
    *(unsigned short*)(animationBytes + 0x386) =
        *(unsigned short*)resourceBytes;
    *(void**)(animationBytes + 0x308) = resource;
    *(unsigned int*)(animationBytes + 0x35C) &= 0xFFFFF9FFu;
    *(void**)(animationBytes + 0x38C) = script;
    *(void**)(animationBytes + 0x390) = script;

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
    *(unsigned int*)(animationBytes + 0x35C) &= ~1u;

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

void AnimationObject_InitializeScriptState(
    AnimationObject* animation, void* resource, int animationIndex) {
    uint8_t* bytes = (uint8_t*)animation;
    *(unsigned int*)(bytes + 0x340) = 0;
    *(unsigned int*)(bytes + 0x344) = 0;
    *(unsigned int*)(bytes + 0x348) = 0;
    *(unsigned int*)(bytes + 0x334) = 0;
    *(unsigned int*)(bytes + 0x338) = 0;
    *(unsigned int*)(bytes + 0x33C) = 0;
    *(unsigned int*)(bytes + 0x34C) = 0;
    *(unsigned int*)(bytes + 0x350) = 0;
    *(unsigned int*)(bytes + 0x35C) |= 0x40000000u;
    *(short*)(bytes + 0x38A) = (short)animationIndex;
    *(unsigned int*)(bytes + 0x354) = 0;
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

void AnimationManager_SetTranslatedPosition(
    void* manager, int animationHandle, const float* position) {
    float translated[3] = {
        position[0] + _DAT_00470b4c,
        position[1] + _DAT_00470b48,
        position[2]
    };
    AnimationManager_SetPosition(manager, animationHandle, translated);
}

bool AnimationManager_ValidateHandle(
    void* manager, int* animationHandle) {
    if (AnimationManager_Find(manager, *animationHandle) != 0) {
        return true;
    }
    *animationHandle = 0;
    return false;
}

void AnimationManager_MarkForRemovalAndClearHandle(
    void* manager, int* animationHandle) {
    AnimationManager_SetFlag(
        manager, *animationHandle, 0x04000000u);
    *animationHandle = 0;
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
    uint8_t* bytes = (uint8_t*)animation;
    if ((*(unsigned int*)(bytes + 0x35C) & 0x04000000u) != 0) {
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
        uint8_t* bytes = (uint8_t*)animation;
        if ((*(unsigned int*)(bytes + 0x35C) & 0x04000000u) == 0) {
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
        if (*(short*)((uint8_t*)childAnimation + 0x38A) == scriptIndex) {
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
    *(unsigned int*)(bytes + 0x35C) |= 0x40000000u;
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
