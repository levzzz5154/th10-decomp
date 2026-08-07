#include "th10/math/timer.hpp"
#include "th10/math/vector.hpp"
#include "th10/math/rng.hpp"
#include "th10/math/angle.hpp"
#include "th10/math/easing.hpp"
#include "th10/math/random_vector.hpp"
#include "th10/game/menu.hpp"
#include "th10/game/progress.hpp"
#include "th10/render/animation_manager.hpp"
#include "th10/game/stage_text.hpp"

// Retail globals read by the 0x00408D60 wrapper (non-MSVC branch).
unsigned int DAT_004776e8 = 0;
unsigned int DAT_00477834 = 0;
unsigned int DAT_00477704 = 0;

#include <cassert>
#include <cstring>
#include <vector>
#include <cstdlib>

// Retail scheduler global; the PE32 build gets it from the aliased .data,
// the host test build has to supply storage.
uint32_t DAT_00491be4;

float _DAT_00470afc = 1.0f;
float _DAT_00470b68 = 0.99f;
float _DAT_00470b64 = 1.01f;
float _DAT_00470b48 = 10.0f;
float _DAT_00470b4c = 20.0f;
float _DAT_00470b60 = 0.5f;
float DAT_00470b04 = 0.0f;
float DAT_00470b38 = 448.0f;
float DAT_00470b3c = 192.0f;
float DAT_00470b40 = -192.0f;
float _DAT_00470b98 = 4294967296.0f;
float _DAT_00470bec = 4.6566128730773926e-10f;
float _DAT_00470bf0 = 2.3283064365386963e-10f;
float DAT_00470b10 = -3.1415927f;
float DAT_00470b14 = 6.2831855f;
float DAT_00470b18 = 3.1415927f;

unsigned int DAT_00492274;
unsigned char DAT_0049231c;

extern "C" void __stdcall EnterCriticalSection(void*) {}
extern "C" void __stdcall LeaveCriticalSection(void*) {}

void* PTR_LAB_0046dab0 = (void*)0x1234;
void* PTR_LAB_0046da60 = (void*)0x5678;

int Position_IsPartiallyInViewport(const void* center, float radius_x,
                                    float radius_y);
unsigned int DAT_00476f78;
void* g_pGameStateManager;
void* g_pD3DDevice = (void*)0x1234;
static int entityInitializations;
static int entityDestructions;
static unsigned int textureWidth;
static unsigned int textureHeight;
static unsigned int textureFormat;
static unsigned int textureMipLevels;
static unsigned int textureUsage;
static unsigned int texturePool;

extern "C" int __stdcall D3DXCreateTexture(
        void* device, unsigned int width, unsigned int height,
        unsigned int mip_levels, unsigned int usage, unsigned int format,
        unsigned int pool, void* output) {
    assert(device == g_pD3DDevice);
    textureWidth = width;
    textureHeight = height;
    textureMipLevels = mip_levels;
    textureUsage = usage;
    textureFormat = format;
    texturePool = pool;
    *(unsigned int*)output = 0xAABBCCDD;
    return -1;
}

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
int AnimationObject_ExecuteScript(AnimationObject*) {
    ++scriptRuns;
    return scriptResult;
}

static int renderedObjects;
void AnimationObject_Render(void*, AnimationObject*) {
    ++renderedObjects;
}

static int updateCallbacks;
static int drawCallbacks;
static AnimationObject* selectedSpriteObject;
static void* selectedSpriteResource;
static int selectedSpriteIndex;

static int UpdateCallback(AnimationObject*) {
    ++updateCallbacks;
    return 0;
}

static int DrawCallback(AnimationObject*) {
    ++drawCallbacks;
    return 0;
}

static int SelectSprite(
    AnimationObject* animation, void* resource, int spriteIndex) {
    selectedSpriteObject = animation;
    selectedSpriteResource = resource;
    selectedSpriteIndex = spriteIndex;
    return 73;
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
    assert(timer.elapsed > -2.26f && timer.elapsed < -2.24f);
}

