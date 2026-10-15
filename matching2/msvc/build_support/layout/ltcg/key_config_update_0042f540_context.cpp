// Compiler context for the key configuration screen 0x0042F540: its real
// caller (the title dispatcher, which keeps the room in EBX) and the real
// bodies of the animation-slot and timer leaves it calls. The configuration,
// its copy in the application state and the key state are objects whose
// address is taken elsewhere in the program; the context takes them here.
#include "../../../src/game/title/menu_flow_updates.cpp"
#include "../../../src/game/title/ending_screen.cpp"
#include "../../../src/game/title/recovery_animation_slot_frames_0042c6d0.cpp"
#include "th10/game/recovery_script_executor_caller_00419120.hpp"
#include "th10/game/title_menu.hpp"
// 0x0042CDF0, a separate translation unit of this link.
__declspec(noinline) int __stdcall Title_DispatchUpdate(Title* room);

#pragma code_seg(".text$0040a000_context")
extern "C" int __stdcall KeyConfigUpdateCompilerContext(
    RecoveryScriptState_0040bd80* script,
    HintLink_00419120* head,
    HintUpdateView* indicator, int release,
    Title* music_room, void** objects) {
    objects[0] = &g_key_bindings_current;
    objects[1] = &g_key_bindings;
    objects[2] = &g_input_keys_raw;
    return RecoveryScript_Execute_0040bd80(script) + head->Drain(indicator, release)
        + Title_UpdateMusicRoom(music_room)
        + Title_DispatchUpdate(music_room);
}
#pragma code_seg()
