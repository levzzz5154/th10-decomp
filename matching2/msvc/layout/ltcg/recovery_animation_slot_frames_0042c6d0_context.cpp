#include "../../src/game/title/recovery_animation_slot_frames_0042c6d0.cpp"
#include "th10/game/recovery_script_executor_caller_00419120.hpp"
#include "th10/game/recovery_script_executor_caller_00433ef0.hpp"
#pragma code_seg(".text$0040a000_context")
extern "C" int __stdcall RecoveryAnimationSlotFramesCompilerContext(
    RecoveryScriptState_0040bd80* script,
    HintLink_00419120* head,
    HintUpdateView* indicator, int release,
    RecoveryMusicRoom_00433ef0* music_room) {
    return RecoveryScript_Execute_0040bd80(script) + head->Drain(indicator, release)
        + RecoveryMusicRoom_Update_00433ef0(music_room);
}
#pragma code_seg()
