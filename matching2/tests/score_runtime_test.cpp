#include "th10/game/score.hpp"

#include <cassert>
#include <cstring>

extern "C" void* malloc(unsigned long size);
extern "C" void free(void* memory);
extern "C" void _free(void* memory) { free(memory); }
void* PTR_LAB_0046dab0 = (void*)0x46DAB0;
void* PTR_LAB_0046da60 = (void*)0x46DA60;
unsigned int DAT_00476f78;
float DAT_00470b04 = 0.0f;
float DAT_00470b38 = 448.0f;
float DAT_00470b3c = 192.0f;
float DAT_00470b40 = -192.0f;

Entity* __fastcall Entity_Constructor(Entity* entity) {
    std::memset(entity, 0, sizeof(*entity));
    return entity;
}

SchedulerCallback* Scheduler_CreateAndRegister(
        SchedulerFunction function, int, void*) {
    SchedulerCallback* callback = (SchedulerCallback*)malloc(
        sizeof(SchedulerCallback));
    std::memset(callback, 0, sizeof(*callback));
    callback->function = function;
    return callback;
}

static void TestScoreCounter() {
    ScoreCounter counter = {};
    counter.value = 100;
    counter.AddScaled(95);
    assert(counter.value == 109);

    counter.AddScaled(-19);
    assert(counter.value == 108);

    counter.value = 99998;
    counter.AddScaled(20);
    assert(counter.value == 99999);
}

static void TestScoreObjectInitialize() {
    unsigned char object[0x424] = {};
    *(unsigned int*)(object + 0x20) = 0xFFFFFFFF;
    *(unsigned int*)(object + 0x420) = 0xFFFFFFFF;
    assert(ScoreObject_Initialize(0, object) == object);
    assert(*(unsigned int*)(object + 0x10) == 0xFFFFFFFF);
    assert(*(unsigned int*)(object + 0x14) == 0);
    assert(*(unsigned int*)(object + 0x18) == 0);
    assert(*(unsigned int*)(object + 0x20) == 1);
}

static void TestScoreExtendedObjectInitialize() {
    unsigned char object[0xD50] = {};
    ScoreExtendedObject_Initialize(0, object);
    assert(*(void**)object == PTR_LAB_0046da60);
    assert(*(unsigned short*)(object + 0x984) == 0xFFFF);
    assert(*(unsigned short*)(object + 0xD30) == 0xFFFF);
    assert(*(unsigned int*)(object + 0x600) == 0);
    assert(*(unsigned int*)(object + 0x9AC) == 0);
}

static int retiredCallbacks;
static int cleanedRecords;
static void RetireScoreCallback(void*) { ++retiredCallbacks; }
static void CleanupScoreRecord(void*) { ++cleanedRecords; }

static void TestScoreExtendedObjectDestroy() {
    unsigned char object[0x40] = {};
    void* callbackA = (void*)0x1111;
    void* callbackB = (void*)0x2222;
    *(void**)(object + 8) = callbackA;
    *(void**)(object + 12) = callbackB;
    ScoreOwnedRecord* first = (ScoreOwnedRecord*)malloc(
        sizeof(ScoreOwnedRecord));
    ScoreOwnedRecord* second = (ScoreOwnedRecord*)malloc(
        sizeof(ScoreOwnedRecord));
    std::memset(first, 0, sizeof(*first));
    std::memset(second, 0, sizeof(*second));
    first->next = second;
    first->cleanup = CleanupScoreRecord;
    second->cleanup = CleanupScoreRecord;
    *(ScoreOwnedRecord**)(object + 0x18) = first;
    retiredCallbacks = cleanedRecords = 0;
    ScoreExtendedObject_Destroy(object, RetireScoreCallback);
    assert(retiredCallbacks == 2 && cleanedRecords == 2);
    assert(*(void**)(object + 0x18) == 0);
}

static int scoreSpawnCalls;
static void ScoreSpawn(void*) { ++scoreSpawnCalls; }

