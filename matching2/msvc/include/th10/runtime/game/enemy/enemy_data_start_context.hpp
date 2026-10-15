// What the 0x0040DC80 model and its link context share: the objects around
// the enemy and the helpers the tick calls.
#ifndef ENEMY_DATA_START_0040DC80_CONTEXT_HPP
#define ENEMY_DATA_START_0040DC80_CONTEXT_HPP
#include <math.h>
#include "script_resolver_00450470.hpp"
#include "th10/platform/sound_queue.hpp"
#include "th10/game/enemy_data_start_0040dc80.hpp"
#include "th10/game/player.hpp"
#include "th10/game/bomb.hpp"

// What the tick reads of the objects around the enemy.
struct PlayerDamage {
    // 0x00428630: total damage of the player's shots overlapping the box.
    // Retail calls it with a null receiver.
    __declspec(noinline) int Sweep(Player* player, const PolarVec3* center, const Vec2* size);
};
struct GameThread_0040dc80 {
    unsigned char reserved_0000[0x378C];
    unsigned int flags;                  // +0x378C
};
struct Gui_0040dc80 {
    unsigned char reserved_0000[0x9DA4];
    unsigned int boss_bar_flags;         // +0x9DA4
};
struct Animation_0040dc80 {
    unsigned char reserved_000[0x300];
    unsigned int color;                  // +0x300
    unsigned char reserved_304[0x35C - 0x304];
    unsigned int flags;                  // +0x35C
};
struct AnimationManager_0040dc80;
struct ScoreState_0040dc80 {
    __declspec(noinline) void AddScore(int amount);     // 0x00409D90
};

extern "C" {
extern GameThread_0040dc80* g_card;
extern Gui_0040dc80* g_front;
extern AnimationManager_0040dc80* g_sprt_ctrl;
extern ScoreState_0040dc80 g_globals;
extern int g_enemy_hittable;                // set once any enemy was open to shots this frame
extern PolarVec3 g_enemy_scroll;          // the scroll applied to unscrolled enemies
}

// 0x00450700: restart the record's script at a named entry.
__declspec(noinline) int __fastcall BindName_00450700(const char* name, EnemyRecord_0040dc80* record);
// 0x0040E5F0: the death effects; nonzero when the enemy is gone.
__declspec(noinline) int __stdcall Enemy_ReleaseOnDeath_0040e5f0(EnemyRecord_0040dc80* record);
// 0x004266B0: touch the player.
__declspec(noinline) int __fastcall FieldContact_004266b0(
    const PolarVec3* position, Player* player, const Vec2* size);
// 0x00449350, 0x004492F0: place an animation in field or in screen coordinates.
__declspec(noinline) void __fastcall SetAnimationTranslatedPosition_00449350(
    AnimationManager_0040dc80* manager, const PolarVec3* position, ScriptChangeHandle id);
__declspec(noinline) void __fastcall Animation_SetPosition(
    AnimationManager_0040dc80* manager, const PolarVec3* position, ScriptChangeHandle id);
// 0x004491C0: the running animation a handle names.
// Retail calls it as a member that ignores its receiver.
struct AnimationFinder_0040dc80 {
    __declspec(noinline) Animation_0040dc80* __fastcall Find(AnimationManager_0040dc80* manager, ScriptChangeHandle id);
};
inline Animation_0040dc80* AnimationManager_Find_004491c0(AnimationManager_0040dc80* manager, ScriptChangeHandle id) {
    return reinterpret_cast<AnimationFinder_0040dc80*>(manager)->Find(manager, id);
}
#endif
