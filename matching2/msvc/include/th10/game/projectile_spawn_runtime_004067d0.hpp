#ifndef TH10_GAME_PROJECTILE_SPAWN_RUNTIME_004067D0_HPP
#define TH10_GAME_PROJECTILE_SPAWN_RUNTIME_004067D0_HPP

// Shared record views for the projectile spawn path: 0x004067D0 (spawn one
// grid cell into a free 0x7F0 slot) and 0x00406D90 (run the slot's command
// script). Every offset below was read off the retail accessors.
#include <stddef.h>
#include "th10/math/timer.hpp"
#include "th10/math/vector.hpp"
#include "th10/game/entity.hpp"

// One scheduler slot of a projectile record; the setter at 0x00405410 is a
// native-LTCG member whose receiver retail keeps in EAX.
struct PlayerSchedulerRecord {
    int field_00;       // 0x00 previous value
    int field_04;       // 0x04 value
    float field_08;     // 0x08 value as float
    int field_0C;       // 0x0C default marker
    unsigned int flags_10;  // 0x10 initialised flag

    __declspec(noinline) void SetSchedulerValue(int value);
};
typedef char SchedulerRecord_size[sizeof(PlayerSchedulerRecord) == 20 ? 1 : -1];

// The score polar vector whose setter at 0x00408750 retail compiled with GCC.
struct ScoreGameplayPolarVector {
    float x;
    float y;

    __declspec(noinline) ScoreGameplayPolarVector* SetScorePolar(float angle, float radius);
};

// One 24-byte command of a spawn script: two floats, two ints, the command
// id and the guard word that stops the script once motion flags are set.
struct SpawnCommandRecord {
    float value_a;      // +0x00
    float value_b;      // +0x04
    int value_c;        // +0x08
    int value_d;        // +0x0C
    int command;        // +0x10
    int guard;          // +0x14, compared as a raw dword
};
typedef char SpawnCommandRecord_size[sizeof(SpawnCommandRecord) == 24 ? 1 : -1];

// The full 0x7F0 projectile slot, as far as the spawn path and the command
// interpreter touch it.
struct ProjectileSpawnRecord {
    unsigned int flags;                     // 0x000
    int countdown;                          // 0x004
    Entity sprite;                          // 0x008 (0x3AC bytes)
    Vec3 position;                          // 0x3B4
    Vec3 velocity;                          // 0x3C0
    unsigned char reserved_3cc[0x3D8 - 0x3CC];
    float fall_speed_3d8;                   // 0x3D8
    unsigned char reserved_3dc[0x3E4 - 0x3DC];
    float angle_3e4;                        // 0x3E4
    unsigned char reserved_3e8[0x3F0 - 0x3E8];
    float width_3f0;                        // 0x3F0
    float height_3f4;                       // 0x3F4
    FrameTimer timer_3f8;                   // 0x3F8
    FrameTimer timer_40c;                   // 0x40C
    int turn_420;                           // 0x420
    unsigned char reserved_424[0x434 - 0x424];
    int bounds_grace;                       // 0x434
    int death_animation;                    // 0x438
    unsigned int motion_flags;              // 0x43C
    unsigned int field_440;                 // 0x440
    unsigned char reserved_444[0x446 - 0x444];
    unsigned short state;                   // 0x446: 0 free, 1 active, 2 lit, 5 leaving
    unsigned char reserved_448[0x450 - 0x448];
    int lifetime;                           // 0x450
    unsigned int field_454;                 // 0x454
    int field_458;                          // 0x458 sound id / score marker
    int command_index;                      // 0x45C
    unsigned int field_460;                 // 0x460
    SpawnCommandRecord commands[18];        // 0x464
    PlayerSchedulerRecord scheduler_614;    // 0x614
    unsigned char reserved_628[0x638 - 0x628];
    unsigned int field_638;                 // 0x638
    unsigned char reserved_63c[0x648 - 0x63C];
    PlayerSchedulerRecord scheduler_648;    // 0x648
    float field_65c;                        // 0x65C
    float field_660;                        // 0x660
    ScoreGameplayPolarVector polar_664;     // 0x664
    unsigned char reserved_66c[0x670 - 0x66C];
    int field_670;                          // 0x670
    unsigned char reserved_674[0x67C - 0x674];
    PlayerSchedulerRecord scheduler_67c;    // 0x67C
    float field_690;                        // 0x690
    float field_694;                        // 0x694
    unsigned char reserved_698[0x6A4 - 0x698];
    int field_6a4;                          // 0x6A4
    unsigned char reserved_6a8[0x6B0 - 0x6A8];
    FrameTimer timer_6b0;                   // 0x6B0
    float field_6c4;                        // 0x6C4
    float field_6c8;                        // 0x6C8
    unsigned char reserved_6cc[0x6D8 - 0x6CC];
    int field_6d8;                          // 0x6D8
    int field_6dc;                          // 0x6DC
    unsigned int field_6e0;                 // 0x6E0
    unsigned char reserved_6e4[0x6F8 - 0x6E4];
    float field_6f8;                        // 0x6F8
    unsigned char reserved_6fc[0x70C - 0x6FC];
    unsigned int field_70c;                 // 0x70C
    int field_710;                          // 0x710
    unsigned char reserved_714[0x718 - 0x714];
    FrameTimer immunity_timer;              // 0x718
    unsigned char reserved_72c[0x74C - 0x72C];
    PlayerSchedulerRecord scheduler_74c;    // 0x74C
    unsigned char reserved_760[0x780 - 0x760];
    PlayerSchedulerRecord scheduler_780;    // 0x780
    unsigned char reserved_794[0x7B4 - 0x794];
    FrameTimer timer_7b4;                   // 0x7B4
    float field_7c8;                        // 0x7C8
    float field_7cc;                        // 0x7CC
    unsigned char reserved_7d0[0x7DC - 0x7D0];
    int field_7dc;                          // 0x7DC
    unsigned char reserved_7e0[0x7EA - 0x7E0];
    short field_7ea;                        // 0x7EA
    short field_7ec;                        // 0x7EC
    unsigned char reserved_7ee[2];
};
typedef char ProjectileSpawnRecord_size[sizeof(ProjectileSpawnRecord) == 0x7F0 ? 1 : -1];
typedef char ProjectileSpawnRecord_state[offsetof(ProjectileSpawnRecord, state) == 0x446 ? 1 : -1];
typedef char ProjectileSpawnRecord_commands[offsetof(ProjectileSpawnRecord, commands) == 0x464 ? 1 : -1];

