#include "../../../src/core/sprtlib/recovery_right_aligned_text.cpp"
#include "right_aligned_text_context/exact_text_dispatcher_anchor.cpp"
#include "../../include/contexts/game/right_aligned_text_context/recovery_script_executor_caller.hpp"
#include "../../include/contexts/game/right_aligned_text_context/recovery_script_executor_caller_433ef0.hpp"
#pragma code_seg(".text$0040a000_context")
extern "C" int __stdcall RecoveryMarkTextDispatcherCompilerContext(
    RecoveryScriptState* script,
    HintLink* head,
    HintUpdateView* indicator, int release,
    Title* music_room) {
    return RecoveryScript_Execute2(script) + head->Drain(indicator, release)
        + Title_UpdateMusicRoom(music_room);
}
#pragma code_seg()
