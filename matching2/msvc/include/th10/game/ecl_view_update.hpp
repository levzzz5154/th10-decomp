#pragma once
#include <string.h>
#include "th10/game/ecl_view_teardown.hpp"

// The key state at 0x00474E30.
struct EclViewInput_0040a450 {
    unsigned short raw;            // +0x00, the keys read this frame
    unsigned char reserved_02[2];
    unsigned short held;           // +0x04
    unsigned short repeated;       // +0x06
    unsigned short pressed;        // +0x08
    unsigned char reserved_0a[0x2C - 0x0A];
    unsigned short held_keys;      // +0x2C
    unsigned short previous_keys;  // +0x2E
    unsigned short repeat_flags;   // +0x30
    unsigned short new_press;      // +0x32
    unsigned short new_release;    // +0x34

    // 0x0040AC20: advance the key-repeat counters and the edge masks.
    __declspec(noinline) unsigned short Update();
    // 0x0040ACE0: is any key of the mask held or repeating?
    __declspec(noinline) unsigned short MaskActive(unsigned short mask);
    __forceinline bool Active(unsigned short mask) const {
        return (repeated & mask) || (held & mask);
    }
};

// The game-wide state at 0x00491C28, as far as the mode switch writes it.
struct EclViewGameState_0040a450 {
    unsigned char reserved_000[0x390];
    int mode;                  // +0x390
    unsigned char reserved_394[0x3CC - 0x394];
    unsigned int flags;        // +0x3CC, bit 0x1000 forces mode 2
};
// 0x0040AC90: request a game mode.
__declspec(noinline) void __stdcall EclView_SetGameMode_0040ac90(EclViewGameState_0040a450* state, int mode);

// What an enemy is created with.
struct EclViewSpawn_0040a450 {
    float x;
    float y;
    float z;
    int reserved_0c[2];
    int life;                  // +0x14
    int reserved_18[10];

    // 0x0040CFB0: create an enemy running the named script entry.
    __declspec(noinline) void Create(EclViewEnemies_0040a940* manager, const char* entry);
};

struct EclViewFindData_0040a450 {
    unsigned int attributes;
    unsigned int times[6];
    unsigned int size_high, size_low, reserved0, reserved1;
    char name[260];
    char alternate_name[14];
};

extern "C" {
extern EclViewInput_0040a450 g_input_keys_raw;
extern EclViewGameState_0040a450 g_application;
void* __cdecl malloc(unsigned int size);
__declspec(dllimport) void* __stdcall FindFirstFileA(const char* pattern, EclViewFindData_0040a450* data);
__declspec(dllimport) int __stdcall FindNextFileA(void* search, EclViewFindData_0040a450* data);
__declspec(dllimport) int __stdcall FindClose(void* search);
}
// 0x0040A340: the loader thread entry, which recreates the managers.
unsigned int __stdcall EclView_LoadThread_0040a340(void* context);

// Destroy and free a manager the screen owns, if there is one; the global
// keeps its stale pointer until the loader thread replaces it.
__declspec(noinline) void EclView_Release(EclViewItems_0040a1a0* object);     // 0x004148E0
__declspec(noinline) void EclView_Release(EclViewPlayer_0040a1a0* object);    // 0x00425090
__declspec(noinline) void EclView_Release(EclViewBullets_0040a1a0* object);   // 0x00406140
__declspec(noinline) void EclView_Release(EclViewLasers_0040a1a0* object);    // 0x00405730
__declspec(noinline) void EclView_Release(EclViewEffects_0040a1a0* object);   // 0x0041AFB0
__declspec(noinline) void EclView_Release(EclViewPopups_0040a1a0* object);    // 0x0042B6D0
__declspec(noinline) void EclView_Release(EclViewEnemies_0040a940* object);   // 0x0040D730

inline void EclView_Remember(MenuCursor* cursor) {
    cursor->previous_selection = cursor->selection;
}
// Select the wanted item, or the last one when there are fewer.
inline void EclView_Select(MenuCursor& cursor, int index) {
    if (cursor.item_count != 0)
        cursor.selection = index >= cursor.item_count ? cursor.item_count - 1 : index;
    else
        cursor.selection = 0;
}

int __fastcall EclView_UpdateTask_0040abe0(EclView_0040a940* viewer);
