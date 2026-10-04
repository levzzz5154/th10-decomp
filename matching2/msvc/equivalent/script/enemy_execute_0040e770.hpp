#pragma once
#include "ecl_core_interpreter_0044e1a0.hpp"

struct Float2 {
    float x, y;
    Float2() {}
    Float2(float x_, float y_) { x = x_; y = y_; }
};
struct Float3 {
    float x, y, z;
    Float3() {}
    Float3(float x_, float y_, float z_) { x = x_; y = y_; z = z_; }
};
static __forceinline Float3 operator+(const Float3& a, const Float3& b) {
    return Float3(a.x + b.x, a.y + b.y, a.z + b.z);
}
extern "C" Float3 g_zero_vector_00491c14;
extern "C" Float2 g_zero_vector2_00491c20;
extern "C" Float3 g_camera_offset_00491d7c;
extern "C" float g_game_speed_00476f78;
extern "C" int g_difficulty_00474c74;
extern "C" int g_rank_00474c98;

struct RngState {
    unsigned short seed;
    unsigned short reserved;
    unsigned int generation;
    __declspec(noinline) float NextFloatSigned_0044bb90();
    // A random angle in [-pi, pi).
    __forceinline float NextAngle() { return NextFloatSigned_0044bb90() * 3.1415927f; }
};
extern "C" RngState g_effect_rng_004918b0;

struct FrameTimer {
    int previous;
    int current;
    float elapsed;
    const float* speed;
    unsigned int flags;
    __declspec(noinline) void Set_00405410(int value);
};

struct Float3Interp {
    Float3 initial, goal, control_1, control_2;
    FrameTimer timer;
    int end_time;
    int mode;
    __declspec(noinline) void Restart_004050d0();
};
struct Float2Interp {
    Float2 initial, goal, control_1, control_2;
    FrameTimer timer;
    int end_time;
    int mode;
    __declspec(noinline) void Restart_00412db0();
};

struct EnemyMotion {
    Float3 position;        // +0x00
    Float3 origin;          // +0x0C
    float speed;            // +0x18
    float angle;            // +0x1C
    float radial_speed;     // +0x20
    float angular_speed;    // +0x24
    unsigned int flags;     // +0x28
};
__declspec(noinline) void __stdcall Motion_SetAngle_00413170(EnemyMotion* motion, float angle);

struct AnmVm {
    unsigned char unknown_000[0x24];
    Float3 rotation;            // +0x024
    unsigned char unknown_030[0xC];
    Float2 scale;               // +0x03C
    unsigned char unknown_044[8];
    float sprite_height;        // +0x04C
    float sprite_width;         // +0x050
    unsigned char unknown_054[0x340 - 0x54];
    Float3 offset;              // +0x340
    unsigned char unknown_34c[0x10];
    unsigned int flags;         // +0x35C
};
struct AnmLoaded;
struct AnmHandle {
    int id;
    __declspec(noinline) void Release_00449630();
    __declspec(noinline) void Show_004495e0();
    __declspec(noinline) void Hide_00449590();
};
__declspec(noinline) AnmHandle* __stdcall Anm_CreateFront_00448e30(AnmLoaded* anm, AnmHandle* out, int script, int layer);
__declspec(noinline) AnmHandle* __stdcall Anm_CreateBack_00448d00(AnmLoaded* anm, AnmHandle* out, int script, int layer);
__declspec(noinline) AnmVm* __stdcall Anm_Resolve_00449450(AnmHandle* handle);
__declspec(noinline) Float3* __stdcall OffsetPoint_00418810(const Float3* point);

struct RenderStageState { __declspec(noinline) void SelectStage_00401d20(int index); };
extern "C" RenderStageState data_00491c28;
extern "C" unsigned char data_00491e48[], data_00491e08[], data_00491dc8[], data_00474df0[];
extern "C" Float3* __stdcall D3DXVec3Project_0045218e(Float3* out, const Float3* vector, const void* viewport,
                                                      const void* projection, const void* view, const void* world);

struct EnemySpawn {
    Float3 position;
    int score;          // +0x0C
    int item;           // +0x10
    int life;           // +0x14
    int mirrored;       // +0x18
    unsigned int flags; // +0x1C
    int variables[8];   // +0x20
};

struct ShooterEx {
    float a, b;
    int c, d, e, f;
};
struct BulletManager;
struct Shooter {
    short type;             // +0x000
    short color;            // +0x002
    Float3 position;        // +0x004
    float angle_1;          // +0x010
    float angle_2;          // +0x014
    float speed_1;          // +0x018
    float speed_2;          // +0x01C
    ShooterEx ex[18];       // +0x020
    unsigned char unknown_1d0[0x24];
    short count_1;          // +0x1F4
    short count_2;          // +0x1F6
    short aim_mode;         // +0x1F8
    unsigned int flags;     // +0x1FC
    int sound;              // +0x200
    int sound_2;            // +0x204
    unsigned char unknown_208[8];
    __declspec(noinline) int Shoot_004073e0(BulletManager* manager);
};
struct BulletManager {
    __declspec(noinline) int Sweep_00408210(int convert);
    __declspec(noinline) int Check_00408100(const Float3* point, float radius, int spawn_item, int filter);
};
extern "C" BulletManager* data_004776f0;

