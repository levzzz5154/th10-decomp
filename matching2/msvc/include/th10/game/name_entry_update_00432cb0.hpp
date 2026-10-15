#ifndef TH10_NAME_ENTRY_UPDATE_00432CB0_HPP
#define TH10_NAME_ENTRY_UPDATE_00432CB0_HPP
#include "th10/game/replay_save_update_00433570.hpp"
#include "th10/game/score_table_insert_00421fa0.hpp"

// The score file as the name entry sees it: the high-score tables of each
// character and shot type.
struct NameEntryShotScore {
    unsigned char reserved_0000[8];
    ScoreTable_00421fa0 table;          // +0x08
    unsigned char reserved_04c8[0x437C - 0x4C8];
};
struct NameEntryScoreFile {
    NameEntryShotScore shots[2][3];
    unsigned char reserved_194e8[0x1D878 - 0x194E8];
    char last_name[9];                  // +0x1D878: the name entered last time
};
typedef char NameEntryShotScoreSize[sizeof(NameEntryShotScore) == 0x437C ? 1 : -1];
typedef char NameEntryLastName[offsetof(NameEntryScoreFile, last_name) == 0x1D878 ? 1 : -1];

__declspec(noinline) int __stdcall TitleNameEntry(Title* room);
#endif
