#pragma once
// MSVC 7.1 is pre-C++11 — use manual typedefs instead of <cstdint>
typedef unsigned char       uint8_t;
typedef unsigned short      uint16_t;
typedef unsigned int        uint32_t;
typedef unsigned long long  uint64_t;
typedef signed char         int8_t;
typedef short               int16_t;
typedef int                 int32_t;
typedef long long           int64_t;

// ============================================================================
// Base Entity - 0x3AC bytes (0xEB dwords + 2 bytes)
// Used by Entity_Destructor (0x401FF0), Entity_Constructor (0x402050),
// Entity_Init (0x401DE0)
// ============================================================================
struct Entity {
    // +0x000
    void*     vtable;
    // +0x004  linked list (self-referencing)
    Entity*   list1_prev;
    Entity*   list1_next;
    void*     field_00C;
    // +0x010  second linked list
    Entity*   list2_prev;
    Entity*   list2_next;
    // +0x018
    uint32_t  field_018;
    // +0x01C
    uint32_t  field_01C;
    // +0x020  flags (bit 0 = movement mode)
    uint32_t  field_020;
    // +0x024 - 0x033  (various state)
    uint32_t  pad_024[4];
    // +0x034  saved across init
    uint32_t  field_034;
    uint32_t  field_038;
    // +0x03C  scale = 1.0f
    float     scaleX;
    // +0x040  scale = 1.0f
    float     scaleY;
    // +0x044 - 0x05B
    uint32_t  pad_044[6];
    // +0x05C  scheduler timer = 0xfff0bdc1
    uint32_t  scheduler_timer;
    // +0x060
    uint32_t  field_060;
    uint32_t  field_064;
    // +0x068  (various)
    uint32_t  pad_068[1];
    // +0x06C  flags (bit 0 cleared by constructor)
    uint32_t  flags_06C;
    // +0x070 - 0x0AF
    uint32_t  pad_070[16];
    // +0x0B0  flags (bit 0 cleared by constructor)
    uint32_t  flags_0B0;
    // +0x0B4 - 0x0FB
    uint32_t  pad_0B4[18];
    // +0x0FC  flags
    uint32_t  flags_0FC;
    // +0x100 - 0x127
    uint32_t  pad_100[10];
    // +0x128  flags
    uint32_t  flags_128;
    // +0x12C - 0x173
    uint32_t  pad_12C[18];
    // +0x174  flags
    uint32_t  flags_174;
    // +0x178 - 0x1AF
    uint32_t  pad_178[14];
    // +0x1B0  flags
    uint32_t  flags_1B0;
    // +0x1B4 - 0x1FB
    uint32_t  pad_1B4[18];
    // +0x1FC  flags
    uint32_t  flags_1FC;
    // +0x200 - 0x227
    uint32_t  pad_200[10];
    // +0x228  flags
    uint32_t  flags_228;
    // +0x22C - 0x23B
    uint32_t  pad_22C[4];
    // +0x23C  = 1.0f
    float     field_23C;
    // +0x240
    uint32_t  field_240;
    uint32_t  field_244;
    uint32_t  field_248;
    uint32_t  field_24C;
    // +0x250  = 1.0f
    float     field_250;
    // +0x254 - 0x263
    uint32_t  pad_254[4];
    // +0x264  = 1.0f
    float     field_264;
    // +0x268
    uint32_t  field_268;
    uint32_t  field_26C;
    uint32_t  field_270;
    uint32_t  field_274;
    // +0x278  = 1.0f
    float     field_278;
    // +0x27C - 0x2FB
    uint32_t  pad_27C[32];
    // +0x2FC  = 0xFFFFFFFF
    uint32_t  field_2FC;
    // +0x300 - 0x33F
    uint32_t  pad_300[16];
    // +0x340  saved across init (3 dwords)
    uint32_t  field_340;
    uint32_t  field_344;
    uint32_t  field_348;
    // +0x34C
    uint32_t  pad_34C[3];
    // +0x358  resource pointer (freed by destructor)
    void*     resource;
    // +0x35C  word = 7 (init) or 0xFFFF (constructor)
    uint16_t  end_marker;
    uint16_t  pad_35E;
    // +0x360  second owned resource used by another entity subsystem
    void*     secondary_resource;
    // +0x364 - 0x3AB
    uint8_t   pad_364[0x3AC - 0x364];
};
// static_assert not available in MSVC 7.1
// sizeof(Entity) == 0x3AC

// ============================================================================
// Bullet / Enemy Entity - 0x2518 bytes
// Allocated by Entity_Spawn (0x40CFB0), initialized by Entity_InitHelper
// (0x40D830). Contains base Entity at offset 0, extended fields after.
// ============================================================================
struct BulletEntity {
    // +0x000  base Entity (0x3AC bytes)
    Entity    base;
    // +0x3AC - 0x103B  extended entity fields
    uint8_t   extended[0x103C - 0x3AC];
    // +0x103C  bullet data (zeroed as 0x537 dwords = 0x14DC bytes)
    uint32_t  bullet_data[0x537];
    // total = 0x103C + 0x14DC = 0x2518
};
// sizeof(BulletEntity) == 0x2518

// Parameters copied into a BulletEntity by the spawn path. The constructor at
// 0x0040CF40 clears all 0x1F8 bytes and gives the radius at +0x2C its default.
struct BulletSpawnParameters {
    uint32_t fields[0x7E];
};
// sizeof(BulletSpawnParameters) == 0x1F8

BulletSpawnParameters* __fastcall BulletSpawnParameters_Initialize(
    void* unused, BulletSpawnParameters* parameters);

// ============================================================================
// Entity Manager / GameStateManager
// Contains global state including entity slot array at +0x3AD4E0
// ============================================================================
struct EntityManager {
    uint8_t data[0x3AD4E0 + 0x80];  // includes 32 entity slots (0x20 * 4)
};

// ============================================================================
// Scheduler Task - 0x24 bytes (9 dwords)
// ============================================================================
struct SchedulerTask {
    SchedulerTask* next;
    SchedulerTask* prev;
    uint32_t       field_008;
    uint32_t       timer;
    uint32_t       field_010;
    uint32_t       field_014;
    uint32_t       field_018;
    uint32_t       field_01C;
    uint32_t       field_020;
};
// sizeof(SchedulerTask) == 0x24

// ============================================================================
// Type aliases (MSVC 7.1: no 'using' declarations, use typedefs)
// ============================================================================
typedef uint8_t  u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;
typedef int8_t   i8;
typedef int16_t  i16;
typedef int32_t  i32;
typedef int64_t  i64;
typedef float    f32;
typedef double   f64;
