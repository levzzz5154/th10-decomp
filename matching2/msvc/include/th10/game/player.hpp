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
extern "C" void __cdecl crt_free(void*);

// The player's own sprite. Its destructor (0x00401FF0, shared with the other
// 0x3AC-byte sprites) frees the sprite's resource block.
struct PlayerSprite : Entity {
    // The destructor cluster exports this at its public thiscall ABI.
#ifdef TH10_PLAYER_SPRITE_EXPORTED_ABI
    __declspec(dllexport)
#endif
    ~PlayerSprite() {
        if (resource)
            crt_free(resource);
        resource = 0;
    }
};
struct Point3_OrientedRect;
struct PickupAnimation;   // an animation object, as the player's records see it
struct Player;
struct PlayerBullet;

// Player positions are kept in hundredths of a pixel; Player::position is the
// same point as floats.
struct FixedPoint {
    int x, y;

    FixedPoint() {}
    FixedPoint(int x_, int y_) : x(x_), y(y_) {}
    // Retail copies these member by member; the compiler's own block copy
    // picks other loop pointers.
    FixedPoint& operator=(const FixedPoint& other) {
        x = other.x;
        y = other.y;
        return *this;
    }
    FixedPoint operator+(const FixedPoint& other) const { return FixedPoint(x + other.x, y + other.y); }
    FixedPoint operator-(const FixedPoint& other) const { return FixedPoint(x - other.x, y - other.y); }
    FixedPoint operator*(int scale) const { return FixedPoint(x * scale, y * scale); }
    FixedPoint operator/(int divisor) const { return FixedPoint(x / divisor, y / divisor); }
    bool operator!=(const FixedPoint& other) const { return x != other.x || y != other.y; }
    FixedPoint& operator+=(const FixedPoint& other) {
        x += other.x;
        y += other.y;
        return *this;
    }
};

// A screen point or size without depth.
struct PickupPoint {
    float x, y;
};

// A position with a polar velocity, or an orbit when flags bit 0 is set.
struct Motion {
    Vector3 position, velocity;
    float speed;        // also the orbit turn rate when flags bit 0 is set
    float angle, radius, radius_step;
    unsigned char flags;
    // 0x0044C2A0: move by one frame.
    __declspec(noinline) void Advance();
    // Recompute the velocity (or the orbit radius and angle); inline.
    void Update();
};

// An animation handle as the player's records keep it. Retail re-reads and
// re-stores it around each use, so the value is volatile.
struct PlayerAnimationHandle {
    volatile unsigned int value;
    __declspec(noinline) void StopAtFrame1();          // 0x00409E50
    __declspec(noinline) void StopAtFrame2();          // 0x0040C480
    __declspec(noinline) void StopAtFrame3();          // 0x0040C4D0
    __declspec(noinline) PickupAnimation* Validate();  // 0x00449450, clears a stale handle
    __declspec(noinline) void Retire();                // 0x00449630
};

enum ShotKind {
    SHOT_HOMING = 2,  // its damage also leaves a small damage source behind
    SHOT_LASER = 3    // stays alive while the fire button is held
};

// One shot of a shot-type (.sht) file: what to fire, how often and from where.
struct ShotDefinition {
    signed char period;          // fires on frames where frame % period == phase
    signed char phase;
    short damage;
    PickupPoint offset;          // from the player or the option firing it
    float width, height;         // hitbox
    float angle, speed;
    signed char option;          // 0 = the player, 1..4 = that option
    unsigned char kind;          // a ShotKind, or 0
    short animation, hit_animation, sound;
    void (__fastcall* on_fire)(Player* player, PlayerBullet* bullet, int frame);
    void (__fastcall* on_update)(Player* player, PlayerBullet* bullet);
    unsigned char unknown_2c[4];
    // Nonzero when this shot cannot hit at that point.
    int (__fastcall* skip_hit)(Player* player, PlayerBullet* bullet, const PickupPoint* point);
};

// The shots a shot type fires at one power level.
struct ShotList {
    ShotDefinition* shots;       // ends with a negative period
    int unknown_04;
};

