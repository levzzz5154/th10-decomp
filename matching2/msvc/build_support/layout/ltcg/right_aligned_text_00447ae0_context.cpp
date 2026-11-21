#include "../../../src/core/sprtlib/sprite_draw_right_aligned_text.cpp"
#include "right_aligned_text_context/exact_text_dispatcher_anchor.cpp"
#include "th10/game/hint_text/recovery_script_executor_caller.hpp"
#include "th10/game/hint_text/recovery_script_executor_caller_433ef0.hpp"
#pragma code_seg(".text$0040a000_context")
extern "C" int __stdcall RecoveryMarkTextDispatcherCompilerContext(
    EndingScriptState* script,
    HintLink* head,
    HintUpdateView* indicator, int release,
    Title* music_room) {
    return RecoveryScript_Execute2(script) + head->Drain(indicator, release)
        + Title_UpdateMusicRoom(music_room);
}
#pragma code_seg()
