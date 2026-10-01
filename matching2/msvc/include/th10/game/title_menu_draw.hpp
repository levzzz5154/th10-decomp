#ifndef TH10_GAME_TITLE_MENU_DRAW_HPP
#define TH10_GAME_TITLE_MENU_DRAW_HPP

#include <stddef.h>
#include <time.h>

#include "th10/game/game_thread_queue_native.hpp"

// One high score table row.
struct ScoreEntry_004329f0 {
    int score;                           // +0x00
    char stage;                          // +0x04
    char continues;                      // +0x05
    char name[10];                       // +0x06
    time_t date;                         // +0x10
    float slowdown;                      // +0x14
};

struct PracticeRecord_00431410 {
    int best_score;                      // +0x00
    unsigned char pad_04;
    unsigned char unlocked;              // +0x05
    unsigned char pad_06[2];
};

// The score file's per-character block.
struct ScoreTable_004329f0 {
    unsigned char pad_00[0x10];
    ScoreEntry_004329f0 rows[5][10];     // +0x10
};

struct ScoreCharacter_00431410 {
    unsigned char pad_000[0x08];
    ScoreTable_004329f0 table;           // +0x008
    int play_count;                      // +0x4C8
    int play_time;                       // +0x4CC, in frames
    int clear_count[5];                  // +0x4D0
    PracticeRecord_00431410 practice[1]; // +0x4E4: six per difficulty
    unsigned char pad_4EC[0x437C - 0x4EC];
};

// Part of the global game state; the title menus write it through pointers.
struct GameSelection_00431410 {
    int shot_type;                       // 0x00474C68
    int character;                       // 0x00474C6C
    int unknown_08;
    int difficulty;                      // 0x00474C74
};

struct TitleMenu_00431410 {
    unsigned char pad_000[0x1C];
    int page;                            // +0x01C
    int phase;                           // +0x020
    int cursor;                          // +0x024
    unsigned char pad_028[0xFC - 0x28];
    int difficulty;                      // +0x0FC
    unsigned char pad_100[0x1D4 - 0x100];
    int rows_hidden;                     // +0x1D4
    unsigned char pad_1D8[0x2B4 - 0x1D8];
    int phase_frames;                    // +0x2B4

    __declspec(noinline) int DrawOverlay();
    __declspec(noinline) int DrawPracticeRows();
    __declspec(noinline) int DrawScoreRows();
};

extern "C" {
extern GameThread_00401530* data_004776e0;
extern GameSelection_00431410 data_00474c68;
extern ScoreCharacter_00431410* data_0047783c;
extern const char* data_0047471c[];      // "test", "Stage 1" .. "Stage 6", "Extra"
}

typedef char ScoreEntry_size[sizeof(ScoreEntry_004329f0) == 0x18 ? 1 : -1];
typedef char ScoreCharacter_practice[offsetof(ScoreCharacter_00431410, practice) == 0x4E4 ? 1 : -1];
typedef char ScoreCharacter_size[sizeof(ScoreCharacter_00431410) == 0x437C ? 1 : -1];

#endif
