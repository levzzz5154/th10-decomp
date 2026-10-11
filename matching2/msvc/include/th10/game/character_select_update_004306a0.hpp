#ifndef TH10_CHARACTER_SELECT_UPDATE_004306A0_HPP
#define TH10_CHARACTER_SELECT_UPDATE_004306A0_HPP
#include "th10/game/difficulty_select_update_00430320.hpp"

// The score file seen by the character selection: whether each character has
// cleared the game with each of her three shot types.
struct ScoreFile_004306a0 {
    unsigned char reserved_00000[0x1D888];
    unsigned char cleared[2][3];
};

extern "C" {
extern int data_00474c6c;               // shot type
extern ScoreFile_004306a0* data_0047783c;
}

__declspec(noinline) int __stdcall TitleMode7_004306a0(RecoveryMusicRoom_00433ef0* room);
#endif
