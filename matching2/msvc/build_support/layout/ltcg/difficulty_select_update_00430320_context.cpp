// Compiler context for the difficulty selection screen 0x00430320 and the
// character selection screen 0x004306A0: their real
// caller (the title dispatcher, which pushes the room) and the real bodies of
// the animation-slot, timer, cursor and input leaves they call. The difficulty,
// the character and the key state are objects whose address is taken
// elsewhere in the program; the context takes them here.
#include "../../../src/game/title/difficulty_select_update.cpp"
#include "../../../src/game/title/ending_screen.cpp"
#include "../../../src/game/title/recovery_animation_slot_frames.cpp"
#include "th10/game/replay_save_update.hpp"
#include "th10/game/options_update.hpp"
#include "th10/game/recovery_script_executor_caller.hpp"
#include "th10/game/title_menu.hpp"
// 0x0042CDF0, a separate translation unit of this link.
__declspec(noinline) int __stdcall Title_DispatchUpdate(Title* room);

#pragma code_seg(".text$0040a000_context")
extern "C" int __stdcall DifficultySelectUpdateCompilerContext(
    RecoveryScriptState* script,
    HintLink* head,
    HintUpdateView* indicator, int release,
    Title* music_room, void** objects) {
    objects[0] = &g_globals_difficulty;
    objects[1] = &g_input_keys_raw;
    objects[2] = &g_globals_character;
    objects[3] = &g_input_keys_held;
    objects[4] = &g_globals_shot_type;
    objects[5] = &g_title_practice_selection;
    objects[6] = &g_practice_difficulty;
    objects[7] = g_keyboard_state;
    objects[8] = &g_main_state;
    objects[9] = &application_state;
    return RecoveryScript_Execute2(script) + head->Drain(indicator, release)
        + Title_UpdateMusicRoom(music_room)
        + Title_DispatchUpdate(music_room);
}
#pragma code_seg()
