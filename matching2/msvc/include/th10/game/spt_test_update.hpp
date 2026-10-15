#pragma once
#include "th10/game/spt_test.hpp"
#include "th10/platform/worker.hpp"

// The key state at 0x00474E30, as far as the screen reads it.
struct SptTestInput_0042bfc0 {
    unsigned char reserved_00[4];
    unsigned short held;       // +0x04
    unsigned short repeated;   // +0x06
    unsigned short pressed;    // +0x08

    // 0x0040ACE0: is any key of the mask held or repeating?
    __declspec(noinline) unsigned short MaskActive(unsigned short mask);
    __forceinline bool Active(unsigned short mask) const {
        return (repeated & mask) || (held & mask);
    }
};

// The game-wide state at 0x00491C28, as far as the mode switch writes it.
struct SptTestGameState_0042bfc0 {
    unsigned char reserved_000[0x390];
    int mode;                  // +0x390
    unsigned char reserved_394[0x3CC - 0x394];
    unsigned int flags;        // +0x3CC, bit 0x1000 forces mode 2
};
// 0x0040AC90: request a game mode.
__declspec(noinline) void __stdcall SptTest_SetGameMode_0040ac90(SptTestGameState_0042bfc0* state, int mode);

struct SptTestFindData_0042bfc0 {
    unsigned int attributes;
    unsigned int times[6];
    unsigned int size_high, size_low, reserved0, reserved1;
    char name[260];
    char alternate_name[14];
};

extern "C" {
extern SptTestInput_0042bfc0 data_00474e30;
extern SptTestGameState_0042bfc0 data_00491c28;
void* __cdecl malloc(unsigned int size);
__declspec(dllimport) void* __stdcall FindFirstFileA(const char* pattern, SptTestFindData_0042bfc0* data);
__declspec(dllimport) int __stdcall FindNextFileA(void* search, SptTestFindData_0042bfc0* data);
__declspec(dllimport) int __stdcall FindClose(void* search);
// 0x0044FD10: run the interpreter and its children for one step.
__declspec(noinline) int __stdcall SptTest_TickVm_0044fd10(SptTestResource_0042be20* vm, float delta);
}
// 0x0042BE10: the loader thread entry.
unsigned int __stdcall SptTest_LoadThread_0042be10(void* context);

inline void SptTest_Remember(MenuCursor* cursor) {
    cursor->previous_selection = cursor->selection;
}
// Select the wanted item, or the last one when there are fewer.
inline void SptTest_Select(MenuCursor& cursor, int index) {
    if (cursor.item_count != 0)
        cursor.selection = index >= cursor.item_count ? cursor.item_count - 1 : index;
    else
        cursor.selection = 0;
}

int __fastcall SptTest_UpdateTask_0042c580(SptTest_0042be20* viewer);
