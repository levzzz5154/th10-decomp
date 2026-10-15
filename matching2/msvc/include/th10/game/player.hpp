#pragma once
// The player object: one 0x4478-byte instance, created at stage start and
// reached through g_player (0x00477834).
//
// Field names follow how the recovered code uses each field. Where a field is
// only stored or copied and its purpose is not established, it keeps an
// offset name (unknown_XXX).
#include <stddef.h>
#include "th10/game/entity.hpp"
#include "th10/math/timer.hpp"

struct SchedulerTask;
struct ShotTypeFile;      // the loaded shot-type (.sht) file
struct ShotDefinition;    // one shot entry of a shot-type file
struct Point3_OrientedRect;

// Player positions are kept in hundredths of a pixel; Player::position is the
// same point as floats.
struct FixedPoint {
    int x, y;
};

enum PlayerStateId {
    PLAYER_RESPAWNING = 0,  // flying in from the bottom edge
    PLAYER_ALIVE = 1,
    PLAYER_DYING = 2,       // drops the power-item fan, then respawns or ends the game
    PLAYER_STATE_3 = 3,     // clears bullets 15 frames in; entered from outside the player
    PLAYER_HIT = 4          // the deathbomb window: 8 frames to bomb before dying
};

enum PlayerDirection {
    PLAYER_DIRECTION_NONE = 0, PLAYER_DIRECTION_UP, PLAYER_DIRECTION_DOWN,
    PLAYER_DIRECTION_LEFT, PLAYER_DIRECTION_RIGHT, PLAYER_DIRECTION_UP_LEFT,
    PLAYER_DIRECTION_UP_RIGHT, PLAYER_DIRECTION_DOWN_LEFT, PLAYER_DIRECTION_DOWN_RIGHT
};

// A box as its two corners; the player refreshes these every frame from its
// position and the matching half-size.
struct PlayerBox {
    Vector3 min, max;
};

// One shot the player has fired (0x5C bytes).
struct PlayerBullet {
    FrameTimer timer;                  // +0x00
    Vector3 position;                  // +0x14
    Vector3 velocity;                  // +0x20
    float speed;                       // +0x2C
    float angle;                       // +0x30
    float unknown_34, unknown_38;      // +0x34
    unsigned char motion_flags;        // +0x3C
    unsigned char pad_3d[3];
    int state;                         // +0x40, 0 = free, 1 = flying
    unsigned int animation;            // +0x44, animation handle
    unsigned int hit_animation;        // +0x48
    int unknown_4c;                    // +0x4C
    int hit_this_frame;                // +0x50
    int has_hit;                       // +0x54
    ShotDefinition* definition;        // +0x58
};

// One of the four options (familiars) that orbit the player (0x98 bytes).
struct PlayerOption {
    int active;                        // +0x00
    unsigned char unknown_04[0x30];
    FixedPoint target;                 // +0x34, where the option is heading
    FixedPoint position;               // +0x3C
    FixedPoint unfocused_offset;       // +0x44, from the player
    FixedPoint focused_offset;         // +0x4C
    unsigned char unknown_54[0x14];
    unsigned int animation;            // +0x68
    unsigned int second_animation;     // +0x6C
    unsigned char unknown_70[0x1C];
    int reset_position;                // +0x8C
    int (__fastcall* update)(PlayerOption* option);  // +0x90
    int unknown_94;
};

// An area that damages enemies: a bomb, or the burst around a respawn
// (0x6C bytes).
struct PlayerDamageSource {
    float radius;                      // +0x00
    float radius_growth;               // +0x04
    float angle;                       // +0x08
    float angle_step;                  // +0x0C
    float width, height;               // +0x10
    Vector3 position;                  // +0x18
    unsigned char motion_24[0x20];     // +0x24, the rest of its motion record
    FrameTimer lifetime;               // +0x44, counts down to zero
    int damage;                        // +0x58
    int damage_dealt;                  // +0x5C
    int damage_limit;                  // +0x60
    int interval;                      // +0x64
    unsigned int flags;                // +0x68, bit 0 = in use
};

