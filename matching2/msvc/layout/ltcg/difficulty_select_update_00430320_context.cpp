// Compiler context for the difficulty selection screen 0x00430320 and the
// character selection screen 0x004306A0: their real
// caller (the title dispatcher, which pushes the room) and the real bodies of
// the animation-slot, timer, cursor and input leaves they call. The difficulty,
// the character and the key state are objects whose address is taken
// elsewhere in the program; the context takes them here.
#include "../../src/game/difficulty_select_update_00430320.cpp"
#include "../../src/game/ending_screen.cpp"
#include "../../src/game/recovery_animation_slot_frames_0042c6d0.cpp"
#include "th10/game/practice_stage_select_update_00430ff0.hpp"
#include "th10/game/recovery_script_executor_caller_00419120.hpp"
#include "th10/game/recovery_script_executor_caller_00433ef0.hpp"
// 0x0042CDF0, a separate translation unit of this link.
__declspec(noinline) int __stdcall TitleDispatcher_Update_0042cdf0(RecoveryMusicRoom_00433ef0* room);

#pragma code_seg(".text$0040a000_context")
extern "C" int __stdcall DifficultySelectUpdateCompilerContext(
    RecoveryScriptState_0040bd80* script,
    RecoveryIndicatorLink_00419120* head,
    RecoveryIndicatorState_00419120* indicator, int release,
    RecoveryMusicRoom_00433ef0* music_room, void** objects) {
    objects[0] = &data_00474c74;
    objects[1] = &data_00474e30;
    objects[2] = &data_00474c68;
    objects[3] = &data_00474e36;
    objects[4] = &data_00474c6c;
    objects[5] = &data_00491c08;
    objects[6] = &data_00474cac;
    objects[7] = data_00497aa8;
    return RecoveryScript_Execute_0040bd80(script) + head->Drain(indicator, release)
        + RecoveryMusicRoom_Update_00433ef0(music_room)
        + TitleDispatcher_Update_0042cdf0(music_room);
}
#pragma code_seg()
