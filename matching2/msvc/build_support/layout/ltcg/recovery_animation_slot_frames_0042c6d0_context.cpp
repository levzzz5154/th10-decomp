#include "../../../src/game/title/title_animation_slot_frames.cpp"
#include "th10/game/ending_script_caller.hpp"
#include "th10/game/title_menu.hpp"
#pragma code_seg(".text$0040a000_context")
extern "C" int __stdcall RecoveryAnimationSlotFramesCompilerContext(
    EndingScriptState* script,
    HintLink* head,
    HintUpdateView* indicator, int release,
    Title* music_room) {
    return EndingScript_Execute(script) + head->Drain(indicator, release)
        + Title_UpdateMusicRoom(music_room);
}
#pragma code_seg()
