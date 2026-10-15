#ifndef TH10_GAME_TITLE_MENU_DRAW_HPP
#define TH10_GAME_TITLE_MENU_DRAW_HPP

#include <stddef.h>
#include <time.h>

#include "th10/game/game_thread_queue_native.hpp"

// One high score table row.
struct ScoreEntry {
    int score;                           // +0x00
    char stage;                          // +0x04
    char continues;                      // +0x05
    char name[10];                       // +0x06
    time_t date;                         // +0x10
    float slowdown;                      // +0x14
};

struct PracticeRecord {
    int best_score;                      // +0x00
    unsigned char pad_04;
    unsigned char unlocked;              // +0x05
    unsigned char pad_06[2];
};

// The score file's per-character block.
struct ScoreTable_004329f0 {
    unsigned char pad_00[0x10];
    ScoreEntry rows[5][10];     // +0x10
};

struct ScoreCharacter {
    unsigned char pad_000[0x08];
    ScoreTable_004329f0 table;           // +0x008
    int play_count;                      // +0x4C8
    int play_time;                       // +0x4CC, in frames
    int clear_count[5];                  // +0x4D0
    PracticeRecord practice[1]; // +0x4E4: six per difficulty
    unsigned char pad_4EC[0x437C - 0x4EC];
};

// Part of the global game state; the title menus write it through pointers.
struct GameSelection_00431410 {
    int shot_type;                       // 0x00474C68
    int character;                       // 0x00474C6C
    int unknown_08;
    int difficulty;                      // 0x00474C74
};

// The header block of a loaded replay.
struct ReplayHeader_00431ba0 {
    char name[12];                       // +0x00
    time_t date;                         // +0x0C
    int score;                           // +0x10
    unsigned char pad_14[0x48 - 0x14];
    float slowdown;                      // +0x48
    unsigned char pad_4C[4];
    int character;                       // +0x50
    int shot_type;                       // +0x54
    int difficulty;                      // +0x58
    int stage;                           // +0x5C
    int final_value_60;                  // +0x60
};

// A replay's per-stage starting state.
struct ReplayStage_00431ba0 {
    unsigned char pad_000[0x0C];
    int score;                           // +0x00C
    unsigned char pad_010[0x1B4 - 0x10];
    int value_1b4;                       // +0x1B4
};

struct ReplayStageSlot {
    ReplayStage_00431ba0* data;          // +0x00
    unsigned char pad_04[0x20];
};

struct ReplayFile_00431ba0 {
    unsigned char pad_00[0x18];
    ReplayHeader_00431ba0* header;       // +0x18
    unsigned char pad_1C[0xB0 - 0x1C];
    ReplayStageSlot stages[8];  // +0xB0, indexed by stage number
};

struct TitleDrawView {
    unsigned char pad_000[0x1C];
    int page;                            // +0x01C
    int phase;                           // +0x020
    int cursor;                          // +0x024
    unsigned char pad_028[0xFC - 0x28];
    int difficulty;                      // +0x0FC
    unsigned char pad_100[0x1D4 - 0x100];
    int spell_page;                      // +0x1D4: 0 shows the score rows
    unsigned char pad_1D8[0x2AC - 0x1D8];
    int listed_spells;                   // +0x2AC
    int unknown_2b0;
    int phase_frames;                    // +0x2B4
    float phase_elapsed;                 // +0x2B8
    unsigned char pad_2BC[0x5D4 - 0x2BC];
    unsigned int spell_lines[10];        // +0x5D4: text animation ids
    unsigned char pad_5FC[0x58DC - 0x5FC];
    char name[12];                       // +0x58DC: high score name being typed
    int name_length;                     // +0x58E8
    int name_confirmed;                  // +0x58EC
    int unknown_58f0;
    int name_cell;                       // +0x58F4: chosen cell of the character grid
    unsigned char pad_58F8[0x59DC - 0x58F8];
    int selected_replay;                 // +0x59DC
    int unknown_59e0;
    ReplayFile_00431ba0* replays[25];    // +0x59E4

    __declspec(noinline) int DrawOverlay();
    __declspec(noinline) int DrawPracticeRows();
    __declspec(noinline) int DrawScoreRows();
    __declspec(noinline) int BuildSpellList();
};

extern "C" {
extern GameThread_00401530* g_ascii_manager;
extern GameSelection_00431410 g_globals_character;
extern ScoreCharacter* g_score;
extern ReplayFile_00431ba0* g_replay;  // the replay just played
extern const char* g_name_entry_grid;        // the name entry character grid
extern const char* g_stage_names_long[];      // "test", "Stage 1" .. "Stage 6", "Extra"
extern const char* g_shot_names[];      // "ReimuA" .. "MarisaC"
extern const char* g_difficulty_names[];      // "Easy" .. "Extra"
extern const char* g_stage_names_short[];      // "tst", "St1" .. "Ex", "All", "ExA"
}

typedef char ScoreEntry_size[sizeof(ScoreEntry) == 0x18 ? 1 : -1];
typedef char ScoreCharacter_practice[offsetof(ScoreCharacter, practice) == 0x4E4 ? 1 : -1];
typedef char ScoreCharacter_size[sizeof(ScoreCharacter) == 0x437C ? 1 : -1];

#endif
