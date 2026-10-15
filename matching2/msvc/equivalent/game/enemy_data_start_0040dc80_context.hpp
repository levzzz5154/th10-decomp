// What the 0x0040DC80 model and its link context share: the objects around
// the enemy and the helpers the tick calls.
#ifndef ENEMY_DATA_START_0040DC80_CONTEXT_HPP
#define ENEMY_DATA_START_0040DC80_CONTEXT_HPP
#include <math.h>
#include "script_resolver_00450470.hpp"
#include "th10/platform/sound_queue.hpp"
#include "th10/game/enemy_data_start_0040dc80.hpp"

// What the tick reads of the objects around the enemy.
struct Player_0040dc80 {
    unsigned char reserved_0000[0x3C0];
    float x;                             // +0x03C0
    unsigned char reserved_03c4[0x458 - 0x3C4];
    int shot_mode;                       // +0x0458
    unsigned char reserved_045c[0x3504 - 0x45C];
    EnemyRecord_0040dc80* target;        // +0x3504
    unsigned char target_chosen;         // +0x3508

    // 0x00428630: total damage of the player's shots overlapping the box.
    // Retail calls it with a null receiver.
    __declspec(noinline) int Sweep(Player_0040dc80* player, const PolarVec3* center, const Vec2* size);
};
struct Stage_0040dc80 {
    unsigned char reserved_00[0x28];
    int covered;                         // +0x28

    int Covered() const { return covered; }
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
extern Player_0040dc80* data_00477834;
extern Stage_0040dc80* data_004776ec;
extern GameThread_0040dc80* data_004776f4;
extern Gui_0040dc80* data_0047770c;
extern AnimationManager_0040dc80* data_00491c10;
extern ScoreState_0040dc80 data_00474c40;
extern int data_00474c50;                // set once any enemy was open to shots this frame
extern PolarVec3 data_00491e6c;          // the scroll applied to unscrolled enemies
}

// 0x00450700: restart the record's script at a named entry.
__declspec(noinline) int __fastcall BindName_00450700(const char* name, EnemyRecord_0040dc80* record);
// 0x0040E5F0: the death effects; nonzero when the enemy is gone.
__declspec(noinline) int __stdcall Enemy_ReleaseOnDeath_0040e5f0(EnemyRecord_0040dc80* record);
// 0x004266B0: touch the player.
__declspec(noinline) int __fastcall FieldContact_004266b0(
    const PolarVec3* position, Player_0040dc80* player, const Vec2* size);
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
