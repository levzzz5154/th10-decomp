#ifndef TH10_GAME_ENEMY_DATA_START_0040DC80_HPP
#define TH10_GAME_ENEMY_DATA_START_0040DC80_HPP
#include <stddef.h>
#include "th10/game/polar_motion.hpp"
#include "th10/math/interpolator.hpp"
#include "th10/math/trajectory_vector.hpp"
#include "th10/math/vector.hpp"
#include "th10/script/ecl_children.hpp"

// The motion records subtract as vectors; the interpolators hand back Vec3.
inline PolarVec3 operator-(const Vec3& a, const PolarVec3& b) {
    PolarVec3 difference;
    difference.x = a.x - b.x;
    difference.y = a.y - b.y;
    difference.z = a.z - b.z;
    return difference;
}
inline PolarVec3 operator-(const PolarVec3& a, const PolarVec3& b) {
    PolarVec3 difference;
    difference.x = a.x - b.x;
    difference.y = a.y - b.y;
    difference.z = a.z - b.z;
    return difference;
}

// 0x004496D0: restart the animation a handle names with another script.
struct ScriptChangeHandle {
    int id;
    __declspec(noinline) void ChangeScript(int index);
};

struct EnemyRecord;

// The enemy proper as the per-frame tick at 0x0040DC80 reads it (0x14DC
// bytes at +0x103C of the record).
struct EnemyTick {
    PolarMotion previous;                         // +0x0000: last frame's `final`
    PolarMotion final;                            // +0x002C: where the enemy is drawn and hit
    PolarMotion relative;                         // +0x0058: offset motion, added to `absolute`
    PolarMotion absolute;                         // +0x0084
    Vec2 hit_size;                                // +0x00B0: against the player's shots
    Vec2 contact_size;                            // +0x00B8: against the player
    ScriptChangeHandle animations[8];             // +0x00C0
    unsigned char reserved_00e0[0xF4 - 0xE0];
    int animation_script;                         // +0x00F4: base script of animations[0]
    int facing;                                   // +0x00F8: -1 left, 0 idle, 1 right
    unsigned char reserved_00fc[0x11C - 0xFC];
    FrameTimer clock;                             // +0x011C
    unsigned char reserved_0130[0x13C - 0x130];
    Interpolator<Vec3> relative_path;             // +0x013C
    Interpolator<Vec3> absolute_path;             // +0x0188
    Interpolator<TrajectoryVec2> relative_heading;   // +0x01D4: angle, speed
    Interpolator<TrajectoryVec2> absolute_heading;   // +0x0210
    Interpolator<TrajectoryVec2> relative_orbit;     // +0x024C: radius, radius step
    Interpolator<TrajectoryVec2> absolute_orbit;     // +0x0288
    unsigned char reserved_02c4[0x13A4 - 0x2C4];
    Vec2 visible_size;                            // +0x13A4: kept while this overlaps the field
    Vec2 limit_center;                            // +0x13AC
    Vec2 limit_size;                              // +0x13B4
    int bonus;                                    // +0x13BC: added to the score on death
    int health;                                   // +0x13C0
    unsigned char reserved_13c4[4];
    int spell_delta;                              // +0x13C8 (+0x2404 of the record), see spell_timer.cpp
    unsigned char reserved_13cc[0x1414 - 0x13CC];
    int flash_frames;                             // +0x1414
    unsigned char reserved_1418[4];
    FrameTimer invulnerable_timer;                // +0x141C
    FrameTimer contact_timer;                     // +0x1430: no contact damage while running
    unsigned int flags;                           // +0x1444
    int covered_script;                           // +0x1448: while the stage flag at +0x28 is set
    int uncovered_script;                         // +0x144C
    unsigned char reserved_1450[0x14D8 - 0x1450];
    EnemyRecord* record;                 // +0x14D8
};
typedef char EnemyTickFacing[offsetof(EnemyTick, facing) == 0xF8 ? 1 : -1];
typedef char EnemyTickClock[offsetof(EnemyTick, clock) == 0x11C ? 1 : -1];
typedef char EnemyTickPath[offsetof(EnemyTick, absolute_path) == 0x188 ? 1 : -1];
typedef char EnemyTickOrbit[offsetof(EnemyTick, absolute_orbit) == 0x288 ? 1 : -1];
typedef char EnemyTickVisible[offsetof(EnemyTick, visible_size) == 0x13A4 ? 1 : -1];
typedef char EnemyTickFlash[offsetof(EnemyTick, flash_frames) == 0x1414 ? 1 : -1];
typedef char EnemyTickFlags[offsetof(EnemyTick, flags) == 0x1444 ? 1 : -1];
typedef char EnemyTickSize[sizeof(EnemyTick) == 0x14DC ? 1 : -1];

// EnemyTick::flags.
enum {
    ENEMY_NO_HIT = 0x1,
    ENEMY_NO_CONTACT = 0x2,
    ENEMY_KEEP_OFFSCREEN = 0x4,
    ENEMY_NO_DAMAGE = 0x8,
    ENEMY_INTANGIBLE = 0x10,
    ENEMY_INVINCIBLE = 0x40,
    ENEMY_SEEN = 0x100,
    ENEMY_LIMITED = 0x200,
    ENEMY_TICKED = 0x400,
    ENEMY_FACES = 0x1000,
    ENEMY_HIT = 0x2000,
    ENEMY_BOSS = 0x8000,
    ENEMY_UNSCROLLED = 0x40000,
    ENEMY_UNTARGETED = 0x80000,
    ENEMY_SWAPS_SCRIPT = 0x100000,
    ENEMY_SCRIPT_SWAPPED = 0x200000
};

// 0x0040DC80: one frame of an enemy: motion, the off-screen test, its
// script, damage from the player's shots, contact, animation and timers.
// 0 to keep the enemy, 1 when it died, -1 when it left or its script ended.
// The 0x2518-byte enemy record: the script interpreter, then the enemy.
struct ScriptTable_00450470;
struct ScriptFrame_0040dc80 {
    int time;
    int instruction;
};
struct EnemyRecord {
    void* vtable;
    ScriptFrame_0040dc80* current;                // +0x0004
    unsigned char reserved_0008[0x102C - 8];
    ScriptTable_00450470* table;                  // +0x102C
    unsigned char reserved_1030[0x103C - 0x1030];
    EnemyTick data;                      // +0x103C

    // 0x004127A0: the script entry of a spell slot that has come due, or 0.
    __declspec(noinline) const char* AdvanceSlots();
    // 0x0040C6E0, 0x0040C730: drop what the running script owns.
    __declspec(noinline) void ClearResourceList();
    __declspec(noinline) void ResetScript();
};
typedef char EnemyRecordSize[sizeof(EnemyRecord) == 0x2518 ? 1 : -1];

extern "C" __declspec(noinline) int __stdcall EnemyDataStart(EnemyTick* enemy);
#endif