struct LaserManager;
struct Laser {
    unsigned char unknown_000[0x24];
    Float3 f24;                 // +0x024
    unsigned char unknown_030[0xC];
    float f3c;                  // +0x03C
    unsigned char unknown_040[4];
    float f44;                  // +0x044
    float f48;                  // +0x048
    unsigned char unknown_04c[0x430 - 0x4C];
    Float3 f430;                // +0x430
    unsigned char unknown_43c[4];
    float f440;                 // +0x440
    __declspec(noinline) void SetVector_0040cf60(const Float3& value);
};
struct LaserParams {
    Float3 position;
};
struct LineLaserParams : LaserParams {
    float f0c, f10, f14, f18, f1c, f20;
    short type, color;      // +0x24
    unsigned int flags;     // +0x28
    ShooterEx ex[18];       // +0x2C
};
struct BeamLaserParams : LaserParams {
    float f0c, f10, f14, f18, f1c, f20, f24, f28, f2c;
    int f30, f34, f38, f3c;
    short type, color;      // +0x40
    unsigned int flags;     // +0x44
    ShooterEx ex[18];       // +0x48
    __declspec(noinline) BeamLaserParams* Construct_0040cf40();
    __forceinline BeamLaserParams() { memset(this, 0, sizeof(*this)); f2c = 8.0f; }
    struct Raw {};
    __forceinline BeamLaserParams(Raw) {}
};
struct LaserManager {
    __declspec(noinline) int Spawn_0041c510(const LaserParams* params, int kind);
    __declspec(noinline) int Cleanup_0041c850(int value);
    __declspec(noinline) Laser* FindById_0040cf90(int id);
    __declspec(noinline) int Evaluate_0041c800(const Float3* point, float radius, int flag);
    __declspec(noinline) int MarkEligible_0041c7d0();
};
extern "C" LaserManager* data_0047781c;

struct ItemDrops {
    int items[13];          // +0x00: [0] is the main item
    float spread_x;         // +0x34
    float spread_y;         // +0x38
};
__declspec(noinline) void __stdcall Drops_Flush_0040c9a0(const Float3* position, ItemDrops* drops);

struct ResourceSlot {
    int id;
    int value;
    const char* begin;
    const char* cursor;
};

struct ScoreDisplay;
struct LifeMarker { float ratio; int value; };
struct Gui {
    unsigned char unknown_0000[0x9E90];
    int f9e90;                  // +0x9E90
    LifeMarker markers[4];      // +0x9E94
    unsigned char unknown_9eb4[4];
    struct GuiMessage* message; // +0x9EB8
    __declspec(noinline) void CreateScoreDisplay_00415db0(int stage);
    __forceinline void SetMarker(int index, int full, float amount, int value) {
        markers[index].value = value;
        markers[index].ratio = amount / (float)full;
    }
};
struct GuiMessage {
    unsigned char unknown_00[0x78];
    int f78;
};
extern "C" Gui* data_0047770c;

struct Player {
    unsigned char unknown_000[0x3C0];
    Float3 position;            // +0x3C0
};
extern "C" Player* data_00477834;

struct SpellCard {
    unsigned char unknown_0000[0x378C];
    unsigned int flags;         // +0x378C
    __declspec(noinline) void End_00409c00();
    __declspec(noinline) void StopAnimation_0040cea0();
};
extern "C" SpellCard* data_004776f4;
__declspec(noinline) void __stdcall SpellCard_Start_00409280(SpellCard* card, int id, const char* name, int time, int unused);

struct SoundQueue { __declspec(noinline) void QueuePan_0043dd10(int sound, float pan); };
extern "C" SoundQueue data_00492590;
struct ScoreState { int fields[20]; };
extern "C" ScoreState data_00474c40;
__declspec(noinline) void __stdcall Score_SetMode_00412ed0(ScoreState* state, int mode);
__declspec(noinline) void* __stdcall CreateScreenEffect_0043c8b0(int priority, int mode, int a, int b, int c, int d);

struct Enemy;
struct EnemyFull;
struct EnemyManager {
    unsigned char unknown_00[0x10];
    EnemyFull* boss[8];         // +0x10
    AnmLoaded* anm[8];          // +0x30
};
extern "C" EnemyManager* data_00477704;
__declspec(noinline) void __stdcall EnemyManager_SweepDeaths_0040e6a0(EnemyManager* manager);
__declspec(noinline) EnemyFull* __stdcall EnemyManager_Spawn_0040cfb0(const EnemySpawn* parameters, EnemyManager* manager, const char* name);
__declspec(noinline) void __stdcall Enemy_BindSlot_00412720(EnemyFull* enemy, int index, int id, int value, const char* data);

