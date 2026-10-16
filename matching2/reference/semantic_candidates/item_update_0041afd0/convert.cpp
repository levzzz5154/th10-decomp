// 0x0041BA50: turn the live normal items of kinds 1 and 4 into kind 9.
//
// Each such item is retired, a kind 9 item is thrown up from its position,
// and a flash starts there. The manager arrives in ESI.
#include "th10/game/item_spawn.hpp"

struct Vector3;
void** __stdcall ItemAnimation_CreateOffset_00448db0(
    void* resource, void** out, int index, const Vector3* position);

#pragma code_seg(".text$40convert")
int ItemSpawnManager_0041bb00::ConvertItems() {
    for (int index = 0; index < 150; ++index) {
        SpawnItem_0041bb00* item = &items[index];
        if (item->motion.state == 0)
            continue;
        int kind = item->motion.kind;
        if (kind != 1 && kind != 4)
            continue;
        item->motion.state = 0;
        if (kind == 1) {
            Spawn(&item->motion.position, 9, -1, -1.5707964f, 2.2f);
        } else if (kind == 4) {
            Spawn(&item->motion.position, 9, -1, -1.5707964f, 2.2f);
        } else if (kind == 10 || kind == 11) {
            Spawn(&item->motion.position, 5, -1, -1.5707964f, 2.2f);
        } else {
            continue;
        }
        void* flash;
        ItemAnimation_CreateOffset_00448db0(
            data_004776f0->item_animation, &flash, 0x189, &item->motion.position);
    }
    return 0;
}
#pragma code_seg()
