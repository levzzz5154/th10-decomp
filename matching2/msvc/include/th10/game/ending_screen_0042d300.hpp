#ifndef TH10_ENDING_SCREEN_0042D300_HPP
#define TH10_ENDING_SCREEN_0042D300_HPP
#include "th10/game/title_menu.hpp"
#include "th10/platform/sound_queue.hpp"

extern "C" void* g_sprt_ctrl;
extern "C" unsigned int g_input_keys_held;
__declspec(noinline) void __stdcall RecoveryMusicInstallSlot(
    Title* room, int index);
// 0x00409E50: stop the animation tree a handle refers to.
__declspec(noinline) void __stdcall RecoveryMusicStopHandle_00409e50(RecoveryHandle_0040bd80* handle);

// 0x0042D300: ending screen phase handler; the room arrives in EBX.
__declspec(noinline) int __stdcall EndingScreen_Update_0042d300(
    Title* room);
#endif
