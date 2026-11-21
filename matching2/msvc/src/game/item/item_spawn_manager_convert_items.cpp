// 0x0041BA50: turn the live normal items of kinds 1 and 4 into kind 9.
//
// Each such item is retired, a kind 9 item is thrown up from its position,
// and a flash starts there. The manager arrives in ESI.
#include "../../../build_support/layout/ltcg/item_collection_runtime/types/item_spawn.hpp"

struct Vector3;
void** __stdcall ItemAnimation_CreateOffset(
    void* resource, void** out, int index, const Vector3* position);

#pragma code_seg(".text$f0041ba50F")
int ItemSpawnManager::ConvertItems() {
    for (int index = 0; index < 150; ++index) {
        Item* item = &items[index];
        if (item->motion.state == Inactive)
            continue;
        int kind = item->motion.kind;
        if (kind != ITEM_POWER_SMALL && kind != ITEM_POWER_LARGE)
            continue;
        item->motion.state = Inactive;
        if (kind == ITEM_POWER_SMALL) {
            Spawn(&item->motion.position, ITEM_FAITH_CONVERTED, -1, -1.5707964f, 2.2f);
        } else if (kind == ITEM_POWER_LARGE) {
            Spawn(&item->motion.position, ITEM_FAITH_CONVERTED, -1, -1.5707964f, 2.2f);
        } else if (kind == ITEM_POWER_SMALL_BOSS || kind == ITEM_POWER_LARGE_BOSS) {
            Spawn(&item->motion.position, ITEM_POINT_FULL_POWER, -1, -1.5707964f, 2.2f);
        } else {
            continue;
        }
        void* flash;
        ItemAnimation_CreateOffset(
            g_bullet_manager->item_animation, &flash, 0x189, &item->motion.position);
    }
    return 0;
}
#pragma code_seg()
