#include "th10/math/timer.hpp"
#include "th10/render/animation_manager.hpp"

#include <cassert>
#include <cmath>
#include <cstring>
#include <vector>
#include <cstdlib>

float _DAT_00470afc = 1.0f;
float _DAT_00470b68 = 0.99f;
float _DAT_00470b64 = 1.01f;
float _DAT_00470b48 = 10.0f;
float _DAT_00470b4c = 20.0f;
unsigned int DAT_00476f78;
void* g_pGameStateManager;
static int entityInitializations;
static int entityDestructions;

struct Entity;

extern "C" void* operator_new(unsigned int size) {
    return std::malloc(size);
}

extern "C" void _free(void* allocation) {
    std::free(allocation);
}

Entity* Entity_Constructor(Entity* entity) {
    return entity;
}

void Entity_Init(void*, Entity*) {
    ++entityInitializations;
}

void Entity_Destructor(Entity* entity) {
    ++entityDestructions;
    unsigned char* bytes = (unsigned char*)entity;
    void** resource = (void**)(bytes + 0x35C - sizeof(void*));
    if (*resource != 0) {
        std::free(*resource);
        *resource = 0;
    }
}

static int scriptRuns;
static int scriptResult = 1;
int FUN_0043ee30(AnimationObject*) {
    ++scriptRuns;
    return scriptResult;
}

static int renderedObjects;
void AnimationObject_Render(void*, AnimationObject*) {
    ++renderedObjects;
}

static int updateCallbacks;
static int drawCallbacks;

static int UpdateCallback(AnimationObject*) {
    ++updateCallbacks;
    return 0;
}

static int DrawCallback(AnimationObject*) {
    ++drawCallbacks;
    return 0;
}

static AnimationObject** RenderChainSlot(AnimationObject* animation) {
    return (AnimationObject**)((unsigned char*)animation + 4 +
                               2 * sizeof(AnimationListNode));
}

static int* RenderBucketSlot(AnimationObject* animation) {
    return (int*)((unsigned char*)RenderChainSlot(animation) +
                  sizeof(AnimationObject*));
}

static void SetCallbacks(AnimationObject* animation) {
    *(AnimationUpdateCallback*)((unsigned char*)animation + 0x398) =
        UpdateCallback;
    *(AnimationDrawCallback*)((unsigned char*)animation + 0x398 +
                              sizeof(AnimationUpdateCallback)) = DrawCallback;
}

static void TestFrameTimer() {
    float speed = 1.0f;
    FrameTimer timer = {4, 5, 5.0f, &speed, 1};
    FrameTimer_Tick(&timer);
    assert(timer.previous == 5);
    assert(timer.current == 6);
    assert(timer.elapsed == 6.0f);

    speed = 0.5f;
    timer.elapsed = 6.25f;
    FrameTimer_Tick(&timer);
    assert(timer.previous == 6);
    assert(timer.current == 6);
    assert(timer.elapsed == 6.75f);

    speed = -0.75f;
    timer.elapsed = -1.5f;
    FrameTimer_Tick(&timer);
    assert(timer.current == -2);
    assert(std::fabs(timer.elapsed - -2.25f) < 0.0001f);
}

