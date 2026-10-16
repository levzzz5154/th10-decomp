#ifndef TH10_GAME_ENEMY_SPAWN_0040CFB0_HPP
#define TH10_GAME_ENEMY_SPAWN_0040CFB0_HPP
#include <stddef.h>
#include "th10/math/timer.hpp"

void* __cdecl operator new(unsigned int size);

struct EnemyVector {
    float x;
    float y;
    float z;
};

// A link of the enemy manager's list.
struct EnemyNode2 {
    void* enemy;
    EnemyNode2* next;
    EnemyNode2* previous;
};

struct EnemyFlags {
    unsigned int reserved_00 : 11;
    unsigned int mirrored : 1;          // bit 11
    unsigned int reserved_12 : 3;
    unsigned int boss_items : 1;        // bit 15
    unsigned int reserved_16 : 2;
    unsigned int quiet : 1;             // bit 18
    unsigned int reserved_19 : 13;
};

// The enemy proper (0x14DC bytes at +0x103C of the record).
struct EnemyData {
    unsigned char reserved_0000[0x58];
    EnemyVector position;      // +0x0058
    unsigned char reserved_0064[0xEC - 0x64];
    int kind;                           // +0x00EC
    int kind_index;                     // +0x00F0
    unsigned char reserved_00f4[8];
    int variables[8];                   // +0x00FC
    unsigned char reserved_011c[0x130 - 0x11C];
    EnemyNode2 node;            // +0x0130
    unsigned char reserved_013c[0x13BC - 0x13C];
    int life;                           // +0x13BC
    int score;                          // +0x13C0
    unsigned char reserved_13c4[8];
    int drop_item;                      // +0x13CC
    unsigned char reserved_13d0[0x1408 - 0x13D0];
    int death_sound;                    // +0x1408
    int death_effect;                   // +0x140C
    int death_callback;                 // +0x1410
    unsigned char reserved_1414[8];
    FrameTimer invulnerable_timer;      // +0x141C
    unsigned char reserved_1430[0x1444 - 0x1430];
    EnemyFlags flags;          // +0x1444
    unsigned char reserved_1448[0x14DC - 0x1448];
};
typedef char EnemyDataSize[sizeof(EnemyData) == 0x14DC ? 1 : -1];
typedef char EnemyDataNode[offsetof(EnemyData, node) == 0x130 ? 1 : -1];
typedef char EnemyDataLife[offsetof(EnemyData, life) == 0x13BC ? 1 : -1];
typedef char EnemyDataTimer[offsetof(EnemyData, invulnerable_timer) == 0x141C ? 1 : -1];
typedef char EnemyDataFlags[offsetof(EnemyData, flags) == 0x1444 ? 1 : -1];

// 0x0040DC80: run the enemy's script up to its first wait. The enemy is
// passed on the stack.
extern "C" void __stdcall EnemyData_Start(EnemyData* enemy);

// The 0x2518-byte enemy record: script interpreter, then the enemy.
struct Enemy4 {
    unsigned char reserved_0000[0x1024];
    unsigned char difficulty_mask;      // +0x1024
    unsigned char reserved_1025[0x103C - 0x1025];
    EnemyData data;            // +0x103C

    // 0x0040D830: bind the record to the named script entry.
    __forceinline Enemy4(const char* entry);
};
typedef char EnemySize[sizeof(Enemy4) == 0x2518 ? 1 : -1];

struct EnemyCtrlSpawnView {
    unsigned char reserved_00[0x58];
    EnemyNode2* head;           // +0x58
    EnemyNode2* tail;           // +0x5C
    int count;                          // +0x60
    int created;                        // +0x64
};

// What an enemy is created with.
struct EnemySpawn2 {
    EnemyVector position;      // +0x00
    int life;                           // +0x0C
    int drop_item;                      // +0x10
    int score;                          // +0x14
    int mirrored;                       // +0x18
    int quiet;                          // +0x1C
    int variables[8];                   // +0x20

    // 0x0040CFB0: create an enemy running the named script entry and append
    // it to the manager's list.
    __declspec(noinline) Enemy4* Create(EnemyCtrlSpawnView* manager, const char* entry);
};
typedef char EnemySpawnSize[sizeof(EnemySpawn2) == 0x40 ? 1 : -1];

// The run's counters, as far as the enemy creation reads them.
struct RunState {
    unsigned char reserved_00[0x34];
    int difficulty;                     // +0x34 (0x00474C74)
};
extern "C" RunState g_globals;

#endif

struct EnemyScriptEntity;
struct BindScriptName { const char* value; };
__declspec(noinline) EnemyScriptEntity* __fastcall InitializeEnemyScriptEntity(int,EnemyScriptEntity*,BindScriptName);
__forceinline Enemy4::Enemy4(const char* entry) {
    BindScriptName name={entry};
    InitializeEnemyScriptEntity(0,reinterpret_cast<EnemyScriptEntity*>(this),name);
}
