#include "../../src/game/recovery_right_aligned_text_00447ae0.cpp"
#include "right_aligned_text_context/exact_text_dispatcher_anchor.cpp"
#include "th10/game/right_aligned_text_context/recovery_script_executor_caller_00419120.hpp"
#include "th10/game/right_aligned_text_context/recovery_script_executor_caller_00433ef0.hpp"
#pragma code_seg(".text$0040a000_context")
extern "C" int __stdcall RecoveryMarkTextDispatcherCompilerContext(
    RecoveryScriptState_0040bd80* script,
    RecoveryIndicatorLink_00419120* head,
    RecoveryIndicatorState_00419120* indicator, int release,
    RecoveryMusicRoom_00433ef0* music_room) {
    return RecoveryScript_Execute_0040bd80(script) + head->Drain(indicator, release)
        + RecoveryMusicRoom_Update_00433ef0(music_room);
}
#pragma code_seg()