static void TestAnimationLookupAndPosition() {
    const unsigned int managerSize = 0x732458;
    std::vector<unsigned char> manager(managerSize, 0);
    g_pGameStateManager = &manager[0];
    unsigned char firstStorage[0x3AC] = {};
    unsigned char secondStorage[0x3AC] = {};
    AnimationObject* first = (AnimationObject*)firstStorage;
    AnimationObject* second = (AnimationObject*)secondStorage;
    *(int*)firstStorage = 17;
    *(int*)secondStorage = 29;
    *(int*)(firstStorage + 0x18) = 1;
    *(int*)(secondStorage + 0x18) = 1;

    AnimationListNode primary = {first, 0, 0};
    AnimationListNode secondary = {second, 0, 0};
    *(AnimationListNode**)(&manager[0x72DAD4]) = &primary;
    *(AnimationListNode**)(&manager[
        0x72DAD4 + 2 * sizeof(AnimationListNode*)]) = &secondary;

    assert(AnimationManager_Find(&manager[0], 0) == 0);
    assert(AnimationManager_Find(&manager[0], 17) == first);
    assert(AnimationManager_Find(&manager[0], 29) == second);
    assert(AnimationManager_Find(&manager[0], 100) == 0);

    const float position[3] = {12.5f, -4.0f, 3.25f};
    AnimationManager_SetPosition(&manager[0], 29, position);
    const float* stored = (const float*)(secondStorage + 0x340);
    assert(stored[0] == position[0]);
    assert(stored[1] == position[1]);
    assert(stored[2] == position[2]);

    AnimationManager_SetStopFrame(&manager[0], 29, 12);
    assert(*(short*)(secondStorage + 0x304) == 12);
    int runResult =
        AnimationManager_SetStopFrameAndRun(&manager[0], 29, 18);
    assert(runResult == 1);
    assert(*(short*)(secondStorage + 0x304) == 18);
    AnimationManager_SetFlag(&manager[0], 29, 2);
    assert((*(unsigned int*)(secondStorage + 0x35C) & 2) != 0);
    AnimationManager_ClearFlag(&manager[0], 29, 2);
    assert((*(unsigned int*)(secondStorage + 0x35C) & 2) == 0);

    *(void**)(secondStorage + 0x308) = (void*)0xCAFE;
    AnimationManager_MarkResourceForRemoval(
        &manager[0], (void*)0xCAFE);
    assert((*(unsigned int*)(secondStorage + 0x35C) & 0x04000000u) != 0);

    int validHandle = 29;
    assert(AnimationManager_ValidateHandle(&manager[0], &validHandle));
    int invalidHandle = 77;
    assert(!AnimationManager_ValidateHandle(&manager[0], &invalidHandle));
    assert(invalidHandle == 0);

    const float untranslated[3] = {1.0f, 2.0f, 3.0f};
    AnimationManager_SetTranslatedPosition(&manager[0], 29, untranslated);
    assert(stored[0] == 21.0f);
    assert(stored[1] == 12.0f);
    assert(stored[2] == 3.0f);

    AnimationListNode* rootChildren =
        (AnimationListNode*)(firstStorage + 4 + sizeof(AnimationListNode));
    AnimationListNode childLink = {second, 0, rootChildren};
    rootChildren->next = &childLink;
    rootChildren->previous = 0;
    *(short*)(secondStorage + 0x38A) = 0x44;
    AnimationManager_SetStopFrame(&manager[0], 17, 33);
    assert(*(short*)(firstStorage + 0x304) == 33);
    assert(*(short*)(secondStorage + 0x304) == 33);
    AnimationManager_SetFlag(&manager[0], 17, 0x80);
    assert((*(unsigned int*)(firstStorage + 0x35C) & 0x80) != 0);
    assert((*(unsigned int*)(secondStorage + 0x35C) & 0x80) != 0);
    assert(AnimationManager_FindChildByScriptIndex(
               &manager[0], 17, 0x44) == 29);

    unsigned char stateResource[0x128] = {};
    void* stateScripts[4] = {};
    stateScripts[2] = (void*)0x4321;
    *(void***)(stateResource + 0x11C) = stateScripts;
    *(unsigned short*)stateResource = 9;
    *(unsigned int*)(firstStorage + 0x340) = 0xFFFFFFFFu;
    *(unsigned int*)(firstStorage + 0x334) = 0xFFFFFFFFu;
    AnimationObject_InitializeScriptState(
        first, stateResource, 2);
    assert(*(unsigned int*)(firstStorage + 0x340) == 0);
    assert(*(unsigned int*)(firstStorage + 0x334) == 0);
    assert(*(short*)(firstStorage + 0x38A) == 2);
    assert(firstStorage[0x3A0] == 0x10);
    assert(firstStorage[0x3A1] == 0x10);
    assert(*(void**)(firstStorage + 0x308) == stateResource);

    std::memset(&manager[0], 0, manager.size());
    g_pGameStateManager = &manager[0];
    AnimationObject* pooled = AnimationManager_AllocateObject(&manager[0]);
    assert(pooled == (AnimationObject*)(&manager[0] + 0x68));
    assert(manager[0x3AC068] == 1);
    assert(*(unsigned int*)(&manager[0x3AD068]) == 1);
    int handle = AnimationManager_RegisterObject(&manager[0], pooled);
    assert(handle == 1);
    assert(AnimationManager_Find(&manager[0], handle) == pooled);

    const float playerPosition[3] = {2.0f, 3.0f, 4.0f};
    int scratch[3] = {};
    unsigned char resource[0x128] = {};
    void* scripts[0x1BA] = {};
    scripts[0x1B9] = (void*)0x5678;
    *(void***)(resource + 0x11C) = scripts;
    *(unsigned short*)resource = 23;
    int playerHandle = PlayerAnimation_Create(
        resource, scratch, 0x1B9, playerPosition);
    assert(playerHandle == 2);
    assert(scratch[0] == playerHandle);
    assert(scriptRuns == 3);
    AnimationObject* playerAnimation =
        AnimationManager_Find(&manager[0], playerHandle);
    assert(playerAnimation != 0);
    const float* translated =
        (const float*)((unsigned char*)playerAnimation + 0x340);
    assert(translated[0] == 22.0f);
    assert(translated[1] == 13.0f);
    assert(translated[2] == 4.0f);

    AnimationManager_RemoveObject(&manager[0], playerAnimation);
    assert(AnimationManager_Find(&manager[0], playerHandle) == 0);
    assert(manager[0x3AC068 + 1] == 0);

    AnimationObject* primaryFront =
        AnimationManager_AllocateObject(&manager[0]);
    int primaryFrontHandle = AnimationManager_RegisterObjectAt(
        &manager[0], primaryFront, AnimationManagerList_Primary,
        AnimationListInsertion_Front);
    AnimationListNode* primaryHead =
        *(AnimationListNode**)(&manager[0x72DAD4]);
    AnimationListNode* primaryTail =
        *(AnimationListNode**)(&manager[
            0x72DAD4 + sizeof(AnimationListNode*)]);
    assert(primaryHead->animation == primaryFront);
    assert(primaryTail->animation == pooled);

    AnimationObject* secondaryBack =
        AnimationManager_AllocateObject(&manager[0]);
    int secondaryBackHandle = AnimationManager_RegisterObjectAt(
        &manager[0], secondaryBack, AnimationManagerList_Secondary,
        AnimationListInsertion_Back);
    AnimationObject* secondaryFront =
        AnimationManager_AllocateObject(&manager[0]);
    int secondaryFrontHandle = AnimationManager_RegisterObjectAt(
        &manager[0], secondaryFront, AnimationManagerList_Secondary,
        AnimationListInsertion_Front);
    AnimationListNode** secondaryHead =
        (AnimationListNode**)(&manager[
            0x72DAD4 + 2 * sizeof(AnimationListNode*)]);
    AnimationListNode** secondaryTail =
        (AnimationListNode**)(&manager[
            0x72DAD4 + 3 * sizeof(AnimationListNode*)]);
    assert((*secondaryHead)->animation == secondaryFront);
    assert((*secondaryTail)->animation == secondaryBack);
    assert(AnimationManager_Find(
               &manager[0], secondaryBackHandle) == secondaryBack);

    AnimationManager_RemoveObject(&manager[0], secondaryFront);
    assert((*secondaryHead)->animation == secondaryBack);
    assert((*secondaryTail)->animation == secondaryBack);
    assert(AnimationManager_Find(
               &manager[0], secondaryFrontHandle) == 0);

    AnimationManager_MarkForRemovalAndClearHandle(
        &manager[0], &primaryFrontHandle);
    assert(primaryFrontHandle == 0);
    assert((*(unsigned int*)((unsigned char*)primaryFront + 0x35C) &
            0x04000000u) != 0);
}

