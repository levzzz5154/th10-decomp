#include "../../src/game/recovery_mark_text_and_dispatcher_004479d0.cpp"
#include "th10/game/marktext_dispatcher_context/recovery_script_executor_caller_00419120.hpp"
#include "th10/game/marktext_dispatcher_context/recovery_script_executor_caller_00433ef0.hpp"
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
