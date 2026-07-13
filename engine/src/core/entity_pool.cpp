#include "th10/entity.h"
#include <cstring>

namespace th10 {

Entity* AllocEntity(GameStateManager* gs) {
    if (!gs) return nullptr;

    // Round-robin scan of pool1
    int& idx = gs->entityPoolIndex;
    int start = idx;
    do {
        idx = (idx + 1) & 0x3FF; // mask with 0x3FF (4095) for 4096 slots
        if (!gs->entityInUse[idx]) {
            gs->entityInUse[idx] = 1;
            Entity* e = &gs->entityPool1[idx];
            ResetEntity(e);
            return e;
        }
    } while (idx != start);

    // Pool1 full, try pool2
    for (int i = 0; i < ENTITY_POOL2_SIZE; i++) {
        if (!gs->entityInUse[ENTITY_POOL1_SIZE + i]) {
            gs->entityInUse[ENTITY_POOL1_SIZE + i] = 1;
            Entity* e = &gs->entityPool2[i];
            ResetEntity(e);
            return e;
        }
    }

    return nullptr; // all pools full
}

void LinkEntity(GameStateManager* gs, Entity* e) {
    if (!gs || !e) return;

    // Assign monotonic ID
    gs->entityIdCounter++;
    if (gs->entityIdCounter == 0) gs->entityIdCounter = 1;
    e->entityId = gs->entityIdCounter;

    // Self-pointer (raw offset within our pool, matches binary's self-referential ptr)
    e->selfRaw = 0; // In our implementation, we track by raw pointer

    // Insert at head of active list
    e->nextRaw = gs->activeListHeadRaw;
    e->prevRaw = 0;
    if (gs->activeListHeadRaw != 0) {
        // Update old head's prev to point to us
        // In 32-bit binary this would dereference at offset+0xC, but we store raw indices
    }
    gs->activeListHeadRaw = 1; // mark as occupied
    if (gs->activeListTailRaw == 0) {
        gs->activeListTailRaw = 1;
    }
}

void UnlinkEntity(GameStateManager* gs, Entity* e) {
    if (!gs || !e) return;

    // Find and clear in-use flag
    ptrdiff_t offset = (uint8_t*)e - (uint8_t*)&gs->entityPool1[0];
    if (offset >= 0 && offset < (ptrdiff_t)(sizeof(Entity) * ENTITY_POOL1_SIZE)) {
        int idx = offset / sizeof(Entity);
        gs->entityInUse[idx] = 0;
    } else {
        offset = (uint8_t*)e - (uint8_t*)&gs->entityPool2[0];
        if (offset >= 0 && offset < (ptrdiff_t)(sizeof(Entity) * ENTITY_POOL2_SIZE)) {
            int idx = ENTITY_POOL1_SIZE + (offset / sizeof(Entity));
            gs->entityInUse[idx] = 0;
        }
    }
}

void ResetEntity(Entity* e) {
    if (!e) return;

    // Preserve entityType and position
    int32_t savedType = e->entityType;
    float savedX = e->posX;
    float savedY = e->posY;
    float savedZ = e->posZ;

    memset(e, 0, sizeof(Entity));

    e->entityType = savedType;
    e->posX = savedX;
    e->posY = savedY;
    e->posZ = savedZ;

    // Defaults matching FUN_00401de0
    e->initValue = -999999.0f; // 0xFFF0BDC1
    e->scaleX = 1.0f;
    e->scaleY = 1.0f;
    e->subId = -1;
    e->transform[0][0] = 1.0f;
    e->transform[1][1] = 1.0f;
    e->transform[2][2] = 1.0f;
    e->transform[3][3] = 1.0f;
}

} // namespace th10
