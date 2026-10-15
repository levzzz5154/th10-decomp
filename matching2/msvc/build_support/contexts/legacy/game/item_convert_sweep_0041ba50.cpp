// 0x0041BA50: turn the live normal items of kinds 1 and 4 into kind 9.
//
// Each such item is retired, a kind 9 item is thrown up from its position,
// and a flash starts there. The manager arrives in ESI.
#include "th10/game/item_spawn_0041bb00.hpp"
#include "th10/game/player_update_collision.hpp"

struct Vector3;
void** __stdcall ItemAnimation_CreateOffset(
    void* resource, void** out, int index, const Vector3* position);

#pragma code_seg(".text$079zz_convert")
int ItemSpawnManager::ConvertItems() {
    for (int index = 0; index < 150; ++index) {
        SpawnItem* item = &normal[index];
        if (item->state == 0)
            continue;
        int kind = item->kind;
        if (kind != 1 && kind != 4)
            continue;
        item->state = 0;
        if (kind == 1) {
            Spawn(item->position, 9, -1, -1.5707964f, 2.2f);
        } else if (kind == 4) {
            Spawn(item->position, 9, -1, -1.5707964f, 2.2f);
        } else if (kind == 10 || kind == 11) {
            Spawn(item->position, 5, -1, -1.5707964f, 2.2f);
        } else {
            continue;
        }
        void* flash;
        ItemAnimation_CreateOffset(
            g_bullet_manager->item_animation, &flash, 0x189, (const Vector3*)item->position);
    }
    return 0;
}
#pragma code_seg()