// The projectile manager: 2000 slots at +0x60, the round-robin cursor at
// +0x10 and the animation resource at +0x3E0B50.
struct ProjectileSpawnManager {
    unsigned char reserved_000[0x10];
    ProjectileSpawnRecord* current;             // +0x10
    unsigned char reserved_014[0x60 - 0x14];
    ProjectileSpawnRecord records[2000];        // +0x60
    unsigned char reserved_3e0360[0x3E0B50 - 0x3E0360];
    void* animations;                           // +0x3E0B50
};
typedef char ProjectileSpawnManager_current[offsetof(ProjectileSpawnManager, current) == 0x10 ? 1 : -1];
typedef char ProjectileSpawnManager_animations[offsetof(ProjectileSpawnManager, animations) == 0x3E0B50 ? 1 : -1];

// The spawn request: an origin, a command script, a grid and the per-colour
// layout fields 0x4067D0 interprets.
struct ProjectileBlueprint_004067d0 {
    short colour;                               // 0x00
    short script_offset;                        // 0x02
    float field_04;                             // 0x04
    float field_08;                             // 0x08
    float field_0c;                             // 0x0C
    float x_base;                               // 0x10
    float x_spacing;                            // 0x14
    float y_head;                               // 0x18
    float y_tail;                               // 0x1C
    SpawnCommandRecord commands[18];            // 0x20
    unsigned char reserved_1d0[0x1F4 - 0x1D0];
    short columns;                              // 0x1F4
    short rows;                                 // 0x1F6
    unsigned short layout;                      // 0x1F8, zero-extended by the switch
    unsigned char reserved_1fa[2];
    unsigned int flags;                         // 0x1FC
    int sound;                                  // 0x200
    int field_204;                              // 0x204
    int command_index;                          // 0x208
};
typedef char ProjectileBlueprint_commands[offsetof(ProjectileBlueprint_004067d0, commands) == 0x20 ? 1 : -1];
typedef char ProjectileBlueprint_columns[offsetof(ProjectileBlueprint_004067d0, columns) == 0x1F4 ? 1 : -1];
typedef char ProjectileBlueprint_flags[offsetof(ProjectileBlueprint_004067d0, flags) == 0x1FC ? 1 : -1];

// A per-colour constant table (int / float variants).
extern "C" int data_00474170[];                 // 0x00474170 first script per colour
extern "C" float data_004741e0[];               // 0x004741E0 speed per colour
extern "C" int data_00474250[];                 // 0x00474250 per colour
extern "C" int data_004742c0[];                 // 0x004742C0 death table selector
extern "C" int data_0047432c[];                 // 0x0047432C death animation per script
extern "C" float data_00470b0c;                 // 0.5
extern "C" float data_00470b14;                 // 2*pi
extern "C" float data_00470b18;                 // pi
extern "C" float data_00470b50;                 // -990
extern "C" float data_00470b60;                 // -1
extern "C" float data_00470c40;                 // 4
extern "C" float data_00470cc8;                 // -999
extern "C" float data_00470ccc;                 // 990
extern "C" float g_game_speed;                 // frame delta, 1.0 normally

#endif
