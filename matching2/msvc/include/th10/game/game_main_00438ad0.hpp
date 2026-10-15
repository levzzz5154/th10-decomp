#ifndef TH10_GAME_MAIN_00438AD0_HPP
#define TH10_GAME_MAIN_00438AD0_HPP
#include <stddef.h>
#include "th10/app/application.hpp"

struct MidiSequencer;
struct GameFrame_00439390;
struct Holder_00438a30;
struct SprtCtrlStateCacheView;

// A Win32 MSG.
struct Message_00438ad0 {
    void* window;
    unsigned int message;
    unsigned int parameter;
    long detail;
    unsigned int time;
    long x, y;
};

// 0x00438AD0: the game's WinMain. Always returns 0.
__declspec(noinline) int __stdcall GameMain_00438ad0(
    void* instance, void* previous, char* command_line, int show);
#endif