struct Enemy {
    unsigned char unknown_0000[0x2C];
    Float3 position;                // +0x002C
    unsigned char unknown_0038[0x20];
    EnemyMotion absolute;           // +0x0058
    EnemyMotion relative;           // +0x0084
    float fb0, fb4, fb8, fbc;       // +0x00B0
    AnmHandle anm[10];              // +0x00C0
    int anm_file;                   // +0x00E8
    int anm_main_file;              // +0x00EC
    int anm_main_script;            // +0x00F0
    int anm_base_script;            // +0x00F4
    int anm_f8;                     // +0x00F8
    int variables[8];               // +0x00FC
    FrameTimer timer_11c;           // +0x011C
    unsigned char unknown_0130[0xC];
    Float3Interp absolute_position_interp;  // +0x013C
    Float3Interp relative_position_interp;  // +0x0188
    Float2Interp absolute_direction_interp; // +0x01D4
    Float2Interp relative_direction_interp; // +0x0210
    Float2Interp absolute_orbit_interp;     // +0x024C
    Float2Interp relative_orbit_interp;     // +0x0288
    Shooter shooters[8];            // +0x02C4
    Float3 shoot_offset[8];         // +0x1344
    float hitbox_width;             // +0x13A4
    float hitbox_height;            // +0x13A8
    float bounds_x, bounds_y, bounds_width, bounds_height;  // +0x13AC
    unsigned char unknown_13bc[4];
    int life;                       // +0x13C0
    int max_life;                   // +0x13C4
    int f13c8;                      // +0x13C8
    ItemDrops drops;                // +0x13CC
    unsigned char unknown_1408[0x14];
    FrameTimer timer_141c;          // +0x141C
    FrameTimer timer_1430;          // +0x1430
    union {
        unsigned int flags;         // +0x1444
        struct {
            unsigned int flags_low : 19;
            unsigned int f19 : 1;
            unsigned int f20 : 1;
            unsigned int f21 : 1;
        };
    };
    int f1448;                      // +0x1448
    int f144c;                      // +0x144C
    int boss_index;                 // +0x1450
    float shoot_range_squared;      // +0x1454
    ResourceSlot slots[8];          // +0x1458
    EnemyFull* ecl;                 // +0x14D8

    __declspec(noinline) int Execute_0040e770();
    __declspec(noinline) float FloatValue_00412aa0(int selector, float value);
    __declspec(noinline) int IntArg_00412a00(int selector);
    __declspec(noinline) int* IntDest_00412a10(int selector);
    int Int(int selector);
    float Float(int selector);
    int IntValue(int selector, int value);
    float* FloatDest(int selector);
    __forceinline void SetSpread(float x, float y) { drops.spread_x = x; drops.spread_y = y; }
};

struct EnemyFull : EclOwner {
    Enemy body;                     // +0x103C
    __forceinline int Int(int selector) { return active->IntOperand(selector); }
    __forceinline float Float(int selector) { return active->FloatOperand(selector); }
    __forceinline int IntValue(int selector, int value) { return active->IntValue(selector, value); }
    __forceinline float* FloatDest(int selector) { return active->FloatDest(selector); }
};

__forceinline int Enemy::Int(int selector) { return ecl->Int(selector); }
__forceinline float Enemy::Float(int selector) { return ecl->Float(selector); }
__forceinline int Enemy::IntValue(int selector, int value) { return ecl->IntValue(selector, value); }
__forceinline float* Enemy::FloatDest(int selector) { return ecl->FloatDest(selector); }

typedef char Enemy_ecl_check[offsetof(Enemy, ecl) == 0x14D8 ? 1 : -1];
typedef char Enemy_flags_check[offsetof(Enemy, flags) == 0x1444 ? 1 : -1];
typedef char Enemy_shooters_check[offsetof(Enemy, shooters) == 0x2C4 ? 1 : -1];
typedef char Enemy_offsets_check[offsetof(Enemy, shoot_offset) == 0x1344 ? 1 : -1];
typedef char Enemy_interp_check[offsetof(Enemy, absolute_position_interp) == 0x13C ? 1 : -1];
typedef char Enemy_drops_check[offsetof(Enemy, drops) == 0x13CC ? 1 : -1];
typedef char Enemy_timer_check[offsetof(Enemy, timer_141c) == 0x141C ? 1 : -1];
typedef char Shooter_size_check[sizeof(Shooter) == 0x210 ? 1 : -1];
typedef char Shooter_count_check[offsetof(Shooter, count_1) == 0x1F4 ? 1 : -1];
typedef char Line_size_check[sizeof(LineLaserParams) == 0x1DC ? 1 : -1];
typedef char Beam_size_check[sizeof(BeamLaserParams) == 0x1F8 ? 1 : -1];
typedef char Full_body_check[offsetof(EnemyFull, body) == 0x103C ? 1 : -1];
typedef char Laser_check[offsetof(Laser, f440) == 0x440 ? 1 : -1];