static void TestScoreStateActivation() {
    unsigned char state[0x480] = {};
    *(unsigned short*)(state + 0x446) = 2;
    *(int*)(state + 0x438) = 4;
    scoreSpawnCalls = 0;
    assert(ScoreState_ActivateFromResult(state, 0, 4, ScoreSpawn) == 1);
    assert(scoreSpawnCalls == 1);
    assert(*(unsigned short*)(state + 0x30C) == 1);
    assert(*(unsigned short*)(state + 0x446) == 3);
    assert(*(unsigned int*)(state + 0x3F8) == 0xFFFFFFFF);
    assert((*(unsigned int*)(state + 0x408) & 1u) != 0);

    *(unsigned short*)(state + 0x446) = 1;
    *(unsigned int*)state = 0;
    assert(ScoreState_ActivateFromResult(state, 1, -1, ScoreSpawn) == 1);
    assert((*(unsigned int*)state & 8u) != 0);
    *(unsigned short*)(state + 0x446) = 0;
    assert(ScoreState_ActivateFromResult(state, 0, 0, ScoreSpawn) == 0);
}

static void TestWrappedAngleDifference() {
    assert(WrappedAngleDifference(6.0f, 0.0f, 6.2831853f, 3.1415926f) < 0.0f);
    assert(WrappedAngleDifference(0.0f, 6.0f, 6.2831853f, 3.1415926f) > 0.0f);
    assert(WrappedAngleDifference(1.0f, 0.5f, 6.2831853f, 3.1415926f) == 0.5f);
}

static void TestEntityAngles() {
    const float point[2] = {1.0f, 0.0f};
    const float origin[2] = {0.0f, 0.0f};
    assert(Entity_AngleToPoint(point, origin) > -0.001f);
    assert(Entity_AngleFromPoint(point, origin) > 3.13f);
    assert(Entity_AngleToPoint(origin, origin) > 3.13f);
}

static void TestScoreVectorFromPolar() {
    float vector[2] = {};
    Score_VectorFromPolar(vector, 1.57079632679f, 4.0f);
    assert(vector[0] > -0.0001f && vector[0] < 0.0001f);
    assert(vector[1] > 3.999f && vector[1] < 4.001f);
}

static void TestJoystickButtonEncoding() {
    unsigned char buttons[32];
    std::memset(buttons, 0xCC, sizeof(buttons));
    Input_EncodeJoystickButtons(0x80000005u, buttons);
    assert(buttons[0] == 0x80 && buttons[2] == 0x80);
    assert(buttons[31] == 0x80 && buttons[1] == 0);
    assert(buttons[30] == 0);
}

static int PollKeyboard(unsigned char* destination) {
    destination[0x41] = 0x80;
    return 7;
}

static void TestKeyboardStateUpdate() {
    unsigned char keyboard[256];
    std::memset(keyboard, 0xCC, sizeof(keyboard));
    assert(Input_UpdateKeyboardState(keyboard, false, false,
                                     PollKeyboard) == 0);
    assert(keyboard[0] == 0 && keyboard[0x41] == 0);
    assert(Input_UpdateKeyboardState(keyboard, true, false,
                                     PollKeyboard) == 7);
    assert(keyboard[0x41] == 0x80);
    assert(Input_UpdateKeyboardState(keyboard, true, true,
                                     PollKeyboard) == 1);
}

static unsigned char normalizedKeyboard[256];
static int ReadKeyboard(unsigned char* state) {
    state[0] = 0x81;
    state[1] = 0x7F;
    return 1;
}
static int WriteKeyboard(const unsigned char* state) {
    std::memcpy(normalizedKeyboard, state, 256);
    return 1;
}

static void TestKeyboardNormalization() {
    std::memset(normalizedKeyboard, 0, sizeof(normalizedKeyboard));
    unsigned char state[256] = {};
    Input_NormalizeKeyboardState(state, ReadKeyboard, WriteKeyboard);
    assert(normalizedKeyboard[0] == 1);
    assert(normalizedKeyboard[1] == 0x7F);
}

