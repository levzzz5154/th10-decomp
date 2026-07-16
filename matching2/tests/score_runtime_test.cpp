#include "th10/game/score.hpp"

#include <cassert>
#include <cstring>

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
    TestScoreCounter();
    TestGameScore();
    TestCallbackRetirement();
    TestFlaggedEntityRelease();
    TestFlaggedEntityArrayRelease();
    return 0;
}
