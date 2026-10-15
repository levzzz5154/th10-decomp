#ifndef TH10_APP_MAIN_TASK_MODE_HPP
#define TH10_APP_MAIN_TASK_MODE_HPP
#include "th10/platform/sound_fade_manager_wave18.hpp"

// Objects owned by one mode of the main task; each is created when its mode
// is entered and destroyed when the next mode replaces it.
struct Game;   // the menu screen (argument at +0x5C)
struct Title;   // the running game
struct ScoreOwnedObject;       // the result screen

extern "C" Game* g_game;
extern "C" Title* g_title;
extern "C" ScoreOwnedObject* g_ending;
extern "C" int data_00491c00;

// One row of the stage table at 0x00474788.
struct StageRouteWave18 {
    unsigned char bytes[0x30];
};
extern "C" StageRouteWave18 data_00474788[];
extern "C" StageRouteWave18* data_00477848;   // the current stage's row

// The menu screen keeps the argument it was created with.
struct GameUiArgumentWave18 {
    unsigned char reserved[0x5C];
    unsigned int argument;
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
