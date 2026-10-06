#include "item_spawn.hpp"
// The game counters live in one object whose address is visible elsewhere,
// so the power read follows the item stores.
struct ItemGameCounters {
    int score;          // 0x00474C44
    short power_units;  // 0x00474C48
};
extern "C" ItemGameCounters g_item_counters;

static __forceinline void ResetTimer(FrameTimer* timer) {
    unsigned int flags = timer->flags;
    if (!(flags & 1u)) {
        flags |= 1u;
        timer->current = 0;
        timer->previous = -999999;
        timer->elapsed = 0.0f;
        timer->speed = &data_00476f78;
        timer->flags = flags;
    }
    timer->current = 0;
    timer->elapsed = 0.0f;
    timer->previous = -1;
}

static __forceinline void ResetMotion(SpawnItem_0041bb00* item) {
    item->motion_state = 0;
    ResetTimer(&item->timer);
    item->motion_counter = 0;
}

static __forceinline SpawnItem_0041bb00* FindFreeItem(SpawnItem_0041bb00* item) {
    for (int slot = 0; slot < 150; ++slot, ++item) {
        if (item->state == 0) return item;
    }
    return 0;
}

static __forceinline AnimationResource_0043e710* ItemAnimation() {
    return static_cast<AnimationResource_0043e710*>(data_004776f0->item_animation);
}

#pragma code_seg(".text$d00itemspawn")
__declspec(noinline) int PlayerItemManager::Spawn(
        const Vector3* position, int kind, int identifier, float angle, float speed) {
    // Ordinary drops scan the first 150 entries. A full pool silently drops
    // the request, and every exit returns zero.
    if (kind != 8) {
        SpawnItem_0041bb00* item = FindFreeItem(normal);
        if (!item) return 0;
        item->state = 1;
        Vector3* location = &item->position;
        *location = *position;
        if (location->x <= -192.0f) location->x = -192.0f;
        else if (location->x >= 192.0f) location->x = 192.0f;
        item->velocity.SetPolar(angle, speed);
        ResetMotion(item);
        // At full power, power items turn into point-value ones.
        if (g_item_counters.power_units >= 100) {
            switch (kind) {
            case 10: case 11: kind = 5; break;
            case 1: case 4: kind = 9; break;
            }
        }
        if (item->kind == 3) ItemAnimation()->CreateOffset(393, location);
        item->kind = kind;
        item->display_kind = kind;
        if (kind == 10) {
            item->display_kind = 1;
            Entity_StartScript_00404f30(ItemAnimation(), &item->animation, 375);
        } else if (kind == 11) {
            item->display_kind = 4;
            Entity_StartScript_00404f30(ItemAnimation(), &item->animation, 378);
        } else {
            Entity_StartScript_00404f30(ItemAnimation(), &item->animation, kind + 374);
        }
        item->animation.primary_color = identifier;
        return 0;
    }
    // Kind 8 uses a 2048-entry ring; its count rises even when this ring slot
    // is occupied. Signed remainders preserve retail's cursor arithmetic.
    int cursor = special_cursor;
    SpawnItem_0041bb00* item = &special[cursor];
    int count = ++special_count;
    if (item->state == 0) {
        int variant;
        if (count >= 1024) variant = cursor % 32 + 16;
        else if (count >= 512) variant = cursor % 16 + 8;
        else if (count >= 256) variant = cursor % 8 + 4;
        else variant = cursor % 4;
        item->variant = variant;
        item->kind = 8;
        item->display_kind = 8;
        item->state = 5;
        item->position = *position;
        item->velocity.SetPolar(angle, speed);
        ResetMotion(item);
    }
    special_cursor = (special_cursor + 1) % 2048;
    return 0;
}
#pragma code_seg()
#pragma code_seg(".text$zzcontext")
extern "C" void __stdcall ItemSpawnContext(ItemGameCounters** counters) { *counters=&g_item_counters; }
#pragma code_seg()
