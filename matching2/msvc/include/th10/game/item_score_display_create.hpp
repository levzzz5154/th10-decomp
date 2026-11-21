#pragma once
#include <stddef.h>

void* __cdecl operator new(unsigned int size);
void __cdecl operator delete(void* block);

// One entry of the stage dialogue message (.msg) directory table.
struct FrontDialogueTableEntry {
    int reserved_0;
    int offset;
};

// The 0x90-byte dialogue/message state built from a stage .msg script by
// 0x00415B00.
struct FrontDialogueState {
    int stage;
    unsigned char reserved_04[0x90 - 0x04];

    __declspec(noinline) FrontDialogueState(void* script);
};

// Front (HUD) view covering the active dialogue object and loaded .msg table.
struct FrontDialogueOwner {
    unsigned char reserved_0000[0x9EB8];
    FrontDialogueState* score_display;   // +0x9EB8
    FrontDialogueTableEntry* score_table;  // +0x9EBC, directory then scripts

    __declspec(noinline) void StartDialogue(int stage);
};

// The stage the game will play next, and progress within it.
extern "C" int g_stage_progress;
extern "C" int g_stage_progress_echo;
