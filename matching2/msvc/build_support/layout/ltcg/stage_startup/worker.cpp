#include <string.h>
#include "th10/game/stage_startup.hpp"
#include "th10/game/stage_route.hpp"
#include "th10/game/title_draw.hpp"
#include "th10/game/score_file.hpp"
#include "th10/core/func_ctrl.hpp"
#include "callback_task.hpp"
#include "path_reset.cpp"
#include "set_clock.cpp"
#include "retire_callbacks.cpp"
#include "../../../../src/game/game/game_initialize.cpp"

// Complete genuine worker at 0x00417C70; only stage startup is selected here.
struct Game;
extern "C" Game* g_game;
extern "C" __declspec(noinline) int __stdcall Game_Initialize(Game*);
#pragma code_seg(".text$00417c70_fn")
extern "C" void __cdecl Game_LoadThread() {
    Game_Initialize(g_game);
}
#pragma code_seg()