static void TestAnimationColorMultiplyChannel() {
    assert(AnimationColor_MultiplyChannel(0, 255) == 0);
    assert(AnimationColor_MultiplyChannel(64, 128) == 64);
    assert(AnimationColor_MultiplyChannel(128, 128) == 128);
    assert(AnimationColor_MultiplyChannel(255, 255) == 255);
    assert(AnimationColor_MultiplyChannel(0x12345680, 0xABCDEF40) == 64);
}

static void TestAnimationTextureCreate() {
    static const unsigned int formats[6] = {0, 21, 25, 23, 20, 26};
    static const unsigned int strides[6] = {4, 4, 2, 2, 3, 2};
    for (unsigned int index = 0; index != 6; ++index) {
        AnimationTextureRecord record = {};
        assert(AnimationTexture_Create(320, 240, index, &record) == 0);
        assert(record.texture == 0xAABBCCDD);
        assert(record.bytes_per_pixel == strides[index]);
        assert(textureWidth == 320 && textureHeight == 240);
        assert(textureMipLevels == 1 && textureUsage == 0);
        assert(textureFormat == formats[index] && texturePool == 1);
    }
}

static void TestAnimationPositionRecordCopy() {
    std::vector<unsigned char> manager(0x200, 0);
    const float source[17] = {1.0f, 2.0f, 10.0f, 6.0f, 18.0f, 12.0f,
        3.0f, 9.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
        4.0f, 6.0f, 0.0f};
    AnimationManager_CopyPositionRecord(manager.data(), 0, source);
    const float* record = (const float*)(manager.data() + 0x118);
    assert(record[0] == 1.0f && record[5] == 12.0f);
    assert(record[8] == 10.0f / 9.0f);
    assert(record[9] == 2.0f && record[10] == 2.0f && record[11] == 4.0f);
    assert(record[12] == 1.0f && record[13] == 2.0f);
}

static void TestStageTextSkipLine() {
    char text[] = "first\r\n\nsecond";
    int remaining = sizeof(text) - 1;
    char* second = StageText_SkipLine(text, &remaining);
    assert(second == text + 8);
    assert(remaining == (int)(sizeof(text) - 1 - 8));

    char unterminated[] = {'a', 'b', 'c'};
    remaining = 3;
    assert(StageText_SkipLine(unterminated, &remaining) == unterminated + 3);
    assert(remaining == 0);

    remaining = 0;
    assert(StageText_SkipLine(text, &remaining) == text);
}

static void TestStageTextInitialize() {
    StageTextState state = {};
    const float first[3] = {1.0f, 2.0f, 3.0f};
    const float second[3] = {4.0f, 5.0f, 6.0f};
    const float defaults[3] = {0.25f, 0.5f, 0.75f};
    StageText_Initialize(&state, first, second, 9, 3, defaults);
    assert(state.resource == 9 && state.mode == 3);
    assert(state.first[2] == 3.0f && state.second[0] == 4.0f);
    assert(state.defaults_b[1] == 0.5f && state.selection == -1);
}

