#include "../../../src/core/sprtlib/recovery_mark_text_and_dispatcher_004479d0.cpp"
#include "../../include/contexts/game/marktext_dispatcher_context/recovery_script_executor_caller_00419120.hpp"
#include "../../include/contexts/game/marktext_dispatcher_context/recovery_script_executor_caller_00433ef0.hpp"
#pragma code_seg(".text$0040a000_context")
extern "C" int __stdcall RecoveryMarkTextDispatcherCompilerContext(
    RecoveryScriptState* script,
    HintLink* head,
    HintUpdateView* indicator, int release,
    Title* music_room) {
    return RecoveryScript_Execute_0040bd80(script) + head->Drain(indicator, release)
        + Title_UpdateMusicRoom(music_room);
}
#pragma code_seg()