static void TestAnimationFrameLoops() {
    const unsigned int managerSize = 0x732458;
    std::vector<unsigned char> manager(managerSize, 0);
    g_pGameStateManager = &manager[0];
    scriptResult = 0;
    updateCallbacks = 0;
    drawCallbacks = 0;
    renderedObjects = 0;

    AnimationObject* first = AnimationManager_AllocateObject(&manager[0]);
    AnimationObject* removed = AnimationManager_AllocateObject(&manager[0]);
    AnimationObject* third = AnimationManager_AllocateObject(&manager[0]);
    AnimationManager_RegisterObjectAt(
        &manager[0], first, AnimationManagerList_Primary,
        AnimationListInsertion_Back);
    AnimationManager_RegisterObjectAt(
        &manager[0], removed, AnimationManagerList_Primary,
        AnimationListInsertion_Back);
    AnimationManager_RegisterObjectAt(
        &manager[0], third, AnimationManagerList_Primary,
        AnimationListInsertion_Back);
    *RenderBucketSlot(first) = 0;
    *RenderBucketSlot(removed) = 1;
    *RenderBucketSlot(third) = 2;
    SetCallbacks(first);
    SetCallbacks(removed);
    SetCallbacks(third);
    *(unsigned int*)((unsigned char*)removed + 0x35C) |= 0x04000000u;

    assert(AnimationManager_UpdatePrimary(&manager[0]) == 1);
    assert(updateCallbacks == 2);
    assert(*(unsigned int*)(&manager[0x64]) == 3);
    assert(manager[0x3AC068 + 1] == 0);

    AnimationObject* bucketZeroSentinel =
        (AnimationObject*)(&manager[0] + 0x72DAE4);
    AnimationObject* bucketTwoSentinel =
        (AnimationObject*)(&manager[0] + 0x72DAE4 + 2 * 0x3AC);
    assert(*RenderChainSlot(bucketZeroSentinel) == first);
    assert(*RenderChainSlot(first) == 0);
    assert(*RenderChainSlot(bucketTwoSentinel) == third);

    AnimationManager_RenderBucket(&manager[0], 0);
    AnimationManager_RenderBucket(&manager[0], 2);
    assert(drawCallbacks == 2);
    assert(renderedObjects == 2);

    AnimationObject* secondaryFirst =
        AnimationManager_AllocateObject(&manager[0]);
    AnimationObject* secondarySecond =
        AnimationManager_AllocateObject(&manager[0]);
    AnimationManager_RegisterObjectAt(
        &manager[0], secondaryFirst, AnimationManagerList_Secondary,
        AnimationListInsertion_Back);
    AnimationManager_RegisterObjectAt(
        &manager[0], secondarySecond, AnimationManagerList_Secondary,
        AnimationListInsertion_Back);
    SetCallbacks(secondaryFirst);
    SetCallbacks(secondarySecond);
    assert(AnimationManager_UpdateSecondary(&manager[0]) == 1);
    assert(*(unsigned int*)(&manager[0x64]) == 2);
    AnimationObject* bucketNineteenSentinel =
        (AnimationObject*)(&manager[0] + 0x72DAE4 + 19 * 0x3AC);
    assert(*RenderChainSlot(bucketNineteenSentinel) == secondaryFirst);
    assert(*RenderChainSlot(secondaryFirst) == secondarySecond);
    assert(*RenderChainSlot(secondarySecond) == 0);
    AnimationManager_RenderBucket(&manager[0], 19);
    assert(drawCallbacks == 4);
    assert(renderedObjects == 4);

    scriptResult = 1;
}

