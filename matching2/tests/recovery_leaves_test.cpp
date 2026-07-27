#include "th10/game/recovery_leaves.hpp"

#include <cassert>
#include <cstdlib>
#include <cstring>

// recovery_leaves.cpp publishes the large-state instance here. The PE32
// build aliases it from retail .data; the host test build supplies storage.
unsigned int DAT_00477830;

static int g_calls;
static int g_frees;
static RecoveryByte g_opcode;
static float g_value;
static void CountCall() { ++g_calls; }
static void Destroy(void*) { ++g_calls; }
static void Free(void*) { ++g_frees; }
static void Forward(RecoveryByte opcode, float value) {
    g_opcode = opcode; g_value = value;
}
static int Invoke(void* object, RecoveryWord first, RecoveryWord second) {
    assert(object == (void*)0x1234 && first == 7 && second == 11);
    return 37;
}
static RecoveryWord First(void* object) {
    return object == (void*)1 ? 1 : 4;
}
static RecoveryWord Second(void*, int value) {
    assert(value == 0);
    return 2;
}
static RecoveryWord Query(void* object, RecoveryWord argument) {
    assert(argument == 0);
    return object == (void*)1 ? 1u : 4u;
}
static RecoveryWord interfaceStates[3];
static void ReadState(void* object, RecoveryWord* state) {
    *state = interfaceStates[(unsigned long)object - 1];
}
static RecoveryWord PickIndex(RecoveryWord count) {
    assert(count == 3);
    return 1;
}
static int cleanupCalls;
static int freedNodes;
static void CleanupNode(RecoveryCleanupNode*) { ++cleanupCalls; }
static void FreeNode(void* node) {
    ++freedNodes;
    delete (RecoveryCleanupNode*)node;
}
static int updateCalls;
static int pollCalls;
static RecoveryWord seekOffset;
static int BeginInterface(void*) { ++updateCalls; return 0; }
static int PollInterface(void*) {
    ++pollCalls;
    return pollCalls == 1 ? (int)0x88780096u : 0;
}
static void SleepInterface(unsigned milliseconds) { assert(milliseconds == 10); }
static void SeekStream(RecoveryWord offset) { seekOffset = offset; }
static unsigned long long PairResult(void* value) {
    return (unsigned long long)(unsigned long)value + 0x100000000ull;
}
static int deadline;
static RecoveryWord RandomValue(void*) { return 7000; }
static void SetDeadline(int value) { deadline = value; }
static RecoveryWord RoundedRandom(void*) { return 42; }
static int transitionCalls;
static void Transition(void*) { ++transitionCalls; }
static RecoveryWord ColorRandom(void* state) {
    return ++*(RecoveryWord*)state;
}
static RecoveryWord configuredFlags[2];
static void Configure(void* resource, RecoveryWord flags) {
    configuredFlags[(unsigned long)resource - 1] = flags;
}
static int subobjectCalls;
static void InitializeSubobject(void*) { ++subobjectCalls; }
static int tickCalls;
static void Tick() { ++tickCalls; }
static int loadMode;
static void* LoadResource(void*, int index, const char*) {
    if (loadMode == index) return 0;
    return (void*)(unsigned long)(index + 10);
}
static const char* missingResource;
static void ReportMissing(const char* name) { missingResource = name; }
static int animationCreates;
static RecoveryWord storedAnimationResource;
static void* CreateAnimation() { ++animationCreates; return (void*)0x99; }
static void ConfigureAnimation(void* object, int index) {
    assert(object == (void*)0x99 && index == 2);
}
static void RegisterAnimation(void* object) { assert(object == (void*)0x99); }
static void StoreAnimation(void*, int index, RecoveryWord resource) {
    assert(index == 2);
    storedAnimationResource = resource;
}
static int markedAnimations;
static void* LookupAnimation(void*, void* token) {
    assert(token == (void*)7);
    return (void*)0xAA;
}
static void MarkAnimation(void*) { ++markedAnimations; }
static RecoveryWord* loadingFlag;
static void ClearLoading(unsigned milliseconds) {
    assert(milliseconds == 1);
    *loadingFlag = 0;
}
static int FindArchive(void*, void*) { return 3; }
static RecoveryWord selectedOffset;
static int SelectArchive(void*, RecoveryWord offset) {
    selectedOffset = offset;
    return 0;
}
static int pathResets;
static void ResetPath() { ++pathResets; }
static int scheduleDispatches;
static void DispatchSchedule(const char*, int tick) { assert(tick == 7); ++scheduleDispatches; }
static int spawnCount;
static void Spawn(void*, int count, RecoveryWord token, float angle, float scale) {
    assert(count == 3 && token == 0xFFFFFFFFu && angle < -1.5f && scale == 2.2f);
    ++spawnCount;
}
static int emitterResets;
static void ResetEmitter(void*) { ++emitterResets; }
static RecoveryWord timerConfigureFirst;
static void ConfigureTimer(RecoveryWord first, RecoveryWord second) {
    timerConfigureFirst = first + second;
}
static int pathLoadCalls;
static const char* loadedPath;
static void LoadWav(void*, const char* path) { ++pathLoadCalls; loadedPath = path; }
static void* AllocateState(RecoveryWord size) {
    assert(size == 0x28);
    return std::malloc(size);
}
static int initializeStateResult;
static int InitializeState(void*) { return initializeStateResult; }
static int resetCalls;
static float resetValue;
static void ResetDecay(float value) { ++resetCalls; resetValue = value; }
static int reloadCalls;
static void ReloadAnimation(void*) { ++reloadCalls; }
static int textureCreates;
static int CreateTexture(void*, int format, int mip_levels) {
    assert(format == 4 && mip_levels == 2);
    ++textureCreates;
    return 0;
}
static int textureFinalizes;
static void FinalizeTexture(void*) { ++textureFinalizes; }
static int logWrites;
static const char* loggedText;
static void WriteLog(void*, const char* text) { ++logWrites; loggedText = text; }
static void* AllocateAny(RecoveryWord size) {
    return std::malloc(size);
}
static int workerStarts;
static void StartWorker(void*) { ++workerStarts; }
static int randomTextDispatches;
static int randomTextCount;
static void DispatchText(void*, const RecoveryWord colors[4], int count) {
    assert(colors[0] == 42 && count == 17);
    ++randomTextDispatches;
    randomTextCount = count;
}
static int deviceSets;
static int deviceDraws;
static int deviceRestores;
static void SetDevice(void*) { ++deviceSets; }
static int DrawDevice(void*) { return ++deviceDraws == 1 ? -1 : 0; }
static void RestoreDevice(void*) { ++deviceRestores; }
static int stageDispatches;
static int stageSetCalls;
static int stageSetValue;
static int stageResets;
static float stageResetValue;
static int stageContinues;
static void DispatchStage(void*) { ++stageDispatches; }
static void SetStage(int value) { ++stageSetCalls; stageSetValue = value; }
static void ResetStage(float value) { ++stageResets; stageResetValue = value; }
static void ContinueStage(void*) { ++stageContinues; }
static float QuantizeMotion(float value) { return (float)(int)value; }

