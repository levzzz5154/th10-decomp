// 0x0041BE80 - Add one tenth of amount to the counter, saturating at 99,999.
#include "th10/game/score.hpp"

void ScoreCounter::AddScaled(int32_t amount) {
    value += amount / 10;
    if (value > 99999) {
        value = 99999;
    }
}

// 0x00409D90 - Add one tenth of an award to the current run score.
void GameScore::AddScaled(int32_t amount) {
    value += amount / 10;
    if (value >= 1000000000) {
        value = 999999999;
    }
}

// 0x00409E20 - Request removal of both registered runtime callbacks.
void ScoreRuntimeCallbacks::Retire() {
    if (primary != 0) {
        primary->flags |= 2;
    }
    if (secondary != 0) {
        secondary->flags |= 2;
    }
}

// 0x00409230 - Release the runtime's first two entities during teardown.
int ScoreRuntimeState::ReleaseFlaggedEntities(
    ScoreEntityRelease releaseEntity, void* entityManager) {
    if ((flags & 1) != 0) {
        releaseEntity(entityManager, &primaryEntity);
        releaseEntity(entityManager, &secondaryEntity);
    }
    return 1;
}

// 0x004091C0 - Release the two trailing entity arrays while this runtime's
// release flag is set. The retail function receives this object through EBX
// and each Entity argument through EAX, which the raw decompiler omits.
int ScoreRuntimeState::ReleaseFlaggedEntityArrays(
    ScoreEntityRelease releaseEntity, void* entityManager) {
    if ((flags & 1) != 0) {
        for (int index = 0; index != 8; ++index) {
            releaseEntity(entityManager, &stageEntities[index]);
        }
        for (int index = 0; index != 5; ++index) {
            releaseEntity(entityManager, &effectEntities[index]);
        }
    }
    return 1;
}

// 0x00409270 - Secondary scheduler callback wrapper. Retail preserves the
// callback owner in EBX before entering the shared array-release routine.
int ScoreRuntimeState::RunArrayReleaseCallback(
    ScoreEntityRelease releaseEntity, void* entityManager) {
    return ReleaseFlaggedEntityArrays(releaseEntity, entityManager);
}
