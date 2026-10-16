#ifndef TH10_CHARACTER_SELECT_UPDATE_004306A0_HPP
#define TH10_CHARACTER_SELECT_UPDATE_004306A0_HPP
#include "th10/game/difficulty_select_update.hpp"

// The score file seen by the character selection: whether each character has
// cleared the game with each of her three shot types.
struct ScoreFile3 {
    unsigned char reserved_00000[0x1D888];
    unsigned char cleared[2][3];
};

extern "C" {
extern int g_globals_shot_type;               // shot type
extern ScoreFile3* g_score;
}

__declspec(noinline) int __stdcall TitleMode7(Title* room);
#endif
