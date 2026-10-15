#pragma once
#include <stddef.h>

void* __cdecl operator new(unsigned int size);
void __cdecl operator delete(void* block);

// One entry of the score table's directory: where a stage's script starts.
struct ItemScoreTableEntry_00415db0 {
    int reserved_0;
    int offset;
};

// The 0x90-byte score display of one stage, built from its script by
// 0x00415B00.
struct ItemScoreDisplay_00415db0 {
    int stage;
    unsigned char reserved_04[0x90 - 0x04];

    __declspec(noinline) ItemScoreDisplay_00415db0(void* script);
};

// The item manager, as far as its score display goes.
struct ItemManager_00415db0 {
    unsigned char reserved_0000[0x9EB8];
    ItemScoreDisplay_00415db0* score_display;   // +0x9EB8
    ItemScoreTableEntry_00415db0* score_table;  // +0x9EBC, directory then scripts

    __declspec(noinline) void CreateScoreDisplay(int stage);
};

// The stage the game will play next, and progress within it.
extern "C" int g_stage_progress;
extern "C" int g_stage_progress_echo;
