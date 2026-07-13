// th10.hpp - Core types reconstructed from Ghidra decompilation
// Touhou 10: Mountain of Faith - matching decompilation
#pragma once

#include <cstdint>

// === Basic types ===
using u8  = uint8_t;
using u16 = uint16_t;
using u32 = uint32_t;
using i32 = int32_t;
using f32 = float;

// === Forward declarations ===
struct Entity;
struct GameStateManager;
struct GameThread;
struct SchedulerTask;
struct AnmFile;

// === Entity (0x3AC bytes) ===
// Core game object - bullets, enemies, items, player, effects
// Stored in pools of 4096 within GameStateManager
struct Entity {
    u32     vtable;         // +0x000: vtable pointer (PTR_LAB_0046cb14)
    u32     flags;          // +0x004: entity flags
    u32     field_008;      // +0x008
    u32     field_00C;      // +0x00C
    u32     field_010;      // +0x010
    u32     field_014;      // +0x014
    u32     field_018;      // +0x018
    u32     field_01C;      // +0x01C
    u32     field_020;      // +0x020
    u32     field_024;      // +0x024
    u32     field_028;      // +0x028
    u32     field_02C;      // +0x02C
    // AnmRef embedded at +0x30? 
    u32     field_030;      // +0x030 
    u32     field_034;      // +0x034: ANM sprite index
    u32     field_038;      // +0x038
    u32     field_03C;      // +0x03C
    u32     field_040;      // +0x040
    u32     field_044;      // +0x044
    u32     field_048;      // +0x048
    u32     field_04C;      // +0x04C
    u32     field_050;      // +0x050
    u32     field_054;      // +0x054
    u32     field_058;      // +0x058
    u32     field_05C;      // +0x05C
    u32     field_060;      // +0x060
    u32     field_064;      // +0x064
    u32     field_068;      // +0x068
    u32     field_06C;      // +0x06C
    u32     field_070;      // +0x070
    u32     field_074;      // +0x074
    u32     field_078;      // +0x078
    u32     field_07C;      // +0x07C
    u32     field_080;      // +0x080
    u32     field_084;      // +0x084
    u32     field_088;      // +0x088
    u32     field_08C;      // +0x08C
    u32     field_090;      // +0x090
    u32     field_094;      // +0x094
    u32     field_098;      // +0x098
    u32     field_09C;      // +0x09C
    u32     field_0A0;      // +0x0A0
    u32     field_0A4;      // +0x0A4
    u32     field_0A8;      // +0x0A8
    u32     field_0AC;      // +0x0AC
    u32     field_0B0;      // +0x0B0
    u32     field_0B4;      // +0x0B4
    u32     field_0B8;      // +0x0B8
    u32     field_0BC;      // +0x0BC
    u32     field_0C0;      // +0x0C0
    u32     field_0C4;      // +0x0C4
    u32     field_0C8;      // +0x0C8
    u32     field_0CC;      // +0x0CC
    u32     field_0D0;      // +0x0D0
    u32     field_0D4;      // +0x0D4
    u32     field_0D8;      // +0x0D8
    u32     field_0DC;      // +0x0DC
    u32     field_0E0;      // +0x0E0
    u32     field_0E4;      // +0x0E4
    u32     field_0E8;      // +0x0E8
    u32     field_0EC;      // +0x0EC
    u32     field_0F0;      // +0x0F0
    u32     field_0F4;      // +0x0F4
    u32     field_0F8;      // +0x0F8
    u32     field_0FC;      // +0x0FC
    // ... 0x3AC / 4 = 235 dwords total ...
    u32     pad[187];       // padding to 0x3AC (940 bytes)
};
static_assert(sizeof(Entity) == 0x3AC, "Entity size mismatch");

// === GameStateManager (0x732460 bytes) ===
// The master game state - contains entity pools, stage data, everything
struct GameStateManager {
    i32     field_000;          // +0x000000
    i32     field_004;          // +0x000004
    
    // Entity pool 1: 0x1000 entities (4096 * 0x3AC = 0x3AC000)
    Entity  entity_pool[0x1000]; // +0x000068? Actually starts at +0x1A based on GameStateInit
    
    u8      pad_entity_pool[0x3AC000]; // placeholder for exact layout
    
    i32     field_3AC068;       // after entity pool
    
    // Entity pool 2: 0x14 entities for bullets/effects
    // plus many more fields...
    
    u32     scale_field_00;     // some scale value
    u32     scale_field_01;     // etc
    
    // Replay data
    i32     replay_score;       // high score
    i32     replay_stage;       // current stage
    u8      replay_char;        // character
    u8      replay_difficulty;  // difficulty
    i32     replay_rng;         // RNG seed
    i32     replay_flags;       // replay flags
};

// === SchedulerTask (0x24 bytes) ===
// Callback/task scheduled for execution
struct SchedulerTask {
    u32     field_00;       // +0x00
    u32     flags;          // +0x04: flags (bit 0 = active, bit 1 = scheduled)
    void*   callback;       // +0x08: function pointer (LABEL address)
    u32     field_0C;       // +0x0C
    u32     field_10;       // +0x10
    void*   self;           // +0x14: self pointer
    u32     field_18;       // +0x18
    u32     field_1C;       // +0x1C
    GameStateManager* gsm;  // +0x20: game state manager
};

// === ANM Animation Reference (0x20 bytes?) ===
// Used in Entity for sprite animation state
struct AnmRef {
    u32     anm_handle;     // ANM file handle
    u32     frame_index;    // current frame
    u32     frame_timer;    // animation timer
    u32     field_0C;
    u32     field_10;
};

// === Global variables (extern) ===
extern GameThread*      g_pGameThread;
extern GameStateManager* g_pGameStateManager;
extern void*            g_pD3D9;
extern void*            g_pD3DDevice;
extern void*            g_pWnd;
extern u32              g_dwPlatformId;
extern u32              g_dwMajorVersion;
extern u32              g_dwMinorVersion;
extern u32              g_dwBuildNumber;
extern char*            g_pCmdLine;
extern char*            g_pEnvStrings;
extern i32              DAT_00491be4;
extern u32              DAT_0049231c;
extern char             DAT_00474f70[];    // log buffer (0x2000 bytes)

// === Core function declarations ===
extern "C" {
    void*   operator_new(u32 size);
    void    operator_delete(void* ptr);
    void    _free(void* ptr);
    void*   __nh_malloc(u32 size, int);
    
    // Vector constructor/destructor iterators (MSVC EH helpers)
    void    __eh_vector_constructor_iterator(void* base, u32 count, u32 stride,
                                              void* constructor, void* destructor);
    
    // Core game
    int     GameMain(void* hInstance);
    GameStateManager* GameStateInit(GameStateManager* gsm);
    void    FUN_00446220(GameStateManager* gsm);  // state destroy
    
    // Entity operations
    void    FUN_00401de0(u32 idx, Entity* entity);  // entity constructor/init
    Entity* FUN_00402050(Entity* entity);  // entity constructor
    void    FUN_00401ff0(Entity* entity);  // entity destructor
    
    // Scheduler
    void*   FUN_00449ed0(void* callback);
    void    FUN_00449ae0(int);
    void    FUN_00449b70(int);
    
    // Logging
    void    FUN_0044b810(char* buf, const char* msg);
    void    FUN_0044b540(const char* filename, const char* buf);
}
