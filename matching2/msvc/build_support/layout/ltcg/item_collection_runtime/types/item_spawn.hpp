#pragma once
#include <stddef.h>
#include "th10/game/item_record.hpp"
struct AnimationResourceFile;
__declspec(noinline) void __stdcall Entity_StartScript(AnimationResourceFile* resource, Entity* entity, int script);

struct ItemAnimationResources_0041bb00 {
    unsigned char reserved_000[0x3e0b50];
    void* item_animation;
};
extern "C" ItemAnimationResources_0041bb00* g_bullet_manager;

struct ItemSpawnManager {
    unsigned char reserved_000[0x14];
    Item items[2198];
    int live_count;
    int special_cursor;
    int special_count;
    __declspec(noinline) int Spawn(const Vector3* position,
        int kind,int identifier,float angle,float speed);
    // 0x0041BA50: turn the live items of kinds 1 and 4 into kind 9.
    __declspec(noinline) int ConvertItems();
};
typedef char ItemSpecialOffsetCheck[offsetof(ItemSpawnManager,items)+150*sizeof(Item)==0x24eb4?1:-1];
typedef char ItemCursorOffsetCheck[offsetof(ItemSpawnManager,special_cursor)==0x21ceb8?1:-1];
typedef char ItemLiveCountOffset[offsetof(ItemSpawnManager,live_count)==0x21CEB4?1:-1];