static void TestAnimationScriptVariables() {
    unsigned char storage[0x3AC] = {};
    AnimationObject* animation = (AnimationObject*)storage;
    int integerFallback = 91;
    float floatFallback = 3.5f;

    int* integerVariable = AnimationObject_ResolveIntegerVariable(
        animation, 10000, &integerFallback, true);
    *integerVariable = 42;
    assert(integerVariable == (int*)(storage + 0x30C));
    assert(AnimationObject_ReadIntegerVariable(animation, 10000) == 42);

    int* extraIntegerVariable = AnimationObject_ResolveIntegerVariable(
        animation, 10009, &integerFallback, true);
    *extraIntegerVariable = -17;
    assert(extraIntegerVariable == (int*)(storage + 0x330));
    assert(AnimationObject_ReadIntegerVariable(animation, 10009) == -17);

    float* floatVariable = AnimationObject_ResolveFloatVariable(
        animation, 10004, &floatFallback, true);
    *floatVariable = 7.75f;
    assert(floatVariable == (float*)(storage + 0x31C));
    assert(AnimationObject_ReadIntegerVariable(animation, 10004) == 7);

    float* basePositionVariable = AnimationObject_ResolveFloatVariable(
        animation, 10015, &floatFallback, true);
    *basePositionVariable = -2.0f;
    assert(basePositionVariable == (float*)(storage + 0x33C));
    assert(*(float*)(storage + 0x33C) == -2.0f);

    assert(AnimationObject_ResolveIntegerVariable(
               animation, 10000, &integerFallback, false) ==
           &integerFallback);
    assert(AnimationObject_ResolveIntegerVariable(
               animation, 12345, &integerFallback, true) ==
           &integerFallback);
    assert(AnimationObject_ResolveFloatVariable(
               animation, 10004, &floatFallback, false) ==
           &floatFallback);
    assert(AnimationObject_ResolveFloatVariable(
               animation, 12345, &floatFallback, true) ==
           &floatFallback);
    assert(AnimationObject_ReadIntegerVariable(animation, 12345) == 12345);
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
    int secondHandle = 29;
    AnimationManager_SetStopFrameFromHandle(
        &manager[0], &secondHandle, 14);
    assert(*(short*)(secondStorage + 0x304) == 14);
    AnimationManager_StopAtFrame2(&secondHandle);
    assert(*(short*)(secondStorage + 0x304) == 2);
    AnimationManager_StopAtFrame3(&secondHandle);
    assert(*(short*)(secondStorage + 0x304) == 3);
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

    selectedSpriteObject = 0;
    selectedSpriteResource = 0;
    assert(AnimationManager_SelectSpriteFromCurrentResource(
               &manager[0], &secondHandle, 6, SelectSprite) == 73);
    assert(selectedSpriteObject == second);
    assert(selectedSpriteResource == (void*)0xCAFE);
    assert(selectedSpriteIndex == 6);
    assert(AnimationManager_SelectSpriteFromResource(
               &manager[0], &secondHandle, (void*)0xBEEF, 9,
               SelectSprite) == 73);
    assert(selectedSpriteResource == (void*)0xBEEF);
    assert(selectedSpriteIndex == 9);
    int missingSpriteHandle = 404;
    assert(AnimationManager_SelectSpriteFromCurrentResource(
               &manager[0], &missingSpriteHandle, 0, SelectSprite) == -1);

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

    stateScripts[3] = (void*)0x8765;
    *(float*)(firstStorage + 0x3C) = 12.0f;
    *(unsigned int*)(firstStorage + 0x35C) = 0x200u;
    *(int*)(firstStorage + 0xB4) = 5;
    *(int*)(firstStorage + 0x22C) = 6;
    int scriptRunsBeforeChange = scriptRuns;
    int firstHandle = 17;
    AnimationManager_ChangeScript(&manager[0], &firstHandle, 3);
    assert(*(short*)(firstStorage + 0x38A) == 3);
    assert(*(float*)(firstStorage + 0x3C) == 6.0f);
    assert((*(unsigned int*)(firstStorage + 0x35C) & 0x200u) == 0);
    assert((*(unsigned int*)(firstStorage + 0x35C) & 0xFFFFu) == 6u);
    assert(*(int*)(firstStorage + 0x2FC) == -1);
    assert(*(int*)(firstStorage + 0xB4) == 0);
    assert(*(int*)(firstStorage + 0x22C) == 0);
    assert(*(unsigned short*)(firstStorage + 0x386) == 9);
    assert(scriptRuns == scriptRunsBeforeChange + 1);
    int entityInitializationsAfterChange = entityInitializations;

    stateScripts[1] = 0;
    AnimationManager_ChangeScript(&manager[0], &firstHandle, 1);
    assert(*(short*)(firstStorage + 0x38A) == 3);
    assert(scriptRuns == scriptRunsBeforeChange + 1);
    int absentHandle = 404;
    AnimationManager_ChangeScript(&manager[0], &absentHandle, 3);
    assert(scriptRuns == scriptRunsBeforeChange + 1);
    assert(entityInitializations == entityInitializationsAfterChange);

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

    const float positioned[3] = {7.0f, 8.0f, 9.0f};
    int createdPrimaryBack = AnimationManager_CreatePrimaryBack(
        &manager[0], resource, 0x1B9, 3);
    int createdPrimaryFront = AnimationManager_CreatePrimaryFront(
        &manager[0], resource, 0x1B9, 4);
    int createdSecondaryBack = AnimationManager_CreateSecondaryBack(
        &manager[0], resource, 0x1B9, 5);
    int createdSecondaryFront = AnimationManager_CreateSecondaryFront(
        &manager[0], resource, 0x1B9, 6);
    int createdPositioned = AnimationManager_CreatePositionedPrimary(
        &manager[0], resource, 0x1B9, positioned);
    assert(createdPrimaryBack != 0);
    assert(createdPrimaryFront != 0);
    assert(createdSecondaryBack != 0);
    assert(createdSecondaryFront != 0);
    assert(createdPositioned != 0);
    assert(*RenderBucketSlot(AnimationManager_Find(
               &manager[0], createdPrimaryBack)) == 3);
    assert(*RenderBucketSlot(AnimationManager_Find(
               &manager[0], createdPrimaryFront)) == 4);
    assert(*RenderBucketSlot(AnimationManager_Find(
               &manager[0], createdSecondaryBack)) == 5);
    assert(*RenderBucketSlot(AnimationManager_Find(
               &manager[0], createdSecondaryFront)) == 6);
    const float* positionedStored = (const float*)((unsigned char*)
        AnimationManager_Find(&manager[0], createdPositioned) + 0x340);
    assert(positionedStored[0] == positioned[0]);
    assert(positionedStored[1] == positioned[1]);
    assert(positionedStored[2] == positioned[2]);
    const int createdHandles[5] = {
        createdPrimaryBack, createdPrimaryFront, createdSecondaryBack,
        createdSecondaryFront, createdPositioned
    };
    for (int index = 0; index != 5; ++index) {
        AnimationManager_RemoveObject(
            &manager[0], AnimationManager_Find(
                &manager[0], createdHandles[index]));
    }

    int scriptRunsBeforePlayer = scriptRuns;
    int playerHandle = PlayerAnimation_Create(
        resource, scratch, 0x1B9, playerPosition);
    assert(playerHandle == 7);
    assert(scratch[0] == playerHandle);
    assert(scriptRuns == scriptRunsBeforePlayer + 1);
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

static void TestAnimationResourceConfiguration() {
    unsigned char object[0x3AC] = {};
    unsigned char resource[0x180] = {};
    unsigned char records[0x44] = {};
    *(unsigned int*)(resource + 0x108) = 1;
    *(unsigned char**)(resource + 0x118) = records;
    *(float*)(records + 0x18) = 2.0f;
    *(float*)(records + 0x1C) = 4.0f;
    *(float*)(records + 0x30) = 20.0f;
    *(float*)(records + 0x34) = 10.0f;
    *(float*)(records + 0x38) = 8.0f;
    *(float*)(records + 0x3C) = 6.0f;
    assert(AnimationObject_ConfigureFromResource(object, resource, 0) == 0);
    assert(*(short*)(object + 0x384) == 0);
    assert(*(void**)(object + 0x308) == resource);
    assert(*(float*)(object + 0x4C) == 10.0f);
    assert(*(float*)(object + 0x50) == 20.0f);
    assert(*(float*)(object + 0x2BC) == 20.0f);
    assert(*(float*)(object + 0x2D0) == 60.0f);
    *(unsigned int*)(resource + 0x124) = 1;
    assert(AnimationObject_ConfigureFromResource(object, resource, 0) == -1);
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

static void TestAnimationDigitTriplet();
static void TestVector2PolarLeaf();
static void TestAnimationResourceSlotClear();
static void TestGameStateTimerTarget();
static void TestGameStateDisableTimerWithOwner();
static void TestFrameTimerAdvance();
static void TestPositionInViewport();
static void TestRngSequence();
static void TestAngleNormalize();
static void TestMenuCursorAdvance();
static void TestGameProgressRecords();
static void TestEasingEvaluate();
static void TestAnimationResourceBatchRelease();
static void TestRandomVectorAndEmbeddedTimer();

int main() {
    TestFrameTimer();
    TestAnimationColorMultiplyChannel();
    TestAnimationTextureCreate();
    TestAnimationPositionRecordCopy();
    TestStageTextSkipLine();
    TestStageTextInitialize();
    TestAnimationScriptVariables();
    TestAnimationLookupAndPosition();
    TestAnimationResourceConfiguration();
    TestAnimationFrameLoops();
    TestAnimationManagerLifecycle();
    TestAnimationDigitTriplet();
    TestVector2PolarLeaf();
    TestAnimationResourceSlotClear();
    TestGameStateTimerTarget();
    TestGameStateDisableTimerWithOwner();
    TestFrameTimerAdvance();
    TestPositionInViewport();
    TestRngSequence();
    TestAngleNormalize();
    TestMenuCursorAdvance();
    TestGameProgressRecords();
    TestEasingEvaluate();
    TestAnimationResourceBatchRelease();
    TestRandomVectorAndEmbeddedTimer();
    return 0;
}

static int g_digit_calls[3];
static int g_digit_count;
static int CaptureDigit(void*, int value) {
    g_digit_calls[g_digit_count++] = value;
    return 0;
}
static void TestAnimationDigitTriplet() {
    g_digit_count = 0;
    AnimationManager_ConfigureDigitTriplet((void*)1, 3, 47, CaptureDigit);
    assert(g_digit_count == 3);
    assert(g_digit_calls[0] == 3 && g_digit_calls[1] == 12 &&
           g_digit_calls[2] == 15);
}

static void TestVector2PolarLeaf() {
    Vector2 value = {};
    Vector2_SetPolar(&value, 1.57079632679f, 2.0f);
    assert(value.x > -0.001f && value.x < 0.001f);
    assert(value.y > 1.999f && value.y < 2.001f);
}

static int g_slot_release_count;
static int g_slot_free_count;
static void SlotRelease(void*) { ++g_slot_release_count; }
static void SlotFree(void*) { ++g_slot_free_count; }
static void TestAnimationResourceSlotClear() {
    std::vector<unsigned char> manager(0x3AD100, 0);
    void** slot = (void**)(&manager[0x3AD06C + 4 * 32]);
    *slot = (void*)0x1234;
    g_slot_release_count = g_slot_free_count = 0;
    AnimationManager_ClearResourceSlot(&manager[0], 32, SlotRelease, SlotFree);
    assert(*slot == 0 && g_slot_release_count == 1 && g_slot_free_count == 1);
    AnimationManager_ClearResourceSlot(&manager[0], -1, SlotRelease, SlotFree);
    assert(g_slot_release_count == 1 && g_slot_free_count == 1);
}

static void TestPositionInViewport() {
    float center_on_screen[2] = {0.0f, 200.0f};
    assert(Position_IsPartiallyInViewport(center_on_screen, 50.0f, 50.0f) == 0);
    float center_near_left[2] = {-180.0f, 200.0f};
    assert(Position_IsPartiallyInViewport(center_near_left, 50.0f, 50.0f) == 0);
    float center_offscreen_left[2] = {-300.0f, 200.0f};
    assert(Position_IsPartiallyInViewport(center_offscreen_left, 50.0f, 50.0f) == 1);
    float center_offscreen_right[2] = {300.0f, 200.0f};
    assert(Position_IsPartiallyInViewport(center_offscreen_right, 50.0f, 50.0f) == 1);
    float center_offscreen_top[2] = {0.0f, -300.0f};
    assert(Position_IsPartiallyInViewport(center_offscreen_top, 50.0f, 50.0f) == 1);
    float center_offscreen_bottom[2] = {0.0f, 600.0f};
    assert(Position_IsPartiallyInViewport(center_offscreen_bottom, 50.0f, 50.0f) == 1);
    float center_edge[2] = {-100.0f, 0.0f};
    assert(Position_IsPartiallyInViewport(center_edge, 100.0f, 100.0f) == 0);
}

static void TestGameStateTimerTarget() {
    unsigned char state[0x300] = {};
    float speed = 1.0f;
    GameState_SetTimerTarget(state, 9, 27, &speed);
    assert(*(int*)(state + 0x20) == 9 && *(int*)(state + 0x2B0) == 26);
    assert(*(int*)(state + 0x2B4) == 0 && *(int*)(state + 0x2B8) == 0);
    assert((*(unsigned int*)(state + 0x2C0) & 1u) != 0);
}

static void TestGameStateDisableTimerWithOwner() {
    unsigned char state[0x300] = {};
    GameState_DisableTimerWithOwner(state, 7);
    assert(*(int*)(state + 0x1C) == 7 && *(int*)(state + 0x20) == 0);
    assert(*(int*)(state + 0x2B0) == -1);
    assert(*(int*)(state + 0x2B4) == 0 && *(int*)(state + 0x2B8) == 0);
    assert((*(unsigned int*)(state + 0x2C0) & 1u) != 0);
    // Re-call should leave the flags set and reset current/next/previous.
    *(int*)(state + 0x1C) = 0;
    *(int*)(state + 0x2B0) = 12;
    *(int*)(state + 0x2B4) = 99;
    GameState_DisableTimerWithOwner(state, 5);
    assert(*(int*)(state + 0x1C) == 5 && *(int*)(state + 0x2B0) == -1);
    assert(*(int*)(state + 0x2B4) == 0);
}

static void TestFrameTimerAdvance() {
    float speed = 1.0f;
    FrameTimer timer = {4, 5, 5.0f, &speed, 1};
    FrameTimer_Advance(&timer, -2.0f);
    assert(timer.previous == 5 && timer.current == 3 && timer.elapsed == 3.0f);
    speed = 2.0f;
    FrameTimer_Advance(&timer, 1.5f);
    assert(timer.previous == 3 && timer.current == 6 && timer.elapsed == 6.0f);
}

// Retail generator sequence from a zero seed, computed from the verified
// 16-bit LCG steps (XOR 0x9630, subtract 0x6553, multiply-and-fold).
static void TestRngSequence() {
    RngState state = {0, 0, 0};
    assert(Rng_NextU32(&state) == 0xC374BFC7u);
    assert(state.seed == 0xBFC7 && state.generation == 2);
    assert(Rng_NextU32(&state) == 0x12937D40u);
    assert(state.seed == 0x7D40 && state.generation == 4);
    assert(Rng_NextU32(&state) == 0x1876A3CCu);
    assert(state.generation == 6);

    RngState floatState = {0, 0, 0};
    unsigned int bits = 0;
    float value = Rng_NextFloat(&floatState);
    std::memcpy(&bits, &value, sizeof(bits));
    assert(bits == 0x3F4374C0u);  // 0.7635002 in [0, 1)
    assert(floatState.generation == 2);
    value = Rng_NextFloat(&floatState);
    std::memcpy(&bits, &value, sizeof(bits));
    assert(bits == 0x3D949BEAu);  // 0.0725630 in [0, 1)

    RngState signedState = {0, 0, 0};
    value = Rng_NextFloatSigned(&signedState);
    std::memcpy(&bits, &value, sizeof(bits));
    assert(bits == 0x3F06E980u);  // 0.5270004 in [-1, 1)
    value = Rng_NextFloatSigned(&signedState);
    std::memcpy(&bits, &value, sizeof(bits));
    assert(bits == 0xBF5AD906u);  // -0.8548740 in [-1, 1)

    // The double-step leaf returns the first pair while advancing four steps.
    RngState doubleState = {0, 0, 0};
    assert(Rng_NextU32DoubleStep(&doubleState) == 0xC374BFC7u);
    assert(doubleState.seed == 0x7D40 && doubleState.generation == 4);
}

static void TestAngleNormalize() {
    // Values already inside [-pi, pi] pass through unchanged.
    assert(Angle_Normalize(1.5f) == 1.5f);
    assert(Angle_Normalize(-3.1415927f) == -3.1415927f);
    // Positive overflow folds by 2*pi per pass.
    float wrapped = Angle_Normalize(3.1415927f * 4.0f);
    assert(wrapped > -0.0001f && wrapped < 0.0001f);
    wrapped = Angle_NormalizeSum(3.0f, 1.0f);
    assert(wrapped > -2.2833f && wrapped < -2.2831f);
    // Negative overflow folds upward.
    wrapped = Angle_Normalize(-3.1415927f * 1.5f);
    assert(wrapped > 1.5707f && wrapped < 1.5709f);
    // The shared 0x20 iteration cap keeps huge inputs bounded.
    assert(Angle_Normalize(1.0e30f) > 1.0e29f);
    assert(Angle_Normalize(-1.0e30f) < -1.0e29f);
}

static void TestMenuCursorAdvance() {
    MenuCursor cursor = {};
    cursor.itemCount = 5;
    cursor.wrap = 1;
    cursor.value = 1;
    assert(MenuCursor_Advance(&cursor, 1) == 2);
    // Wrap past the last item back to the first.
    cursor.value = 4;
    assert(MenuCursor_Advance(&cursor, 1) == 0);
    // Wrap below the first item up to the last.
    cursor.value = 0;
    assert(MenuCursor_Advance(&cursor, -1) == 4);
    // Clamp mode stops at the edges instead of wrapping.
    cursor.wrap = 0;
    cursor.value = 4;
    assert(MenuCursor_Advance(&cursor, 1) == 4);
    cursor.value = 0;
    assert(MenuCursor_Advance(&cursor, -1) == 0);
    // Skipped positions are bypassed with another step in the same direction.
    cursor.wrap = 1;
    cursor.skipValues[0] = 2;
    cursor.skipCount = 1;
    cursor.value = 1;
    assert(MenuCursor_Advance(&cursor, 1) == 3);
    cursor.value = 3;
    assert(MenuCursor_Advance(&cursor, -1) == 1);
    // Consecutive skips keep advancing until a free position is found.
    cursor.skipValues[1] = 3;
    cursor.skipCount = 2;
    cursor.value = 1;
    assert(MenuCursor_Advance(&cursor, 1) == 4);
    // A skip right after the wrap boundary is bypassed too.
    cursor.itemCount = 3;
    cursor.skipValues[0] = 0;
    cursor.skipCount = 1;
    cursor.value = 2;
    assert(MenuCursor_Advance(&cursor, 1) == 1);
    // An empty list never moves the cursor.
    cursor.itemCount = 0;
    cursor.skipCount = 0;
    cursor.value = 7;
    assert(MenuCursor_Advance(&cursor, 1) == 7);
}

static void TestGameProgressRecords() {
    std::vector<unsigned char> progress(0x1D892, 0);
    assert(GameProgress_HasAnyPlayRecord(&progress[0]) == 0);
    // Bytes outside the six checked flags do not count as a record.
    progress[0x1D882] = 1;
    progress[0x1D88E] = 1;
    assert(GameProgress_HasAnyPlayRecord(&progress[0]) == 0);
    for (int index = 0; index < 6; ++index) {
        std::vector<unsigned char> single(0x1D892, 0);
        single[0x1D888 + index] = 1;
        assert(GameProgress_HasAnyPlayRecord(&single[0]) == 1);
    }

    GameProgress_UnlockAllStages(&progress[0]);
    for (int index = 0; index < 16; ++index)
        assert(progress[0x1D882 + index] == 1);
    for (int table = 0; table < 6; ++table) {
        unsigned int base = 0x4E9 + table * 0x437C;
        for (int stage = 0; stage < 6; ++stage)
            assert(progress[base + stage * 8] == 1);
        // Untouched neighbors stay clear.
        assert(progress[base + 1] == 0);
        assert(progress[base + 6 * 8] == 0);
    }
}

static void TestEasingEvaluate() {
    assert(Easing_Evaluate(1, 1.0f, 2.0f) == 0.25f);
    assert(Easing_Evaluate(2, 1.0f, 2.0f) == 0.125f);
    assert(Easing_Evaluate(3, 1.0f, 2.0f) == 0.0625f);
    assert(Easing_Evaluate(4, 0.5f, 1.0f) == 0.75f);
    assert(Easing_Evaluate(5, 0.5f, 1.0f) == 0.875f);
    assert(Easing_Evaluate(6, 0.5f, 1.0f) == 0.9375f);
    assert(Easing_Evaluate(9, 0.25f, 1.0f) == 0.125f);
    assert(Easing_Evaluate(9, 0.75f, 1.0f) == 0.875f);
    assert(Easing_Evaluate(12, 0.25f, 1.0f) == 0.375f);
    assert(Easing_Evaluate(12, 0.75f, 1.0f) == 0.625f);
    assert(Easing_Evaluate(15, 3.0f, 4.0f) == 0.0f);
    assert(Easing_Evaluate(16, 3.0f, 4.0f) == 1.0f);
    assert(Easing_Evaluate(0, 3.0f, 4.0f) == 0.75f);
}

static int g_batch_prepare;
static int g_batch_releases;
static int g_batch_frees;
static void BatchPrepare(void*, void*) { ++g_batch_prepare; }
static void BatchRelease(void*) { ++g_batch_releases; }
static void BatchFree(void*) { ++g_batch_frees; }

static void TestAnimationResourceBatchRelease() {
    AnimationResourceBatchEntry entries[2] = {
        {(void*)1, (void*)2}, {(void*)3, (void*)4}
    };
    AnimationResourceBatch batch = {
        (void*)5, entries, 2, (void*)6, (void*)7, (void*)8
    };
    g_batch_prepare = g_batch_releases = g_batch_frees = 0;
    AnimationManager_ReleaseResourceBatch(&batch, (void*)9, BatchPrepare,
                                          BatchRelease, BatchFree);
    assert(g_batch_prepare == 1 && g_batch_releases == 2 &&
           g_batch_frees == 6 && batch.active == 0 && batch.entries == 0 &&
           batch.auxiliary_a == 0 && batch.auxiliary_b == 0 &&
           batch.auxiliary_c == 0 && entries[0].resource == 0 &&
           entries[1].allocation == 0);
    AnimationManager_ReleaseResourceBatch(&batch, (void*)9, BatchPrepare,
                                          BatchRelease, BatchFree);
    assert(g_batch_prepare == 1 && g_batch_frees == 6);
}

static void TestRandomVectorAndEmbeddedTimer() {
    int lanes[3] = {0, 0, 0};
    RandomVector_StoreRoundedScalar(lanes, 2.49);
    assert(lanes[0] == 2 && lanes[1] == 2 && lanes[2] == 2);
    RandomVector_StoreRoundedScalar(lanes, -2.51);
    assert(lanes[0] == -3 && lanes[1] == -3 && lanes[2] == -3);

    float speed = 1.0f;
    EmbeddedTimerState timer = {7, 8, 9, 0, 0};
    EmbeddedTimer_Reset(&timer, &speed);
    assert(timer.target == -1 && timer.current == 0 && timer.previous == 0 &&
           timer.speed == &speed && (timer.flags & 1u) != 0);
    timer.target = 42;
    EmbeddedTimer_Reset(&timer, &speed);
    assert(timer.target == -1 && timer.current == 0 && timer.previous == 0);
}
