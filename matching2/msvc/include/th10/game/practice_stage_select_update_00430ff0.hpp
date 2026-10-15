#ifndef TH10_PRACTICE_STAGE_SELECT_UPDATE_00430FF0_HPP
#define TH10_PRACTICE_STAGE_SELECT_UPDATE_00430FF0_HPP
#include "th10/game/shot_type_select_update_00430a60.hpp"

extern "C" {
extern int data_00491c08;               // practice stage selected last time
extern int data_00474cac;               // number key held when practice starts
extern unsigned char data_00497aa8[256];    // keyboard snapshot
}

// 0x0044B010 as its callers see it: the snapshot buffer in EDX and nothing
// else (the maintained form is src/core/zunlib/keyboard_state.cpp).  Returns
// whether the snapshot holds DirectInput scan codes rather than virtual keys.
int __stdcall Input_UpdateKeyboardState(unsigned char* destination);

__declspec(noinline) int __stdcall TitleMode9_00430ff0(Title* room);
#endif
