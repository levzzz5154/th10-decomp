// 0x00430FF0..0x0043140B: practice stage selection screen of the title menu
// (and its five-entry phase table).
//
// Phase 0 offers the six stages with the cursor on the one chosen last time,
// installs the stage list and the character's frame and runs phase 1 on the
// same frame.  Phase 1 waits eleven frames.  Phase 2 moves the cursor and
// handles cancel and confirm; a stage that has not been reached with the
// chosen character, shot type and difficulty only plays the refusal sound.
// Confirm also records which number key (1 to 9) is held, from virtual keys
// or from DirectInput scan codes.  Phase 3 starts the fade at frame 10 and
// starts the chosen stage after forty frames.  Phase 4 goes back to the shot
// type selection after six frames.
//
// The room is a stack argument; the handler is linked with the title
// dispatcher and the real bodies of its leaves
// (build_support/layout/ltcg/difficulty_select_update.json).
#include "th10/game/practice_stage_select_update.hpp"

// Select an item, clamped to the items the menu has.
static __forceinline void SelectItem8(MenuCursor& cursor, int index) {
    int count = cursor.item_count;
    if (count != 0)
        cursor.selection = index >= count ? count - 1 : (((index < 0) - 1) & index);
    else
        cursor.selection = index;
}

enum PracticeSelectPhase {
    PRAC_PHASE_ENTER = 0,
    PRAC_PHASE_WAIT_OPEN = 1,
    PRAC_PHASE_ACTIVE = 2,
    PRAC_PHASE_CONFIRM_LAUNCH = 3,
    PRAC_PHASE_CANCEL_LEAVE = 4
};

enum PracticeSelectConstants {
    PRAC_STAGE_COUNT = 6,
    PRAC_KEY_CANCEL = 0x000A,
    PRAC_KEY_UP = 0x0010,
    PRAC_KEY_DOWN = 0x0020,
    PRAC_KEY_CONFIRM = 0x1001,
    PRAC_SFX_CONFIRM = 10,
    PRAC_SFX_CANCEL = 11,
    PRAC_SFX_MOVE = 12,
    PRAC_SFX_INVALID = 0x25,
    PRAC_TARGET_LEAVE = 3,
    PRAC_TARGET_SHOT_TYPE = 8,
    PRAC_MAIN_MODE_GAME = 7
};

#pragma code_seg(".text$00430ff0_fn")
__declspec(noinline) int __stdcall TitleMode9(Title* room) {
    switch (room->phase) {
    case PRAC_PHASE_ENTER:
        room->cursor.item_count = PRAC_STAGE_COUNT;
        SelectItem8(room->cursor, g_title_practice_selection);
        RecoveryMusicInstallSlot(room, 106);
        {
            // MATCH: a named local: its symbol precedes the cursor's, which the
            // unlock test's operand order in phase 2 depends on.
            int character_slot = g_globals_character + 107;
            RecoveryMusicInstallSlot(room, character_slot);
        }
        room->SetTimerTarget(PRAC_PHASE_WAIT_OPEN);
    case PRAC_PHASE_WAIT_OPEN:
        if (room->timer.current > 10)
            room->SetTimerTarget(PRAC_PHASE_ACTIVE);
        break;
    case PRAC_PHASE_ACTIVE: {
        MenuCursor* cursor = &room->cursor;
        cursor->previous_selection = cursor->selection;
        if ((short)g_input_keys_raw.InputMaskActive(PRAC_KEY_UP)) cursor->Advance(-1);
        if ((short)g_input_keys_raw.InputMaskActive(PRAC_KEY_DOWN)) cursor->Advance(1);
        if (cursor->previous_selection != cursor->selection)
            g_sound_manager.Queue(PRAC_SFX_MOVE, 0);
        if (g_input_keys_held & PRAC_KEY_CANCEL) {
            room->SetTimerTarget(PRAC_PHASE_CANCEL_LEAVE);
            g_sound_manager.Queue(PRAC_SFX_CANCEL, 0);
            g_title_practice_selection = cursor->selection;
        } else if (g_input_keys_held & PRAC_KEY_CONFIRM) {
            if (g_score->shots[g_globals_character][g_globals_shot_type]
                    .practice[g_globals_difficulty][cursor->selection].unlocked == 0) {
                g_sound_manager.Queue(PRAC_SFX_INVALID, 0);
            } else {
                room->SetTimerTarget(PRAC_PHASE_CONFIRM_LAUNCH);
                g_sound_manager.Queue(PRAC_SFX_CONFIRM, 0);
            }
            g_title_practice_selection = cursor->selection;
            g_globals_initial_lives = 0;
            if (Input_UpdateKeyboardState(g_keyboard_state) == 0) {
                if (g_keyboard_state['1'] & 0x80) g_globals_initial_lives = 1;
                else if (g_keyboard_state['2'] & 0x80) g_globals_initial_lives = 2;
                else if (g_keyboard_state['3'] & 0x80) g_globals_initial_lives = 3;
                else if (g_keyboard_state['4'] & 0x80) g_globals_initial_lives = 4;
                else if (g_keyboard_state['5'] & 0x80) g_globals_initial_lives = 5;
                else if (g_keyboard_state['6'] & 0x80) g_globals_initial_lives = 6;
                else if (g_keyboard_state['7'] & 0x80) g_globals_initial_lives = 7;
                else if (g_keyboard_state['8'] & 0x80) g_globals_initial_lives = 8;
                else if (g_keyboard_state['9'] & 0x80) g_globals_initial_lives = 9;
            } else {
                if (g_keyboard_state[2] & 0x80) g_globals_initial_lives = 1;
                else if (g_keyboard_state[3] & 0x80) g_globals_initial_lives = 2;
                else if (g_keyboard_state[4] & 0x80) g_globals_initial_lives = 3;
                else if (g_keyboard_state[5] & 0x80) g_globals_initial_lives = 4;
                else if (g_keyboard_state[6] & 0x80) g_globals_initial_lives = 5;
                else if (g_keyboard_state[7] & 0x80) g_globals_initial_lives = 6;
                else if (g_keyboard_state[8] & 0x80) g_globals_initial_lives = 7;
                else if (g_keyboard_state[9] & 0x80) g_globals_initial_lives = 8;
                else if (g_keyboard_state[10] & 0x80) g_globals_initial_lives = 9;
            }
        }
        break;
    }
    case PRAC_PHASE_CONFIRM_LAUNCH:
        if (room->timer.current == 10) {
            g_ascii_manager->EnsureAnimationResource(480.0f, 392.0f);
            RecoveryAscii_Create(0x2b, 5, 0x20, 0, 0, 0);
        }
        if (room->timer.current >= 40) {
            MenuCursor* cursor = &room->cursor;
            cursor->PushSelection();
            room->DisableTimerWithOwner(PRAC_TARGET_LEAVE);
            int stage = cursor->selection + 1;
            g_stage_route_current = &g_stage_routes[stage];
            g_globals_stage = stage;
            g_globals_stage_shown = stage;
            Music_FadeOut(6.0f);
            g_main_state = PRAC_MAIN_MODE_GAME;
        }
        break;
    case PRAC_PHASE_CANCEL_LEAVE:
        if (room->timer.current >= 6) {
            room->ClearAnimationSlot(106);
            room->ClearAnimationSlot(g_globals_character + 107);
            room->DisableTimerWithOwner(PRAC_TARGET_SHOT_TYPE);
            room->cursor.PopSelection();
        }
        break;
    }
    return 1;
}
#pragma code_seg()
