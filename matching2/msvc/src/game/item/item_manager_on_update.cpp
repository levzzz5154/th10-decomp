#include "th10/game/item_manager_destructor.hpp"

// 0x0041BA00: skip the item update when the active scene sets flags 0, 2 or 10.
struct SceneFlags {
    unsigned char unknown_00[0x58];
    unsigned int flags_58;               // +0x58
};

extern "C" SceneFlags* g_game;  // 0x00477810
struct ItemSpawnManager;
extern "C" int __stdcall ItemManager_UpdateItems(ItemSpawnManager* manager);

int ItemManager::OnUpdate() {
    SceneFlags* scene = g_game;
    if (scene != 0 && ((((scene->flags_58 >> 2) | scene->flags_58) & 1) != 0 ||
                       (scene->flags_58 & 0x400) != 0))
        return 1;
    return ItemManager_UpdateItems(reinterpret_cast<ItemSpawnManager*>(this));
}