// A loaded shot-type file: one shot list per power level, unfocused then
// focused.
struct ShotTypeFile {
    unsigned short version;                  // +0x00
    unsigned short unknown_002;
    float hitbox_size;                       // +0x04, set per shot type at start
    float item_seek_speed;                   // +0x08, items flying to the player
    float item_box_size;                     // +0x0C
    float speed;                             // +0x10, pixels per frame
    float focused_speed;                     // +0x14
    float diagonal_speed;                    // +0x18
    float focused_diagonal_speed;            // +0x1C
    unsigned char option_offsets[0xF0];      // +0x20, 12-byte rows, unfocused then focused
    ShotList lists[10];
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
    FrameTimer timer;                        // +0x00
    Motion motion;                           // +0x14
    // 0 = free, 1 = flying, 2 = hit and fading. Retail reads it once per
    // test, so it is volatile.
    volatile int state;                      // +0x40
    PlayerAnimationHandle animation;         // +0x44
    PlayerAnimationHandle laser_animation;   // +0x48, lasers only
    unsigned int unknown_4c;                 // +0x4C
    int hit_this_frame;                      // +0x50
    int hitting;                             // +0x54, a laser that is touching an enemy
    ShotDefinition* definition;              // +0x58
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
    unsigned char unknown_70[0x14];
    int was_focused;                   // +0x84, trailing options
    int index;                         // +0x88, which option this is
    int reset_position;                // +0x8C
    int (__fastcall* update)(PlayerOption* option);  // +0x90, optional
    int unknown_94;

    // The four points above by index, the order a replay saves them in.
    FixedPoint& Point(int which) { return (&target)[which]; }

    // 0x00427960: for options that trail the player: while unfocused, sit on
    // the position history and remember the offset; while focused, hold that
    // offset and redraw the history between this option and the previous one.
    __declspec(noinline) void FollowTrail();
};

// An area that damages enemies: a bomb, or the burst around a respawn
// (0x6C bytes).
struct PlayerDamageSource {
    float radius;                      // +0x00
    float radius_growth;               // +0x04
    float angle;                       // +0x08, of a rotated rectangle
    float angle_step;                  // +0x0C
    float width, height;               // +0x10
    union {
        struct {
            Vector3 position;          // +0x18
            unsigned char unknown_24[0x20];
        };
        Motion motion;                 // +0x18
    };
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
    PlayerSprite sprite;                     // +0x014
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
    // +0x42F4: per firing point (0 = player, 1..4 = options), whether a laser
    // is out. One shot type keeps its focus transition age in the last slot.
    int laser_active[5];
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

    // 0x00428E10: move the player to a fixed-point position and make the
    // options jump to their places.
    __declspec(noinline) Player* SetFixedPosition(const FixedPoint* source);

    // 0x004250B0: read the input and move the player, the focus marker, the
    // position history and the options.
    __declspec(noinline) int Move();
    // 0x004281D0: while alive and shooting, run the 15-frame shot cycle.
    __declspec(noinline) int UpdateShooting();
    // 0x00428160: fire every shot of the current power level that is due on
    // `frame` of the cycle.
    __declspec(noinline) int FireShots(int frame);
    // 0x00426660: the angle from `point` to the player (0 when they meet).
    // LTCG callers pass the point in EAX.
    __declspec(noinline) float AngleFromPoint(const float* point);

    // 0x00424ED0
    __declspec(noinline) ~Player();
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
PLAYER_CHECK(laser_active, offsetof(Player, laser_active) == 0x42F4);
PLAYER_CHECK(motion_size, sizeof(Motion) == 0x2C);
PLAYER_CHECK(shot_definition_skip_hit, offsetof(ShotDefinition, skip_hit) == 0x30);
PLAYER_CHECK(bullet_state, offsetof(PlayerBullet, state) == 0x40);
PLAYER_CHECK(damage_source_lifetime, offsetof(PlayerDamageSource, lifetime) == 0x44);
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
