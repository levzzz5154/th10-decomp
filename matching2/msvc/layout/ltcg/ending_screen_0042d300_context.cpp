// Compiler context for the ending screen handler 0x0042D300: its real caller
// (the title dispatcher, which keeps the room in EBX) and the real bodies of
// the animation-slot and timer leaves it calls.
#include "../../src/game/ending_screen.cpp"
#include "ending_screen_dependencies/title_dispatcher.cpp"
#include "../../src/game/recovery_animation_slot_frames_0042c6d0.cpp"
#include "th10/game/recovery_script_executor_caller_00419120.hpp"
#include "th10/game/recovery_script_executor_caller_00433ef0.hpp"
#pragma code_seg(".text$0040a000_context")
extern "C" int __stdcall EndingScreenCompilerContext(
    RecoveryScriptState_0040bd80* script,
    RecoveryIndicatorLink_00419120* head,
    RecoveryIndicatorState_00419120* indicator, int release,
    RecoveryMusicRoom_00433ef0* music_room) {
    return RecoveryScript_Execute_0040bd80(script) + head->Drain(indicator, release)
        + RecoveryMusicRoom_Update_00433ef0(music_room)
        + TitleDispatcher_Update_0042cdf0(music_room);
}
#pragma code_seg()
