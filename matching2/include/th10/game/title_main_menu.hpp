#pragma once

#include <cstdint>

enum TitleMenuInput : uint32_t {
    TITLE_MENU_UP = 0x10,
    TITLE_MENU_DOWN = 0x20,
    TITLE_MENU_CANCEL = 0x0A,
    TITLE_MENU_CONFIRM = 0x1001,
};

enum TitleMenuAction {
    TITLE_MENU_ACTION_NONE = 0,
    TITLE_MENU_ACTION_START,
    TITLE_MENU_ACTION_EXTRA,
    TITLE_MENU_ACTION_PRACTICE,
    TITLE_MENU_ACTION_REPLAY,
    TITLE_MENU_ACTION_MUSIC_ROOM,
    TITLE_MENU_ACTION_RESULTS,
    TITLE_MENU_ACTION_OPTIONS,
    TITLE_MENU_ACTION_QUIT,
};

struct TitleMainMenuState {
    int phase;
    int selection;
    int previous_selection;
    int item_count;
    int phase_frame;
    TitleMenuAction pending_action;
};

void TitleMainMenu_Initialize(TitleMainMenuState* state);
TitleMenuAction TitleMainMenu_Update(TitleMainMenuState* state,
                                     uint32_t input_flags);
