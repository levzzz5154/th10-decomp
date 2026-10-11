// Compiler context for the key configuration screen 0x0042F540: its real
// caller (the title dispatcher, which keeps the room in EBX) and the real
// bodies of the animation-slot and timer leaves it calls. The configuration,
// its copy in the application state and the key state are objects whose
// address is taken elsewhere in the program; the context takes them here.
#include "../../src/game/menu_flow_updates.cpp"
#include "../../src/game/ending_screen.cpp"
#include "../../src/game/recovery_animation_slot_frames_0042c6d0.cpp"
#include "th10/game/recovery_script_executor_caller_00419120.hpp"
#include "th10/game/recovery_script_executor_caller_00433ef0.hpp"
// 0x0042CDF0, a separate translation unit of this link.
__declspec(noinline) int __stdcall TitleDispatcher_Update_0042cdf0(RecoveryMusicRoom_00433ef0* room);

#pragma code_seg(".text$0040a000_context")
extern "C" int __stdcall KeyConfigUpdateCompilerContext(
    RecoveryScriptState_0040bd80* script,
    RecoveryIndicatorLink_00419120* head,
    RecoveryIndicatorState_00419120* indicator, int release,
    RecoveryMusicRoom_00433ef0* music_room, void** objects) {
    objects[0] = &data_00474e88;
    objects[1] = &data_00491d4c;
    objects[2] = &data_00474e30;
    return RecoveryScript_Execute_0040bd80(script) + head->Drain(indicator, release)
        + RecoveryMusicRoom_Update_00433ef0(music_room)
        + TitleDispatcher_Update_0042cdf0(music_room);
}
#pragma code_seg()
