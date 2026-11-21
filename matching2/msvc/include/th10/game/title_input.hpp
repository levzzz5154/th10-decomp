#pragma once
#include "menu_cursor.hpp"

struct ReplayFile;

// Both high-score entry and replay saving use this keyboard.
struct TitleNameKeyboard {
    char name[12];
    int name_length;
    int name_confirmed;
    int reserved_58f0;
    MenuCursor grid;
};

struct TitleReplayList {
    int reserved_59d8; // Cleared after enumerating the replay directory.
    int selected_replay;
    int selected_stage;
    ReplayFile* files[50]; // 25 numbered slots, then up to 25 user replays.
};

typedef char TitleNameGridOffset[offsetof(TitleNameKeyboard, grid) == 0x18 ? 1 : -1];
typedef char TitleReplayFilesOffset[offsetof(TitleReplayList, files) == 0x0C ? 1 : -1];
