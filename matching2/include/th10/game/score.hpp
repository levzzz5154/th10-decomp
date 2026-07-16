#pragma once

#include "th10/game/entity.hpp"
#include "th10/game/scheduler.hpp"

// Partial layout for the score/counter object used by 0x0041BE80.
struct ScoreCounter {
    uint32_t field_000[3];
    int32_t value;  // +0x0C, capped at 99,999

    void AddScaled(int32_t amount);
};

// Partial layout of the global run-score state at 0x00474C40. The field at
// +0x04 is the player's score; callers pass awards in tenths of a point.
struct GameScore {
    uint32_t unknown_00;
    int32_t value;  // +0x04, capped at 999,999,999

    void AddScaled(int32_t amount);
};

// Partial owner layout used by the score/game-flow callbacks adjacent to the
// score accumulator code. A callback with its retirement bit (0x02) set is
// removed by the scheduler on its next pass.
struct ScoreRuntimeCallbacks {
    uint32_t unknown_00[2];
    SchedulerCallback* primary;    // +0x08
    SchedulerCallback* secondary;  // +0x0C

    void Retire();
};

typedef void (*ScoreEntityRelease)(void* manager, Entity* entity);
// Partial layout of the score/gameplay runtime owning all entity arrays visited
// by the teardown callbacks at 0x004091C0 and 0x00409230.
struct ScoreRuntimeState {
    uint32_t unknown_000[4];
    Entity primaryEntity;    // +0x0010
    Entity secondaryEntity;  // +0x03BC
    uint8_t unknown_0768[0x10];
    Entity stageEntities[8]; // +0x0778
    Entity effectEntities[5];// +0x24D8
    uint8_t unknown_3744[0x48];
    uint32_t flags;          // +0x378C; bit 0 requests entity release

    int ReleaseFlaggedEntities(
        ScoreEntityRelease releaseEntity, void* entityManager);
    int ReleaseFlaggedEntityArrays(
        ScoreEntityRelease releaseEntity, void* entityManager);
    int RunArrayReleaseCallback(
        ScoreEntityRelease releaseEntity, void* entityManager);
};
