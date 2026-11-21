#include "../../../src/game/pause/pause_choice_update.cpp"

#include "pause_choice/child.cpp"
#include "pause_choice/find.cpp"
#include "pause_choice/input_mask.cpp"
#include "pause_choice/input_mode.cpp"
#include "pause_choice/mark6.cpp"
#include "pause_choice/menu.cpp"
#include "pause_choice/queue.cpp"
#include "pause_choice/registrar.cpp"
#include "pause_choice/setflag.cpp"
#include "pause_choice/setstop.cpp"
#include "pause_choice/stop1.cpp"
#include "pause_choice/timer.cpp"
#include "pause_choice/unpause.cpp"

#pragma code_seg(".text$20present")
__declspec(noinline) int __fastcall AppPresent2(void*) { return 1; }
#pragma code_seg()
