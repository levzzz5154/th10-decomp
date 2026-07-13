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

struct Entity;

extern "C" void* operator_new(unsigned int size) {
    return std::malloc(size);
}

Entity* Entity_Constructor(Entity* entity) {
    return entity;
}

void Entity_Init(void*, Entity*) {}

static int scriptRuns;
void FUN_0043ee30(AnimationObject*) { ++scriptRuns; }

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
    unsigned char firstStorage[0x360] = {};
    unsigned char secondStorage[0x360] = {};
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
    assert(scriptRuns == 1);
    AnimationObject* playerAnimation =
        AnimationManager_Find(&manager[0], playerHandle);
    assert(playerAnimation != 0);
    const float* translated =
        (const float*)((unsigned char*)playerAnimation + 0x340);
    assert(translated[0] == 22.0f);
    assert(translated[1] == 13.0f);
    assert(translated[2] == 4.0f);
}

int main() {
    TestFrameTimer();
    TestAnimationLookupAndPosition();
    return 0;
}
