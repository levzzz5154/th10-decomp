#ifndef TH10_GAME_NAME_ENTRY_PREPARE_00423570_HPP
#define TH10_GAME_NAME_ENTRY_PREPARE_00423570_HPP
#include <stddef.h>
#include "th10/game/menu_cursor.hpp"
#include "th10/game/score_table_insert.hpp"

// Everything the score file keeps for one character and shot type.
struct ScorePlayerData {
    ScoreTable table;
    unsigned char reserved_4c0[0x437C - sizeof(ScoreTable)];
};

// The loaded score file at *0x0047783C.
struct ScoreFile2 {
    unsigned char reserved_00[8];
    ScorePlayerData players[7];   // +0x08: shot type + character * 3
    unsigned char reserved_1d86c[0xC];
    char last_name[9];                     // +0x1D878: the name entered last time
};
typedef char ScoreFileNameOffset[offsetof(ScoreFile2, last_name) == 0x1D878 ? 1 : -1];

// One row of the stage table at 0x00474788.
struct StageInfo {
    unsigned char reserved_00[0x30];
};

// The result screen that owns the name entry.
struct NameEntryMenu {
    unsigned char reserved_00[0x24];
    MenuCursor rows;              // +0x24: the score rows; the new record is selected
    MenuCursor alphabet;          // +0xFC: the character grid
    unsigned char reserved_1d4[0xC];
    int name_length;              // +0x1E0
    int extra_cleared;            // +0x1E4: stage 7 was finished; the record counts as stage 8
    int no_entry;                 // +0x1E8: the score did not reach the table
    unsigned char reserved_1ec[0xC8];
    char name[9];                 // +0x2B4
};
typedef char NameEntryMenuNameOffset[offsetof(NameEntryMenu, name) == 0x2B4 ? 1 : -1];

extern "C" ScoreFile2* g_score;
extern "C" StageInfo g_stage_routes[];
extern "C" StageInfo* g_stage_route_current;   // the current stage's row
extern "C" const char* g_name_entry_grid;           // the name entry character grid

// 0x00423570: enter the score and set up the name entry.
void __stdcall PrepareNameEntry(NameEntryMenu* menu);

#endif
