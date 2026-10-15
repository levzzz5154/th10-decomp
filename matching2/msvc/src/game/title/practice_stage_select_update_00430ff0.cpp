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
// (build_support/layout/ltcg/difficulty_select_update_00430320.json).
#include "th10/game/practice_stage_select_update_00430ff0.hpp"

// Select an item, clamped to the items the menu has.
static __forceinline void SelectItem_00430ff0(MenuCursor& cursor, int index) {
    int count = cursor.item_count;
    if (count != 0)
        cursor.selection = index >= count ? count - 1 : (((index < 0) - 1) & index);
    else
        cursor.selection = index;
}

#pragma code_seg(".text$00430ff0_fn")
__declspec(noinline) int __stdcall TitleMode9_00430ff0(Title* room) {
    switch (room->phase) {
    case 0:
        room->cursor.item_count = 6;
        SelectItem_00430ff0(room->cursor, data_00491c08);
        RecoveryMusicInstallSlot_0042c670(room, 106);
        {
            // A named local: its symbol precedes the cursor's, which the
            // unlock test's operand order in phase 2 depends on.
            int character_slot = data_00474c68 + 107;
            RecoveryMusicInstallSlot_0042c670(room, character_slot);
        }
        room->SetTimerTarget(1);
    case 1:
        if (room->timer.current > 10)
            room->SetTimerTarget(2);
        break;
    case 2: {
        MenuCursor* cursor = &room->cursor;
        cursor->previous_selection = cursor->selection;
        if ((short)data_00474e30.InputMaskActive(0x10)) cursor->Advance(-1);
        if ((short)data_00474e30.InputMaskActive(0x20)) cursor->Advance(1);
        if (cursor->previous_selection != cursor->selection)
            data_00492590.Queue(12, 0);
        if (data_00474e36 & 0xa) {
            room->SetTimerTarget(4);
            data_00492590.Queue(11, 0);
            data_00491c08 = cursor->selection;
        } else if (data_00474e36 & 0x1001) {
            if (data_0047783c->shots[data_00474c68][data_00474c6c]
                    .practice[data_00474c74][cursor->selection].unlocked == 0) {
                data_00492590.Queue(0x25, 0);
            } else {
                room->SetTimerTarget(3);
                data_00492590.Queue(10, 0);
            }
            data_00491c08 = cursor->selection;
            data_00474cac = 0;
            if (Input_UpdateKeyboardState(data_00497aa8) == 0) {
                if (data_00497aa8['1'] & 0x80) data_00474cac = 1;
                else if (data_00497aa8['2'] & 0x80) data_00474cac = 2;
                else if (data_00497aa8['3'] & 0x80) data_00474cac = 3;
                else if (data_00497aa8['4'] & 0x80) data_00474cac = 4;
                else if (data_00497aa8['5'] & 0x80) data_00474cac = 5;
                else if (data_00497aa8['6'] & 0x80) data_00474cac = 6;
                else if (data_00497aa8['7'] & 0x80) data_00474cac = 7;
                else if (data_00497aa8['8'] & 0x80) data_00474cac = 8;
                else if (data_00497aa8['9'] & 0x80) data_00474cac = 9;
            } else {
                if (data_00497aa8[2] & 0x80) data_00474cac = 1;
                else if (data_00497aa8[3] & 0x80) data_00474cac = 2;
                else if (data_00497aa8[4] & 0x80) data_00474cac = 3;
                else if (data_00497aa8[5] & 0x80) data_00474cac = 4;
                else if (data_00497aa8[6] & 0x80) data_00474cac = 5;
                else if (data_00497aa8[7] & 0x80) data_00474cac = 6;
                else if (data_00497aa8[8] & 0x80) data_00474cac = 7;
                else if (data_00497aa8[9] & 0x80) data_00474cac = 8;
                else if (data_00497aa8[10] & 0x80) data_00474cac = 9;
            }
        }
        break;
    }
    case 3:
        if (room->timer.current == 10) {
            g_ascii_manager->EnsureAnimationResource(480.0f, 392.0f);
            RecoveryAscii_Create_0043c8b0(0x2b, 5, 0x20, 0, 0, 0);
        }
        if (room->timer.current >= 40) {
            MenuCursor* cursor = &room->cursor;
            cursor->PushSelection();
            room->DisableTimerWithOwner(3);
            int stage = cursor->selection + 1;
            data_00477848 = data_00474788 + stage * 0x30;
            data_00474c7c = stage;
            data_00474c80 = stage;
            Music_FadeOut(6.0f);
            data_00491fb8 = 7;
        }
        break;
    case 4:
        if (room->timer.current >= 6) {
            room->ClearAnimationSlot(106);
            room->ClearAnimationSlot(data_00474c68 + 107);
            room->DisableTimerWithOwner(8);
            room->cursor.PopSelection();
        }
        break;
    }
    return 1;
}
#pragma code_seg()
