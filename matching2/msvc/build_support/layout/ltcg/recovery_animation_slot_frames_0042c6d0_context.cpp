#include "../../../src/game/title/recovery_animation_slot_frames.cpp"
#include "th10/game/recovery_script_executor_caller.hpp"
#include "th10/game/title_menu.hpp"
#pragma code_seg(".text$0040a000_context")
extern "C" int __stdcall RecoveryAnimationSlotFramesCompilerContext(
    RecoveryScriptState* script,
    HintLink* head,
    HintUpdateView* indicator, int release,
    Title* music_room) {
    return RecoveryScript_Execute2(script) + head->Drain(indicator, release)
        + Title_UpdateMusicRoom(music_room);
}
#pragma code_seg()
