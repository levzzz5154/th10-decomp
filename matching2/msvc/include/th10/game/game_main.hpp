#ifndef TH10_GAME_MAIN_00438AD0_HPP
#define TH10_GAME_MAIN_00438AD0_HPP
#include <stddef.h>
#include "th10/app/application.hpp"

struct MidiSequencer;
struct GameFrame;
struct Holder2;
struct SprtCtrlStateCacheView;

// A Win32 MSG.
struct Message2 {
    void* window;
    unsigned int message;
    unsigned int parameter;
    long detail;
    unsigned int time;
    long x, y;
};

// 0x00438AD0: the game's WinMain. Always returns 0.
__declspec(noinline) int __stdcall GameMain2(
    void* instance, void* previous, char* command_line, int show);
#endif