static void TestAnimationManagerLifecycle() {
    const unsigned int managerSize = 0x732460;
    std::vector<unsigned char> manager(managerSize, 0xA5);
    entityInitializations = 0;
    entityDestructions = 0;

    AnimationManager_InitializeStorage(&manager[0]);
    assert(entityInitializations == 0x1000);
    assert(*(int*)(&manager[0]) == -1);
    assert(*(int*)(&manager[4]) == -1);
    assert(*(unsigned int*)(&manager[0x3ADA60]) == 1);
    assert(manager[0x3ADA6C] == 0xFF);
    assert(*(AnimationListNode**)(&manager[0x72DAD4]) == 0);
    assert(*(unsigned int*)(&manager[0x3AD068]) == 0);

    AnimationObject* primary = AnimationManager_AllocateObject(&manager[0]);
    AnimationObject* secondary = AnimationManager_AllocateObject(&manager[0]);
    AnimationManager_RegisterObjectAt(
        &manager[0], primary, AnimationManagerList_Primary,
        AnimationListInsertion_Back);
    AnimationManager_RegisterObjectAt(
        &manager[0], secondary, AnimationManagerList_Secondary,
        AnimationListInsertion_Back);

    void** primaryResource = (void**)((unsigned char*)primary + 0x35C -
                                      sizeof(void*));
    void** unusedPoolResource = (void**)(&manager[0] + 0x68 + 10 * 0x3AC +
                                         0x35C - sizeof(void*));
    void** sentinelResource = (void**)(&manager[0] + 0x72DAE4 +
                                       0x35C - sizeof(void*));
    *primaryResource = std::malloc(1);
    *unusedPoolResource = std::malloc(1);
    *sentinelResource = std::malloc(1);
    *(void**)(&manager[0x3AD488]) = std::malloc(1);

    AnimationManager_DestroyStorage(&manager[0]);
    assert(entityInitializations == 0x1002);
    assert(entityDestructions == 0x1000 + 20);
    assert(*(AnimationListNode**)(&manager[0x72DAD4]) == 0);
    assert(*(AnimationListNode**)(&manager[
        0x72DAD4 + 2 * sizeof(AnimationListNode*)]) == 0);
    assert(manager[0x3AC068] == 0);
    assert(manager[0x3AC068 + 1] == 0);
    assert(*(void**)(&manager[0x3AD488]) == 0);
    assert(*primaryResource == 0);
    assert(*unusedPoolResource == 0);
    assert(*sentinelResource == 0);
}

int main() {
    TestFrameTimer();
    TestAnimationLookupAndPosition();
    TestAnimationFrameLoops();
    TestAnimationManagerLifecycle();
    return 0;
}
