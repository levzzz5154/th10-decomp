// What the 0x0040DC80 model and its link context share: the objects around
// the enemy and the helpers the tick calls.
#ifndef ENEMY_DATA_START_0040DC80_CONTEXT_HPP
#define ENEMY_DATA_START_0040DC80_CONTEXT_HPP
#include <math.h>
#include "th10/script/script_resolver.hpp"
#include "th10/platform/sound_queue.hpp"
#include "th10/game/enemy_data_start.hpp"
#include "th10/game/player.hpp"
#include "th10/game/bomb.hpp"

// What the tick reads of the objects around the enemy.
struct PlayerDamage {
    // 0x00428630: total damage of the player's shots overlapping the box.
    // Retail calls it with a null receiver.
    __declspec(noinline) int Sweep(Player* player, const PolarVec3* center, const Vec2* size);
};
struct GameThreadFlagsView {
    unsigned char reserved_0000[0x378C];
    unsigned int flags;                  // +0x378C
};
struct Gui2 {
    unsigned char reserved_0000[0x9DA4];
    unsigned int boss_bar_flags;         // +0x9DA4
};
struct Animation2 {
    unsigned char reserved_000[0x300];
    unsigned int color;                  // +0x300
    unsigned char reserved_304[0x35C - 0x304];
    unsigned int flags;                  // +0x35C
};
struct EnemyAnmManagerView;
struct ScoreState2 {
    __declspec(noinline) void AddScore(int amount);     // 0x00409D90
};

extern "C" {
extern GameThreadFlagsView* g_card;
extern Gui2* g_front;
extern EnemyAnmManagerView* g_sprt_ctrl;
extern ScoreState2 g_globals;
extern int g_enemy_hittable;                // set once any enemy was open to shots this frame
extern PolarVec3 g_enemy_scroll;          // the scroll applied to unscrolled enemies
}

// 0x00450700: restart the record's script at a named entry.
__declspec(noinline) int __fastcall BindName(EnemyRecord* record, const char* name);
// 0x0040E5F0: the death effects; nonzero when the enemy is gone.
__declspec(noinline) int __stdcall Enemy_ReleaseOnDeath(EnemyRecord* record);
// 0x004266B0: touch the player.
__declspec(noinline) int __fastcall FieldContact(
    const PolarVec3* position, Player* player, const Vec2* size);
// 0x00449350, 0x004492F0: place an animation in field or in screen coordinates.
__declspec(noinline) void __fastcall SetAnimationTranslatedPosition(
    EnemyAnmManagerView* manager, const PolarVec3* position, ScriptChangeHandle id);
__declspec(noinline) void __fastcall Animation_SetPosition(
    EnemyAnmManagerView* manager, const PolarVec3* position, ScriptChangeHandle id);
// 0x004491C0: the running animation a handle names.
// Retail calls it as a member that ignores its receiver.
struct AnimationFinder {
    __declspec(noinline) Animation2* __fastcall Find(EnemyAnmManagerView* manager, ScriptChangeHandle id);
};
inline Animation2* AnimationManager_Find(EnemyAnmManagerView* manager, ScriptChangeHandle id) {
    return reinterpret_cast<AnimationFinder*>(manager)->Find(manager, id);
}
#endif
