#ifndef TH10_PRACTICE_STAGE_SELECT_UPDATE_00430FF0_HPP
#define TH10_PRACTICE_STAGE_SELECT_UPDATE_00430FF0_HPP
#include "th10/game/shot_type_select_update.hpp"

extern "C" {
extern int g_title_practice_selection;               // practice stage selected last time
extern int g_globals_initial_lives;             // number key held when practice starts; 0 means 9 lives, n means n-1
extern unsigned char g_keyboard_state[256];    // keyboard snapshot
}

// 0x0044B010 as its callers see it: the snapshot buffer in EDX and nothing
// else (the maintained form is src/core/zunlib/keyboard_state.cpp).  Returns
// whether the snapshot holds DirectInput scan codes rather than virtual keys.
int __stdcall Input_UpdateKeyboardState(unsigned char* destination);

__declspec(noinline) int __stdcall TitleMode9(Title* room);
#endif