static void TestInputHistoryStep() {
    unsigned char state[0x100] = {};
    *(unsigned int*)(state + 0x8C) = 2;
    *(unsigned int*)(state + 12 + 4) = 0x1111;
    *(unsigned int*)(state + 12 + 8) = 0x2222;
    *(unsigned int*)(state + 0x4C + 4) = 0x3333;
    *(unsigned int*)(state + 0x4C + 8) = 0x4444;
    *(unsigned int*)(state + 0xD4) = 9;
    Score_InputHistoryStep(state);
    assert(*(unsigned int*)(state + 0x8C) == 1);
    assert(*(unsigned int*)state == 0x1111);
    assert(*(unsigned int*)(state + 8) == 0x3333);
    assert(*(unsigned int*)(state + 0xD4) == 0);
    Score_InputHistoryStep(state);
    assert(*(unsigned int*)(state + 0x8C) == 0);
}

static void TestInputHistorySave() {
    unsigned char state[0x100] = {};
    *(unsigned int*)(state + 0x8C) = 15;
    *(unsigned int*)state = 0xaaaa;
    *(unsigned int*)(state + 8) = 0xbbbb;
    *(unsigned int*)(state + 0xD4) = 7;
    Score_InputHistorySave(state);
    assert(*(unsigned int*)(state + 12 + 15 * 4) == 0xaaaa);
    assert(*(unsigned int*)(state + 0x4C + 15 * 4) == 0xbbbb);
    assert(*(unsigned int*)(state + 0x8C) == 15);
    assert(*(unsigned int*)(state + 0xD4) == 0);
}

static void TestScoreInputAndPatternHelpers() {
    assert(InputMaskActive(0x0001, 0, 0x0001));
    assert(InputMaskActive(0, 0x0002, 0x0002));
    assert(!InputMaskActive(0x0001, 0x0002, 0x0004));

    const unsigned char patterns[] = {
        'a', 'b', 'c', 0, 0,
        'b', 'b', 'd', 0, 0,
    };
    assert(CountPatternMatches(patterns, 2, 5, 3, 'b') == 3);
}

static void TestInputAndBoundedCounterHelpers() {
    unsigned char state[0x400] = {};
    *(unsigned short*)(state + 0x2c) = 1;
    *(unsigned short*)(state + 0x2e) = 0;
    UpdateInputState(state);
    assert(*(unsigned short*)(state + 0x32) == 1);
    assert(*(unsigned short*)(state + 0x34) == 0);
    unsigned int counter[3] = {0, 0, 10};
    assert(UpdateBoundedCounter(3, counter) == 3);
    assert(UpdateBoundedCounter(20, counter) == 9);
    SetInputMode(state, 7);
    assert(*(unsigned int*)(state + 0x390) == 7);
    *(unsigned int*)(state + 0x3cc) = 0x1000;
    SetInputMode(state, 7);
    assert(*(unsigned int*)(state + 0x390) == 2);
    float vector[2] = {};
    Score_SetPolarVector(vector, 0.0f, 4.0f);
    assert(vector[0] == 4.0f && vector[1] == 0.0f);
}

static int EvaluateRecord(ScoreLinkedRecord*) { return 3; }
static int RuntimeCallback(void*) { return 0; }

static void TestLinkedScoreRecords() {
    ScoreLinkedRecord first = {};
    ScoreLinkedRecord second = {};
    first.next = &second;
    first.type = 0;
    second.type = 1;
    second.Evaluate = EvaluateRecord;
    ScoreRecords_MarkEligible(&first);
    assert(first.marked == 1 && second.marked == 0);
    float destination[3] = {};
    const float source[3] = {1.0f, 2.0f, 3.0f};
    assert(ScoreRecords_CopyVectorAndEvaluate(&first, destination, source) == 0);
    second.type = 0;
    assert(ScoreRecords_CopyVectorAndEvaluate(&first, destination, source) == 3);
    assert(destination[2] == 3.0f);
}

static void TestRuntimeCallbackInitialization() {
    ScoreRuntimeCallbacks callbacks = {};
    assert(ScoreRuntimeCallbacks_Initialize(
        &callbacks, &callbacks, RuntimeCallback, RuntimeCallback,
        RuntimeCallback));
    assert(callbacks.primary != 0 && callbacks.secondary != 0 &&
           callbacks.tertiary != 0);
    callbacks.Retire();
    assert((callbacks.primary->flags & 2) != 0);
    assert((callbacks.secondary->flags & 2) != 0);
    assert((callbacks.tertiary->flags & 2) != 0);
}

