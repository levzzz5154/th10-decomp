#ifndef TH10_TITLE_MAIN_MENU_UPDATE_0042D420_HPP
#define TH10_TITLE_MAIN_MENU_UPDATE_0042D420_HPP
#include "th10/game/shot_type_select_update.hpp"

// The score file seen by 0x0042C850, which reports whether any character has
// cleared the game with any shot type (the maintained form is
// src/game/title/progress.cpp).
struct ScoreFileProgress {
    unsigned char reserved_00000[0x1D888];
    unsigned char cleared[6];
    __declspec(noinline) int HasAnyClear();
};

__declspec(noinline) int __stdcall TitleMainMenu(Title* room);
#endif
