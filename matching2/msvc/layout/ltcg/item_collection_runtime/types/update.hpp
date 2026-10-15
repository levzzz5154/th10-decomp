#pragma once
#include "item_spawn.hpp"
#include "th10/platform/sound_queue.hpp"
#include "th10/game/player.hpp"
#include "th10/game/bomb.hpp"
#include "th10/render/animation_object_0043e5a0.hpp"


// These fields share the run-state object at 0x00474C40. In particular the
// point value and gauge are the same word, and the power is a signed short.
struct ItemRunState {
    int reserved_00, score;
    short power;
    unsigned short reserved_0a;
    int gauge, gauge_decay;
    FrameTimer gauge_timer;
    unsigned char reserved_28[8];
    int lives, point_tier;
    unsigned char reserved_38[0x18];
    int capped_count, reserved_54, power_accumulator;
    __declspec(noinline) void AdjustPower(int amount);
    __declspec(noinline) int AddPower(int amount);
    __declspec(noinline) void AddLives(int amount);
    __declspec(noinline) void AddScore(int amount);
    __declspec(noinline) void AddGauge(int amount);
    __declspec(noinline) void AdvanceGaugeTimer(int frames);
};
struct ItemAnimationHandle { unsigned int value; };
struct ItemAnimationNode {
    ItemAnimationNode* object;
    ItemAnimationNode* next;
    unsigned char reserved_008[0x0C];
    ItemAnimationNode* children;
    int children_flagged;
    unsigned char reserved_01c[0x340];
    unsigned int flags;
};
struct ItemAnimationLists {
    unsigned char reserved_000[0x72DAD4];
    ItemAnimationNode* primary;
    int reserved_72dad8;
    ItemAnimationNode* secondary;
    __declspec(noinline) ItemAnimationNode* Find(ItemAnimationHandle handle);
    __declspec(noinline) void* MarkForRemoval(ItemAnimationHandle handle);
};
struct ItemHud {
    // Opaque animation storage. Named accessors retain the actual overlapping
    // views used by the life banner and three power-digit animations.
    unsigned char storage[0x9ECC];
    ItemAnimationHandle& ExtendBanner() {
        return *reinterpret_cast<ItemAnimationHandle*>(storage+0x9E18);
    }
    Resource_0043e5a0*& AnimationResource() {
        return *reinterpret_cast<Resource_0043e5a0**>(storage+0x9EC8);
    }
    __declspec(noinline) void SetPowerDigits(int whole, int fraction);
    __declspec(noinline) void SetActiveCount(int count);
};
struct ItemFloatingText {
    unsigned char glyphs[12];
    Vector3 position;
    unsigned int color;
    FrameTimer timer;
    unsigned char reserved_30[8];
    unsigned char active, length;
    unsigned char reserved_3a[6];
};
struct ItemSmollScoreView {
    unsigned char reserved_000[0x14];
    int next_text;
    unsigned char reserved_018[0x3C4-0x18];
    ItemFloatingText texts[0x2D3];
    __declspec(noinline) void Spawn(int value, const Vector3* position, unsigned int color);
};

extern "C" {
extern ItemRunState data_00474c40;
extern ItemHud* g_front;
extern ItemSmollScoreView* g_smoll_score;
extern unsigned int g_input;
extern float data_00476f78;
extern float data_00470b04, data_00470b94, data_00470bf4, data_00470cdc;
extern float data_00470b08, data_00470be0, data_00470cd8, data_00470c38;
extern float data_00470cc4, data_00470cd4, data_00470cd0, data_00470ce0;
// 0x00426F70: rebuild the options after a power change.
__declspec(noinline) void __stdcall Player_RefreshOptions(Player* player);
__declspec(noinline) int __stdcall ItemManager_UpdateItems(ItemSpawnManager_0041bb00* manager);
}
__declspec(noinline) void** __stdcall ItemAnimation_CreatePrimaryBack(
    void* resource, void** output, int script, int layer);

typedef char ItemRunPowerOffset[offsetof(ItemRunState,power)==8?1:-1];
typedef char ItemRunGaugeOffset[offsetof(ItemRunState,gauge)==12?1:-1];
typedef char ItemRunLivesOffset[offsetof(ItemRunState,lives)==0x30?1:-1];
typedef char ItemRunPowerAccumulatorOffset[offsetof(ItemRunState,power_accumulator)==0x58?1:-1];
typedef char ItemFloatingTextSize[sizeof(ItemFloatingText)==0x40?1:-1];
typedef char ItemSmollScoreViewOffset[offsetof(ItemSmollScoreView,texts)==0x3C4?1:-1];
