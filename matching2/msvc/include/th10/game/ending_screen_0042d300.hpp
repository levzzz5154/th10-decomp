#ifndef TH10_ENDING_SCREEN_0042D300_HPP
#define TH10_ENDING_SCREEN_0042D300_HPP
#include "th10/game/recovery_script_executor_caller_00433ef0.hpp"
#include "th10/platform/sound_queue.hpp"

extern "C" void* data_00491c10;
extern "C" unsigned int data_00474e36;
__declspec(noinline) void __stdcall RecoveryMusicInstallSlot_0042c670(
    RecoveryMusicRoom_00433ef0* room, int index);
// 0x00409E50: stop the animation tree a handle refers to.
__declspec(noinline) void __stdcall RecoveryMusicStopHandle_00409e50(RecoveryHandle_0040bd80* handle);

// 0x0042D300: ending screen phase handler; the room arrives in EBX.
__declspec(noinline) int __stdcall EndingScreen_Update_0042d300(
    RecoveryMusicRoom_00433ef0* room);
#endif
