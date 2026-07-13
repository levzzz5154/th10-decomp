// =============================================================================
// animation_manager.cpp - Handle lookup and position propagation
// Functions: 0x004489D0 (Register), 0x00448DB0 (player creation),
//            0x0043E710 (LoadScript), 0x004491C0 (Find),
//            0x004492F0 (SetPosition), 0x00449950 (Allocate)
// =============================================================================
#include "th10/render/animation_manager.hpp"
#include "th10/game/entity.hpp"

extern "C" void* operator_new(unsigned int size);
extern void* g_pGameStateManager;
extern float _DAT_00470b48;
extern float _DAT_00470b4c;
extern unsigned int DAT_00476f78;

Entity* __fastcall Entity_Constructor(Entity* entity);
void __fastcall Entity_Init(void* unused, Entity* entity);
void FUN_0043ee30(AnimationObject* animation);

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
    uint8_t* bytes = (uint8_t*)manager;
    AnimationListNode* node =
        (AnimationListNode*)((uint8_t*)animation + 4);
    node->animation = animation;
    node->next = 0;
    node->previous = 0;

    AnimationListNode** head =
        (AnimationListNode**)(bytes + 0x72DAD4);
    AnimationListNode** tail =
        (AnimationListNode**)(bytes + 0x72DAD4 + sizeof(AnimationListNode*));
    if (*head == 0) {
        *head = node;
    } else {
        if ((*tail)->next != 0) {
            node->next = (*tail)->next;
            (*tail)->next->previous = node;
        }
        (*tail)->next = node;
        node->previous = *tail;
    }
    *tail = node;

    int* nextHandle = (int*)(bytes + 0x732454);
    ++*nextHandle;
    if (*nextHandle == 0) {
        ++*nextHandle;
    }
    *(int*)animation = *nextHandle;
    return *nextHandle;
}

static void AnimationObject_SetPosition(
    AnimationObject* animation, const float* position) {
    float* destination = (float*)((uint8_t*)animation + 0x340);
    destination[0] = position[0];
    destination[1] = position[1];
    destination[2] = position[2];
}

void AnimationObject_LoadScript(
    AnimationObject* animation, void* resource, int animationIndex) {
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

    Entity_Init(0, (Entity*)animation);
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

void AnimationManager_SetPosition(
    void* manager, int animationHandle, const float* position) {
    AnimationObject* animation =
        AnimationManager_Find(manager, animationHandle);
    if (animation == 0) {
        return;
    }

    AnimationObject_SetPosition(animation, position);
    if (*(int*)((uint8_t*)animation + 0x18) != 0) {
        return;
    }

    AnimationListNode* child =
        *(AnimationListNode**)((uint8_t*)animation + 0x14);
    while (child != 0) {
        AnimationObject_SetPosition(child->animation, position);
        child = child->next;
    }
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
