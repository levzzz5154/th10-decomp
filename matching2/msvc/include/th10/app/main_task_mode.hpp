#ifndef TH10_APP_MAIN_TASK_MODE_HPP
#define TH10_APP_MAIN_TASK_MODE_HPP
#include "th10/platform/sound_fade_manager_wave18.hpp"
#include "th10/game/stage_route.hpp"

// Objects owned by one mode of the main task; each is created when its mode
// is entered and destroyed when the next mode replaces it.
struct Game;             // active gameplay/stage controller (replay_mode flag at +0x5C)
struct Title;            // title / main menu screen
struct ScoreOwnedObject; // ending / staffroll screen

extern "C" Game* g_game;
extern "C" Title* g_title;
extern "C" ScoreOwnedObject* g_ending;
extern "C" int g_main_mode_request;

// Gameplay keeps the mode argument (0 = normal play, 1 = replay playback) at +0x5C.
struct GameUiArgumentWave18 {
    unsigned char reserved[0x5C];
    unsigned int argument;
};

enum MainTaskModeId {
    MAIN_MODE_BOOT = 0,
    MAIN_MODE_LOADING = 1,
    MAIN_MODE_INIT_DONE = 2,
    MAIN_MODE_QUIT = 3,
    MAIN_MODE_TITLE = 4,
    MAIN_MODE_GAME = 7,
    MAIN_MODE_GAME_NEXT_STAGE = 10,
    MAIN_MODE_GAME_RESTART = 11,
    MAIN_MODE_GAME_REPLAY = 12,
    MAIN_MODE_GAME_RELOAD = 13,
    MAIN_MODE_ENDING = 14,
    MAIN_MODE_TITLE_RETURN = 15
};

enum MainTaskUpdateResult {
    MAIN_TASK_CONTINUE = 1,
    MAIN_TASK_QUIT = 4
};

extern "C" void (__stdcall *imp_EnterCriticalSection)(void*);   // EnterCriticalSection
extern "C" void (__stdcall *imp_LeaveCriticalSection)(void*);   // LeaveCriticalSection

extern "C" void* __cdecl ModeCreateStateWave18();
extern "C" void __stdcall ModeReleaseGlobalsWave18();
extern "C" void* __cdecl ModeCreateProgressWave18();
extern "C" void* __stdcall ModeCreateUiWave18(unsigned int);
extern "C" void* __stdcall ModeCreateSmallWave18();
__declspec(noinline) void Game_Delete(Game*);
__declspec(noinline) void Title_Delete(Title*);
__declspec(noinline) void ScoreOwnedObject_Destroy(ScoreOwnedObject*);

#endif