static void TestGameScore() {
    GameScore score = {};
    score.value = 123;
    score.AddScaled(99);
    assert(score.value == 132);

    score.AddScaled(-29);
    assert(score.value == 130);

    score.value = 999999998;
    score.AddScaled(20);
    assert(score.value == 999999999);
}

static void TestScoreGaugeMinimum() {
    unsigned char gauge[0x10] = {};
    *(int*)(gauge + 0x0C) = 4500;
    ScoreGauge_AddWithMinimum(gauge, 3000);
    assert(*(int*)(gauge + 0x0C) == 5000);
    *(int*)(gauge + 0x0C) = 5200;
    ScoreGauge_AddWithMinimum(gauge, 3000);
    assert(*(int*)(gauge + 0x0C) == 5500);
    *(int*)(gauge + 0x0C) = 4800;
    ScoreGauge_AddWithMinimum(gauge, 1000);
    assert(*(int*)(gauge + 0x0C) == 5000);
}

static void TestCallbackRetirement() {
    SchedulerCallback primary;
    SchedulerCallback secondary;
    std::memset(&primary, 0, sizeof(primary));
    std::memset(&secondary, 0, sizeof(secondary));
    primary.flags = 0x10;
    secondary.flags = 0x21;

    ScoreRuntimeCallbacks callbacks = {};
    callbacks.primary = &primary;
    callbacks.secondary = &secondary;
    callbacks.Retire();
    assert(primary.flags == 0x12);
    assert(secondary.flags == 0x23);

    callbacks.primary = 0;
    secondary.flags = 0;
    callbacks.Retire();
    assert(secondary.flags == 2);
}

static void* releasedManager;
static Entity* releasedEntities[16];
static int releaseCount;

static void RecordEntityRelease(void* manager, Entity* entity) {
    releasedManager = manager;
    releasedEntities[releaseCount++] = entity;
}

static void TestFlaggedEntityRelease() {
    ScoreRuntimeState state = {};
    void* manager = reinterpret_cast<void*>(0x1234);

    releaseCount = 0;
    assert(state.ReleaseFlaggedEntities(RecordEntityRelease, manager) == 1);
    assert(releaseCount == 0);

    state.flags = 1;
    assert(state.ReleaseFlaggedEntities(RecordEntityRelease, manager) == 1);
    assert(releaseCount == 2);
    assert(releasedManager == manager);
    assert(releasedEntities[0] == &state.primaryEntity);
    assert(releasedEntities[1] == &state.secondaryEntity);
}

static void TestFlaggedEntityArrayRelease() {
    ScoreRuntimeState state = {};
    void* manager = reinterpret_cast<void*>(0x5678);

    releaseCount = 0;
    releasedManager = 0;
    assert(state.ReleaseFlaggedEntityArrays(
               RecordEntityRelease, manager) == 1);
    assert(releaseCount == 0);
    assert(releasedManager == 0);

    state.flags = 1;
    assert(state.RunArrayReleaseCallback(
               RecordEntityRelease, manager) == 1);
    assert(releaseCount == 13);
    assert(releasedManager == manager);
    for (int index = 0; index != 8; ++index) {
        assert(releasedEntities[index] == &state.stageEntities[index]);
    }
    for (int index = 0; index != 5; ++index) {
        assert(releasedEntities[index + 8] == &state.effectEntities[index]);
    }
}

int main() {
    TestWrappedAngleDifference();
    TestEntityAngles();
    TestScoreVectorFromPolar();
    TestJoystickButtonEncoding();
    TestKeyboardStateUpdate();
    TestKeyboardNormalization();
    TestInputHistoryStep();
    TestInputHistorySave();
    TestScoreInputAndPatternHelpers();
    TestInputAndBoundedCounterHelpers();
    TestLinkedScoreRecords();
    TestRuntimeCallbackInitialization();
    TestScoreCounter();
    TestScoreObjectInitialize();
    TestScoreExtendedObjectInitialize();
    TestScoreExtendedObjectDestroy();
    TestScoreStateActivation();
    TestGameScore();
    TestScoreGaugeMinimum();
    TestCallbackRetirement();
    TestFlaggedEntityRelease();
    TestFlaggedEntityArrayRelease();
    return 0;
}