int main() {
    g_calls = 0;
    GameThread_RunQueueLeaf(CountCall);
    assert(g_calls == 1);

    int object = 0;
    g_calls = g_frees = 0;
    assert(Bullet_DeletingDestructor(&object, 0, Destroy, Free) == &object);
    assert(g_calls == 1 && g_frees == 0);
    assert(Platform_DeletingDestructor(&object, 1, Destroy, Free) == &object);
    assert(g_calls == 2 && g_frees == 1);

    Ecl_ForwardFloat(9, 2.5f, Forward);
    assert(g_opcode == 9 && g_value == 2.5f);

    RecoveryListNode first = {0, 0};
    RecoveryListNode tail = {&first, 0};
    RecoveryListNode inserted = {0, 0};
    first.next = &tail;
    ScoreList_InsertAfter(&first, &inserted);
    assert(first.next == &inserted && inserted.previous == &first &&
           inserted.next == &tail && tail.previous == &inserted);

    unsigned char ecl[0x2600] = {};
    Ecl_SetResourceSlot(ecl, 2, 6, 0xAA, 0xBB);
    RecoveryWord* slot = (RecoveryWord*)(ecl + 0x2494 + 0x20);
    assert(slot[0] == 6 && slot[1] == 0xAA && slot[2] == 0xBB &&
           slot[3] == 0xBB);
    Ecl_SetResourceSlot(ecl, 2, -1, 1, 2);
    assert((int)slot[0] == -1 && slot[1] == 0xAA);

    unsigned char animations[0x7000] = {};
    for (int index = 0; index < 9; ++index)
        *(RecoveryWord*)(animations + 0x4CDC + index * 0x3AC) = 0x11;
    Animation_SetActiveCount(animations, 3);
    for (int index = 0; index < 9; ++index) {
        RecoveryWord flags = *(RecoveryWord*)(animations + 0x4CDC + index * 0x3AC);
        assert((flags & 2) == (index < 3 ? 2u : 0u));
    }

    RecoveryTimerState timer = {1, 2, 3, 0, 0};
    RecoveryTimer_Reset(&timer, (void*)0x55);
    assert(timer.value == 0xFFFFFFFFu && timer.current == 0 &&
           timer.previous == 0 && timer.speed == (void*)0x55 &&
           (timer.initialized & 1) != 0);

    Vector2 vector;
    Vector2_SetEllipticPolar(&vector, 0.0f, 3.0f, 7.0f);
    assert(vector.x == 3.0f && vector.y == 0.0f);
    Vector2_SetAnimationPolar(&vector, 0.0f, 5.0f);
    assert(vector.x == 5.0f && vector.y == 0.0f);

    unsigned char path[0x60] = {};
    assert(PathState_Reset(path, 0x77) == 0);
    assert(*(RecoveryWord*)(path + 0x40) == 0xFFFFFFFFu &&
           *(RecoveryWord*)(path + 0x44) == 0 &&
           *(RecoveryWord*)(path + 0x48) == 0 &&
           *(RecoveryWord*)(path + 0x4C) == 0x77 &&
           (*(RecoveryWord*)(path + 0x50) & 1) != 0 &&
           *(RecoveryWord*)(path + 0x58) == 0 &&
           *(RecoveryWord*)(path + 0x5C) == 0);

    unsigned char owner[0x40] = {};
    *(void**)(owner + 4) = (void*)0x1234;
    *(RecoveryWord*)(owner + 0x20) = 7;
    *(RecoveryWord*)(owner + 0x24) = 11;
    assert(Platform_InvokeConfigured(owner, Invoke) == 37 &&
           *(RecoveryWord*)(owner + 0x30) == 1);
    *(void**)(owner + 4) = 0;
    assert(Platform_InvokeConfigured(owner, Invoke) == (int)0x800401F0u);

    void* interfaces[2] = {(void*)1, (void*)2};
    assert(Platform_AggregateInterfaces(interfaces, 2, First, Second) == 7);
    assert(Platform_AggregateInterfaces(0, 2, First, Second) == 0x800401F0u);

    unsigned char score[0x50] = {};
    *(int*)(score + 0x44) = 2;
    *(RecoveryWord*)(score + 0x4C) = 9;
    Score_SetMode(score, 3);
    assert(*(int*)(score + 0x44) == 3 && *(RecoveryWord*)(score + 0x4C) == 0);
    *(RecoveryWord*)(score + 0x4C) = 8;
    Score_SetMode(score, 3);
    assert(*(RecoveryWord*)(score + 0x4C) == 8);
    Score_SetNormalizedAngle(score, 3.1415927f * 2.0f);
    assert(*(float*)(score + 0x1C) < 0.01f);

    void* queriedEntries[2] = {(void*)1, (void*)2};
    RecoveryInterfaceArray queried = {queriedEntries, 2};
    assert(Platform_QueryInterfaces(&queried, Query) == 5);
    assert(Platform_QueryInterfaces(0, Query) == 0x800401F0u);
    void* availableEntries[3] = {(void*)1, 0, (void*)3};
    RecoveryInterfaceArray available = {availableEntries, 3};
    interfaceStates[0] = 1;
    interfaceStates[2] = 1;
    assert(Platform_FindAvailable(&available, 0, ReadState, PickIndex) == 0);
    availableEntries[1] = (void*)2;
    interfaceStates[1] = 1;
    assert(Platform_FindAvailable(&available, 0, ReadState, PickIndex) ==
           (void*)2);

    RecoveryCleanupNode* firstNode = new RecoveryCleanupNode{0, 0, CleanupNode};
    RecoveryCleanupNode* secondNode =
        new RecoveryCleanupNode{firstNode, 0, CleanupNode};
    firstNode->next = secondNode;
    RecoveryCleanupNode* head = firstNode;
    cleanupCalls = freedNodes = 0;
    RecoveryLinkedCleanup(&head, FreeNode);
    assert(head == 0 && cleanupCalls == 2 && freedNodes == 2);

    unsigned char initialized[0x2C8] = {0xFF};
    assert(RecoveryState_Initialize(initialized) == initialized);
    assert(*(RecoveryWord*)initialized == 2 &&
           g_recovery_global_state == initialized);

    unsigned char configured[0x240] = {};
    RecoveryState_Configure42300(configured, (void*)0x1234, 7, 8, 9, 0x55);
    assert(*(RecoveryWord*)(configured + 0x130) == 7 &&
           *(RecoveryWord*)(configured + 0x108) == 8 &&
           *(RecoveryWord*)(configured + 0x10C) == 9 &&
           *(RecoveryWord*)(configured + 0x118) == 0xFFFFFFFFu &&
           *(RecoveryWord*)(configured + 0x124) == 0x55 &&
           (*(RecoveryWord*)(configured + 0x128) & 1) != 0);

    const RecoveryByte firstColor[3] = {1, 2, 3};
    const RecoveryByte secondColor[3] = {4, 5, 6};
    RecoveryState_Configure42220(configured, firstColor, secondColor,
                                  0xAA, 0xBB, 0x66);
    assert(*(RecoveryWord*)(configured + 0xBC) == 4 &&
           *(RecoveryWord*)(configured + 0xC8) == 1 &&
           *(RecoveryWord*)(configured + 0xD0) == 3 &&
           *(RecoveryWord*)(configured + 0x100) == 0xAA &&
           *(RecoveryWord*)(configured + 0x104) == 0xBB &&
           *(RecoveryWord*)(configured + 0xEC) == 0xFFFFFFFFu);

    RecoveryState_Configure41F50(configured, 0x11223344, 0x1FF, 4, 5, 0x77);
    assert(*(RecoveryWord*)(configured + 0x22C) == 0x11223344 &&
           *(RecoveryWord*)(configured + 0x230) == 0xFF &&
           *(RecoveryWord*)(configured + 0x208) == 4 &&
           *(RecoveryWord*)(configured + 0x20C) == 5 &&
           *(RecoveryWord*)(configured + 0x218) == 0xFFFFFFFFu);
    assert(Recovery_InvokeZero(CountCall) == 0);
    Recovery_InvokeVoid(CountCall);
    assert(Recovery_InvokePair((void*)7, PairResult) == 0x100000007ull);

    RecoveryAppendNode list = {0, 0};
    RecoveryAppendNode middle = {0, 0};
    RecoveryAppendNode tailNode = {0, 0};
    Recovery_AppendNode(&list, &middle);
    Recovery_AppendNode(&list, &tailNode);
    assert(list.next == &middle && middle.previous == &list &&
           middle.next == &tailNode && tailNode.previous == &middle);

    void* ownedEntries[2] = {(void*)1, (void*)2};
    RecoveryOwnedArrayState owned = {ownedEntries, 2, (void*)3, 1};
    g_calls = g_frees = 0;
    Platform_ReleaseOwnedArray(&owned, Destroy, Destroy, Free);
    assert(owned.entries == 0 && owned.auxiliary == 0 && g_calls == 3 &&
           g_frees == 2);

    RecoveryWord completed = 9;
    updateCalls = pollCalls = 0;
    assert(Platform_RunInterface((void*)1, &completed, BeginInterface,
                                 PollInterface, SleepInterface) == 0);
    assert(completed == 1 && updateCalls == 1 && pollCalls == 2);
    assert(Platform_RunInterface(0, &completed, BeginInterface,
                                 PollInterface, SleepInterface) ==
           (int)0x800401F0u);

    unsigned char streamBytes[0x40] = {};
    RecoveryStreamState* stream = (RecoveryStreamState*)streamBytes;
    stream->memory_mode = 0;
    stream->handle = 5;
    RecoveryStreamRecord record = {12, 34};
    seekOffset = 0;
    assert(Platform_SelectStreamRecord(stream, &record, 100, SeekStream) == 0);
    assert(stream->record == &record && stream->position == 34 &&
           stream->cursor == 34 && seekOffset == 112);
    stream->handle = 0xFFFFFFFFu;
    assert(Platform_SelectStreamRecord(stream, &record, 0, SeekStream) ==
           (int)0x80004005u);

    g_calls = g_frees = 0;
    assert(Platform_DeletingDestructorWithRelease(&object, 1, Destroy, Free) ==
           &object);
    assert(g_calls == 1 && g_frees == 1);
    g_calls = g_frees = 0;
    assert(Platform_DeletingDestructorVtable(&object, 1, Destroy, Free) ==
           &object);
    assert(g_calls == 1 && g_frees == 1);

    deadline = 0;
    assert(Platform_SetOperationDeadline(true, RandomValue, 0, SetDeadline) ==
           2000);
    assert(deadline == 2000);
    assert(Platform_SetOperationDeadline(false, RandomValue, 0, SetDeadline) ==
           -10000);
    assert(deadline == -10000);

    RecoveryOwnedLink bucketNodes[8] = {};
    RecoveryOwnedLink directNodes[8] = {};
    RecoveryOwnedLink bucketTail = {(void*)1, 0};
    RecoveryOwnedLink directTail = {(void*)2, 0};
    bucketNodes[0].next = &bucketTail;
    directNodes[0].next = &directTail;
    g_frees = 0;
    Recovery_ClearEightBuckets(bucketNodes, directNodes, Free);
    assert(bucketNodes[0].next == 0 && directNodes[0].next == 0 &&
           g_frees == 2);

    g_calls = g_frees = 0;
    Platform_ReleaseOwnedHandle(&object, Destroy, Free);
    assert(g_calls == 1 && g_frees == 1);

    float speedValue = 1.0f;
    RecoveryTickState ticking = {4, 5, 5.0f, &speedValue};
    assert(Recovery_TickState(&ticking, 0, 1.0f, RoundedRandom, 0) == 0);
    assert(ticking.previous == 5 && ticking.current == 6 &&
           ticking.elapsed == 6.0f);
    speedValue = 0.5f;
    assert(Recovery_TickState(&ticking, 0, 1.0f, RoundedRandom, 0) == 0);
    assert(ticking.previous == 6 && ticking.current == 42 &&
           ticking.elapsed == 6.5f);

    unsigned char playback[0x90] = {};
    *(RecoveryWord*)(playback + 0x3C) = 10;
    *(RecoveryWord*)(playback + 0x40) = 20;
    *(RecoveryWord*)(playback + 0x84) = 1;
    transitionCalls = 0;
    Recovery_SwitchPlaybackState(playback, false, Transition);
    assert(*(RecoveryWord*)(playback + 0x4C) == 10 &&
           *(RecoveryWord*)(playback + 0x50) == 20 &&
           *(RecoveryWord*)(playback + 0x84) == 0 && transitionCalls == 1);
    *(RecoveryWord*)(playback + 0x4C) = 30;
    *(RecoveryWord*)(playback + 0x50) = 40;
    Recovery_SwitchPlaybackState(playback, true, Transition);
    assert(*(RecoveryWord*)(playback + 0x34) == 30 &&
           *(RecoveryWord*)(playback + 0x38) == 40 &&
           *(RecoveryWord*)(playback + 0x84) == 1 && transitionCalls == 2);

    const float channels[6] = {1, 2, 3, 4, 5, 6};
    RecoveryColorRecord color = {};
    RecoveryWord colorSeed = 10;
    Recovery_ScaleColor(channels, &color, 0.5f, ColorRandom, &colorSeed);
    assert(color.channels[0] == 0.5f && color.channels[5] == 3.0f &&
           color.random_channels[0] == 11 && color.random_channels[3] == 14);

    void* firstResource = (void*)1;
    void* secondResource = (void*)2;
    void* firstSlot = 0;
    void* secondSlot = 0;
    configuredFlags[0] = configuredFlags[1] = 0xFFFFFFFFu;
    assert(Recovery_InstallPairSetFlags(&firstSlot, &secondSlot,
                                        firstResource, secondResource,
                                        Configure) == 0);
    assert(firstSlot == firstResource && secondSlot == secondResource &&
           configuredFlags[0] == 2 && configuredFlags[1] == 2);
    assert(Recovery_InstallPairClearFlags(&firstSlot, &secondSlot,
                                          firstResource, secondResource,
                                          Configure) == 0);
    assert(configuredFlags[0] == 0 && configuredFlags[1] == 0);
    g_calls = g_frees = 0;
    assert(Recovery_ReleasePair(&firstSlot, &secondSlot, Destroy, Free) == 0);
    assert(firstSlot == 0 && secondSlot == 0 && g_calls == 2 && g_frees == 2);

    unsigned char largeState[0x800] = {0xFF};
    subobjectCalls = 0;
    assert(Recovery_InitializeLargeState(largeState, InitializeSubobject) ==
           largeState);
    assert(subobjectCalls == 1 && *(RecoveryWord*)(largeState + 0x3CC) == 0x140);
    unsigned char timedState[0x2C8] = {};
    RecoveryWord publishedSpeed = 0;
    *(RecoveryWord*)(timedState + 0x2C0) = 0x99;
    tickCalls = 0;
    Recovery_InitializeTimedState(timedState, Tick, &publishedSpeed);
    assert(*(RecoveryWord*)(timedState + 4) == 0xD &&
           *(RecoveryWord*)(timedState + 0x10) == 0xFFFFFFFFu &&
           publishedSpeed == 0x99 && tickCalls == 2);

    loadMode = 0;
    missingResource = 0;
    assert(Recovery_LoadStartupResources(0, LoadResource, ReportMissing) == 0);
    loadMode = 6;
    assert(Recovery_LoadStartupResources(0, LoadResource, ReportMissing) == -1 &&
           missingResource != 0);
    loadMode = 7;
    assert(Recovery_LoadStartupResources(0, LoadResource, ReportMissing) == -1);
    animationCreates = 0;
    storedAnimationResource = 0;
    assert(Recovery_InstallAnimationSlot((void*)1, 2, 0x1234,
                                         CreateAnimation, ConfigureAnimation,
                                         RegisterAnimation, StoreAnimation) == 0);
    assert(animationCreates == 1 && storedAnimationResource == 0x1234);
    RecoveryWord animationSlot = 7;
    void* children[2] = {(void*)1, (void*)2};
    markedAnimations = 0;
    Recovery_ClearAnimationSlot(&animationSlot, 0, LookupAnimation,
                                MarkAnimation, children, 2);
    assert(animationSlot == 0 && markedAnimations == 3);

    void* cachedSlots[2] = {0, (void*)0x44};
    RecoveryWord loading = 0;
    loadingFlag = &loading;
    assert(Recovery_LoadCachedResource(cachedSlots, 2, 0, 0, "x",
                                       LoadResource, &loading, false,
                                       ClearLoading) != 0);
    assert(loading == 0 && cachedSlots[0] != 0);
    assert(Recovery_LoadCachedResource(cachedSlots, 2, 1, 0, "x",
                                       LoadResource, &loading, false,
                                       ClearLoading) == (void*)0x44);

    selectedOffset = 0;
    assert(Recovery_SelectArchiveEntry(true, 0, 0, FindArchive,
                                       SelectArchive) == 0 &&
           selectedOffset == 0x9C);
    assert(Recovery_SelectArchiveEntry(false, 0, 0, FindArchive,
                                       SelectArchive) == -1);

    char resourcePath[32] = {};
    pathResets = 0;
    assert(Recovery_SplitResourcePath(resourcePath, "abc:def",
                                      sizeof(resourcePath), ResetPath) ==
           1 && pathResets == 2 && resourcePath[3] == '\0');
    assert(Recovery_SplitResourcePath(resourcePath, "abcdef",
                                      sizeof(resourcePath), ResetPath) ==
           0 && pathResets == 3);

    char schedule[0x9C] = {};
    schedule[0] = 5;
    schedule[1] = 2;
    schedule[0x34] = 3;
    schedule[0x35] = 1;
    schedule[0x68] = -1;
    scheduleDispatches = 0;
    assert(Recovery_DispatchSchedule(7, schedule, 3, DispatchSchedule) == 2 &&
           scheduleDispatches == 2);
    g_calls = g_frees = 0;
    assert(Platform_DeletingDestructorNoReturn(&object, Destroy, Free) == 0);
    assert(g_calls == 1 && g_frees == 1);
    int emitterCount = 3;
    spawnCount = emitterResets = 0;
    Recovery_ResetEmitter(&emitterCount, (void*)1, Spawn, ResetEmitter);
    assert(emitterCount == 0 && spawnCount == 1 && emitterResets == 1);
    emitterCount = 0;
    Recovery_ResetEmitter(&emitterCount, (void*)1, Spawn, ResetEmitter);
    assert(emitterResets == 2);

    unsigned char playerTimer[0x2A40] = {};
    timerConfigureFirst = 0;
    Recovery_InitializePlayerTimer(playerTimer, 0x55, ConfigureTimer);
    assert(timerConfigureFirst == 32 &&
           *(RecoveryWord*)(playerTimer + 0x2A1C) == 0x1D &&
           *(RecoveryWord*)(playerTimer + 0x2A20) == 30 &&
           *(RecoveryWord*)(playerTimer + 0x2A24) == 0x41F00000u &&
           (*(RecoveryWord*)(playerTimer + 0x2A18) & 2) != 0);

    char whitespace[] = " \t\n  hello world \r\n";
    Recovery_TrimWhitespace(whitespace);
    assert(std::strcmp(whitespace, "hello world") == 0);

    unsigned char table[0x3F0] = {0xFF};
    assert(Recovery_InitializeStateTable(table) == table &&
           *(RecoveryWord*)table == 2);

    char wavPath[32] = "music.ogg";
    pathLoadCalls = 0;
    Recovery_ReplaceExtensionWav(0, wavPath, LoadWav);
    assert(std::strcmp(wavPath, "music.wav") == 0 && pathLoadCalls == 1 &&
           loadedPath == wavPath);

    RecoveryWord wordValues[6] = {1, 2, 3, 4, 5, 6};
    RecoveryWordColorRecord wordColor = {};
    RecoveryWord colorWordSeed = 20;
    Recovery_InitializeWordColor(wordValues, &wordColor, ColorRandom,
                                  &colorWordSeed);
    assert(wordColor.channels[0] == 1 && wordColor.channels[5] == 6 &&
           wordColor.random_channels[0] == 21);

    unsigned char rawPair[0x20] = {};
    *(void**)(rawPair + 8) = (void*)1;
    *(void**)(rawPair + 0xC) = (void*)2;
    RecoveryWord rawFlag = 3;
    g_calls = g_frees = 0;
    Recovery_ReleaseRawPairAndReset(rawPair, Destroy, Free, &rawFlag);
    assert(g_calls == 2 && g_frees == 2 && rawFlag == 0 &&
           *(void**)(rawPair + 8) == 0 && *(void**)(rawPair + 0xC) == 0);

    initializeStateResult = 0;
    void* smallState = Recovery_CreateSmallState(AllocateState,
                                                  InitializeState, Destroy, Free);
    assert(smallState != 0 && g_recovery_small_state == smallState &&
           (*(RecoveryWord*)smallState & 2) != 0);
    std::free(smallState);
    g_recovery_small_state = 0;

    void* interfaceStorage[2] = {(void*)1, (void*)2};
    RecoveryOwnedArrayState interfaceOwner = {};
    Recovery_InitializeInterfaceArray(&interfaceOwner, interfaceStorage, 2,
                                      (void*)3, Query);
    assert(interfaceOwner.entries == interfaceStorage &&
           interfaceOwner.count == 2 && interfaceOwner.auxiliary == (void*)3);
    void* singleStorage[1] = {};
    RecoveryInterfaceArray singleOwner = {};
    Recovery_InitializeSingleInterface(&singleOwner, (void*)4, singleStorage,
                                       (void*)5, Query);
    assert(singleOwner.entries == singleStorage && singleOwner.count == 1 &&
           singleStorage[0] == (void*)4);

    const float pointInput[3] = {1, 2, 3};
    float pointOutput[3] = {};
    Recovery_OffsetPoint(pointInput, pointOutput);
    assert(pointOutput[0] == 21 && pointOutput[1] == 12 && pointOutput[2] == 3);

    unsigned char decay[0x20] = {};
    *(int*)(decay + 0x18) = 1;
    resetCalls = 0;
    Recovery_DecayCounter(decay, ResetDecay);
    assert(resetCalls == 1 && resetValue == -1.0f);
    *(int*)(decay + 0x18) = 0;
    *(int*)(decay + 0xC) = 5100;
    *(int*)(decay + 0x10) = 10;
    Recovery_DecayCounter(decay, ResetDecay);
    assert(*(int*)(decay + 0x10) == 18 && *(int*)(decay + 0xC) == 5090);

    unsigned char packetBytes[12] = {};
    RecoveryPacketBuffer packet = {packetBytes, packetBytes, 12};
    assert(!Recovery_AppendPacket(&packet, 1, 2, 3));
    assert(*(unsigned short*)packetBytes == 1 && packet.cursor == packetBytes + 6);
    assert(!Recovery_AppendPacket(&packet, 4, 5, 6));

    unsigned char randomTable[0x448] = {};
    Recovery_InitializeRandomTable(randomTable, RoundedRandom, 0);
    assert(*(RecoveryWord*)randomTable == 0x5453 &&
           *(RecoveryWord*)(randomTable + 8) == 0x448 &&
           *(short*)(randomTable + 0x46) == 42);

    initializeStateResult = 0;
    void* timerState = Recovery_CreateTimerState(AllocateAny, InitializeState,
                                                 Destroy, Free);
    assert(timerState != 0 && *(RecoveryWord*)timerState == 2);
    std::free(timerState);

    RecoveryWord rootStatus = 0;
    RecoveryWord childStatus[2] = {};
    Recovery_MarkAnimationTree(&rootStatus, childStatus, 2);
    assert(rootStatus == 6 && childStatus[0] == 6 && childStatus[1] == 6);

    void* fixedState = Recovery_CreateFixedState(0x48, AllocateAny,
                                                 InitializeState, Destroy, Free);
    assert(fixedState != 0 && *(RecoveryWord*)fixedState == 2);
    std::free(fixedState);

    unsigned char emitterState[0x40] = {};
    reloadCalls = 0;
    assert(Recovery_UpdateEmitterDecision(emitterState, 0, 2, true) == 1);
    *(int*)(emitterState + 0x24) = 11;
    assert(Recovery_UpdateEmitterDecision(emitterState, 0, 2, true) == 6);
    *(int*)(emitterState + 0x30) = 3;
    Recovery_IncrementAnimationCount(emitterState, 2, ReloadAnimation);
    assert(*(int*)(emitterState + 0x30) == 5 && reloadCalls == 1);
    Recovery_IncrementAnimationCount(emitterState, 6, ReloadAnimation);
    assert(*(int*)(emitterState + 0x30) == 9);

    textureCreates = textureFinalizes = 0;
    assert(Recovery_CreateTextureFromMemory((void*)1, 4, 2,
                                            CreateTexture, FinalizeTexture) == 0);
    assert(textureCreates == 1 && textureFinalizes == 1);
    unsigned char logState[0x360] = {};
    logWrites = 0;
    Recovery_MarkLogState(logState, WriteLog, "hello");
    assert(logWrites == 1 && std::strcmp(loggedText, "hello") == 0 &&
           (*(RecoveryWord*)(logState + 0x35C) & 1) != 0);
    void* resourceState = Recovery_CreateResourceState(0x20, AllocateAny,
                                                       InitializeState, Destroy,
                                                       Free);
    assert(resourceState != 0);
    std::free(resourceState);
    RecoveryWord workerHandle = 0;
    RecoveryWord workerId = 0;
    workerStarts = 0;
    assert(Recovery_StartWorker((void*)1, StartWorker, &workerHandle,
                                &workerId) == 0 && workerHandle == 1 &&
           workerId == 0 && workerStarts == 1);

    unsigned char* composite = (unsigned char*)std::calloc(1, 0x9EC8);
    *(void**)(composite + 0x9EB8) = (void*)1;
    *(void**)(composite + 0x9EBC) = (void*)2;
    *(void**)(composite + 0x9E80) = (void*)3;
    g_calls = g_frees = 0;
    Recovery_ReleaseCompositeState(composite, Destroy, Free);
    assert(g_calls == 3 && g_frees == 3 &&
           *(void**)(composite + 0x9EB8) == 0);
    std::free(composite);

    void* globalStates[3] = {(void*)1, (void*)2, (void*)3};
    g_calls = g_frees = 0;
    Recovery_ReleaseGlobalStates(globalStates, 3, Destroy, Free);
    assert(globalStates[0] == 0 && globalStates[2] == 0 && g_calls == 3 &&
           g_frees == 3);

    randomTextDispatches = randomTextCount = 0;
    assert(Recovery_DispatchRandomText(0, 0, RoundedRandom,
                                       DispatchText) == 1 &&
           randomTextDispatches == 1 && randomTextCount == 17);
    assert(Recovery_DispatchRandomText(4, 0, RoundedRandom,
                                       DispatchText) == 0);

    void* largeResource = Recovery_CreateLargeResourceState(
        AllocateAny, InitializeState, Destroy, Free);
    void* hugeResource = Recovery_CreateHugeResourceState(
        AllocateAny, InitializeState, Destroy, Free);
    assert(largeResource != 0 && hugeResource != 0);
    std::free(largeResource);
    std::free(hugeResource);

    deviceSets = deviceDraws = deviceRestores = 0;
    Recovery_ResetDeviceStreams((void*)1, SetDevice, DrawDevice, RestoreDevice);
    assert(deviceSets == 2 && deviceDraws == 2 && deviceRestores == 1);

    unsigned char* stageState = (unsigned char*)std::calloc(1, 0x3510);
    *(RecoveryWord*)(stageState + 0x3504) = 0x1234;
    stageState[0x3508] = 1;
    Recovery_UpdateStageSequence(stageState, false, DispatchStage, SetStage,
                                 ResetStage, ContinueStage);
    assert(*(RecoveryWord*)(stageState + 0x3504) == 0 &&
           stageState[0x3508] == 0);

    *(int*)(stageState + 0x458) = 1;
    *(int*)(stageState + 0x460) = 2;
    *(int*)(stageState + 0x464) = -1;
    stageDispatches = stageSetCalls = stageResets = stageContinues = 0;
    Recovery_UpdateStageSequence(stageState, false, DispatchStage, SetStage,
                                 ResetStage, ContinueStage);
    assert(stageDispatches == 0 && stageSetCalls == 0 && stageContinues == 0);

    Recovery_UpdateStageSequence(stageState, true, DispatchStage, SetStage,
                                 ResetStage, ContinueStage);
    assert(stageSetCalls == 1 && stageSetValue == 0 && stageDispatches == 1 &&
           stageContinues == 1);

    *(int*)(stageState + 0x460) = 14;
    *(int*)(stageState + 0x464) = 15;
    stageDispatches = stageSetCalls = stageResets = stageContinues = 0;
    Recovery_UpdateStageSequence(stageState, true, DispatchStage, SetStage,
                                 ResetStage, ContinueStage);
    assert(stageDispatches == 1 && stageResets == 1 &&
           stageResetValue == -15.0f && stageContinues == 0);

    stageDispatches = stageSetCalls = stageResets = stageContinues = 0;
    Recovery_UpdateStageSequence(stageState, false, DispatchStage, SetStage,
                                 ResetStage, ContinueStage);
    assert(stageDispatches == 1 && stageSetCalls == 1 && stageSetValue == -1 &&
           stageResets == 0 && stageContinues == 0);
    std::free(stageState);

    float linearMotion[11] = {1.5f, 2.5f, 3.0f, 2.0f, -1.0f, 4.0f};
    Recovery_AdvancePolarMotion(linearMotion, QuantizeMotion);
    assert(linearMotion[0] == 3.0f && linearMotion[1] == 1.0f &&
           linearMotion[2] == 7.0f);

    float polarMotion[11] = {};
    polarMotion[3] = 10.0f;
    polarMotion[4] = 20.0f;
    polarMotion[5] = 30.0f;
    polarMotion[7] = 0.0f;
    polarMotion[8] = 2.0f;
    ((RecoveryWord*)polarMotion)[10] = 1;
    Recovery_AdvancePolarMotion(polarMotion, QuantizeMotion);
    assert(polarMotion[0] == 12.0f && polarMotion[1] == 20.0f &&
           polarMotion[2] == 30.0f);
    return 0;
}
