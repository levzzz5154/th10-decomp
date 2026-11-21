#include "../../../src/core/sprtlib/sprite_text_dispatcher.cpp"
#include "th10/game/ending_script/script_executor_caller.hpp"
#include "th10/game/ending_script/script_executor_caller_433ef0.hpp"
#pragma code_seg(".text$0040a000_context")
extern "C" int __stdcall RecoveryMarkTextDispatcherCompilerContext(
    EndingScriptState* script,
    HintLink* head,
    HintUpdateView* indicator, int release,
    Title* music_room) {
    return EndingScript_Execute(script) + head->Drain(indicator, release)
        + Title_UpdateMusicRoom(music_room);
}
#pragma code_seg()