struct Player {
    unsigned char unknown_000[8];
    SchedulerTask* update_task;              // +0x008
    SchedulerTask* draw_task;                // +0x00C
    void* animation_file;                    // +0x010, the character's ANM
    Entity sprite;                           // +0x014
    Vector3 position;                        // +0x3C0
    FixedPoint fixed_position;               // +0x3CC
    int speed;                               // +0x3D4, fixed-point units per frame
    int focused_speed;                       // +0x3D8
    int diagonal_speed;                      // +0x3DC
    int focused_diagonal_speed;              // +0x3E0
    unsigned char unknown_3e4[0xC];
    FixedPoint velocity;                     // +0x3F0
    unsigned char unknown_3f8[0xC];
    PlayerBox hitbox;                        // +0x404
    Vector3 hitbox_half_size;                // +0x41C
    Vector3 item_box_size;                   // +0x428
    Vector3 item_attract_half_size;          // +0x434
    Vector3 death_position;                  // +0x440, where the last death happened
    FixedPoint previous_velocity;            // +0x44C
    PlayerDirection direction;               // +0x454
    PlayerStateId state;                     // +0x458
    ShotTypeFile* shot_type;                 // +0x45C
    FrameTimer shot_timer;                   // +0x460
    FrameTimer state_timer;                  // +0x474, frames in the current state
    FrameTimer focus_timer;                  // +0x488
    PlayerBullet bullets[128];               // +0x49C
    unsigned int focus_marker;               // +0x329C, animation handle
    PlayerOption options[4];                 // +0x32A0
    int option_count;                        // +0x3500, power level in whole units
    void* homing_target;                     // +0x3504, an enemy
    char has_homing_target;                  // +0x3508
    unsigned char pad_3509[3];
    PlayerDamageSource damage_sources[32];   // +0x350C
    unsigned char unknown_428c[0x68];
    int unknown_42f4[5];                     // +0x42F4
    int focus_transition_age;                // +0x4308
    FrameTimer invulnerability_timer;        // +0x430C
    unsigned int unknown_4320;               // +0x4320
    PlayerBox item_collect_box;              // +0x4324, position +- item_box_size / 2
    PlayerBox focused_item_attract_box;      // +0x433C, position +- item_attract_half_size
    PlayerBox item_attract_box;              // +0x4354, position +- item_box_size
    FixedPoint position_history[33];         // +0x436C, newest first; the options trail it
    int focused;                             // +0x4474

    // 0x004267F0: test the player against a laser: a rectangle that starts at
    // `origin`, runs `length` along `angle` and is `width` wide. Returns 1 for
    // a hit (and calls Player_Hit), 2 for a graze (within 1.5 widths of the
    // centre line), 0 otherwise.
    __declspec(noinline) int CheckLaserHit(const Point3_OrientedRect* origin, float angle, float width,
                                           float length);
};

#define PLAYER_CHECK(name, expression) typedef char player_check_##name[(expression) ? 1 : -1]
PLAYER_CHECK(size, sizeof(Player) == 0x4478);
PLAYER_CHECK(bullet_size, sizeof(PlayerBullet) == 0x5C);
PLAYER_CHECK(option_size, sizeof(PlayerOption) == 0x98);
PLAYER_CHECK(damage_source_size, sizeof(PlayerDamageSource) == 0x6C);
PLAYER_CHECK(sprite, offsetof(Player, sprite) == 0x14);
PLAYER_CHECK(position, offsetof(Player, position) == 0x3C0);
PLAYER_CHECK(velocity, offsetof(Player, velocity) == 0x3F0);
PLAYER_CHECK(hitbox, offsetof(Player, hitbox) == 0x404);
PLAYER_CHECK(direction, offsetof(Player, direction) == 0x454);
PLAYER_CHECK(state, offsetof(Player, state) == 0x458);
PLAYER_CHECK(bullets, offsetof(Player, bullets) == 0x49C);
PLAYER_CHECK(focus_marker, offsetof(Player, focus_marker) == 0x329C);
PLAYER_CHECK(option_count, offsetof(Player, option_count) == 0x3500);
PLAYER_CHECK(damage_sources, offsetof(Player, damage_sources) == 0x350C);
PLAYER_CHECK(unknown_42f4, offsetof(Player, unknown_42f4) == 0x42F4);
PLAYER_CHECK(invulnerability_timer, offsetof(Player, invulnerability_timer) == 0x430C);
PLAYER_CHECK(item_collect_box, offsetof(Player, item_collect_box) == 0x4324);
PLAYER_CHECK(position_history, offsetof(Player, position_history) == 0x436C);
PLAYER_CHECK(focused, offsetof(Player, focused) == 0x4474);
#undef PLAYER_CHECK

extern "C" {
extern Player* g_player;  // 0x00477834
// 0x00426CF0: the player was hit. Enters PLAYER_HIT, plays the hit effect and
// sound and starts the deathbomb window.
void __stdcall Player_Hit(Player* player);
}
