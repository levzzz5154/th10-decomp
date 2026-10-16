// 0x004306A0..0x00430A5B: character selection screen of the title menu (and
// its five-entry phase table).
//
// Phase 0 offers the two characters; for the extra stage a character who has
// not cleared the game with any shot type is disabled and the cursor moved
// off her.  It installs and starts the selection animation and runs phase 1
// on the same frame.  Phase 1 waits seven frames.  Phase 2 moves the cursor
// with left and right and handles cancel and confirm: on confirm the chosen
// character's two children stop at frame 6 and the other's at frame 1.
// Phase 3 leaves for the shot type selection after fourteen frames, keeping
// the remembered shot type only when the character did not change; phase 4
// goes back to the difficulty selection after six.
//
// The room is a stack argument; the handler is linked with the title
// dispatcher and the real bodies of its leaves
// (build_support/layout/ltcg/difficulty_select_update.json).
//
// Shapes that are load-bearing (each measured against the image):
//
//  * Each confirmed child is a named local in its own block inside the
//    handler: the four share one stack slot (the parameter home) and each
//    search stays a call.  Through an inlined helper the searches inline;
//    as temporaries they get four slots.
//  * The constant selections go through an inlined select helper with one
//    store per path; the computed one calls 0x0040AD20.
//  * The key test 0x0040ACE0 is the real function, inlined here by the
//    compiler and called in the difficulty selection.
#include "th10/game/character_select_update.hpp"

// Select an item, clamped to the last one when the menu has items.
static __forceinline void SelectItem6(MenuCursor& cursor, int index) {
    if (cursor.item_count != 0)
        cursor.selection = index >= cursor.item_count ? cursor.item_count - 1 : index;
    else
        cursor.selection = index;
}

// MenuCursor::DisableItem (0x00434BC0) as it is inlined here.
static __forceinline void DisableItem3(MenuCursor& cursor, int item) {
    cursor.disabled_items[cursor.disabled_count] = item;
    ++cursor.disabled_count;
}

#pragma code_seg(".text$004306a0_fn")
__declspec(noinline) int __stdcall TitleMode7(Title* room) {
    switch (room->phase) {
    case 0:
        room->cursor.item_count = 2;
        if (g_globals_difficulty == 4) {
            ScoreFile3* score = g_score;
            if (!score->cleared[0][0] && !score->cleared[0][1] && !score->cleared[0][2]) {
                if (room->cursor.selection == 0)
                    SelectItem6(room->cursor, 1);
                DisableItem3(room->cursor, 0);
            }
            if (!score->cleared[1][0] && !score->cleared[1][1] && !score->cleared[1][2]) {
                if (room->cursor.selection == 1)
                    SelectItem6(room->cursor, 0);
                DisableItem3(room->cursor, 1);
            }
        }
        RecoveryMusicInstallSlot(room, 99);
        room->ClearAnimationSlot(125);
        RecoveryMusicInstallSlot(room, 125);
        AnimationManager_SetStopFrameAndRun(
            3, reinterpret_cast<RecoveryLookupContext*>(g_sprt_ctrl),
            *reinterpret_cast<RecoveryScriptId*>(&room->animation_slots[125]));
        room->SetSlotFrame(125, room->cursor.selection + 0x11);
        room->SetTimerTarget(1);
    case 1:
        if (room->timer.current > 6)
            room->SetTimerTarget(2);
        break;
    case 2: {
        MenuCursor* cursor = &room->cursor;
        cursor->previous_selection = cursor->selection;
        if ((short)g_input_keys_raw.InputMaskActive(0x40)) cursor->Advance(-1);
        if ((short)g_input_keys_raw.InputMaskActive(0x80)) cursor->Advance(1);
        if (cursor->previous_selection != cursor->selection) {
            g_sound_manager.Queue(12, 0);
            reinterpret_cast<TitleAnimationSlotView*>(room)->RestartSlot(125);
            room->SetSlotFrame(125, cursor->selection + 7);
        }
        if (g_input_keys_held & 0xa) {
            room->SetTimerTarget(4);
            g_sound_manager.Queue(11, 0);
        } else if (g_input_keys_held & 0x1001) {
            AnimationHandle15* handle =
                reinterpret_cast<AnimationHandle15*>(&room->animation_slots[125]);
            {
                AnimationRef2 child = handle->FindChildRef(cursor->selection + 0x79);
                reinterpret_cast<AnimationHandle11*>(&child)->SetStopFrame(6);
            }
            {
                AnimationRef2 child = handle->FindChildRef(room->cursor.selection + 0x7b);
                reinterpret_cast<AnimationHandle11*>(&child)->SetStopFrame(6);
            }
            {
                AnimationRef2 child = handle->FindChildRef(0x7a - room->cursor.selection);
                reinterpret_cast<AnimationHandle11*>(&child)->SetStopFrame(1);
            }
            {
                AnimationRef2 child = handle->FindChildRef(0x7c - room->cursor.selection);
                reinterpret_cast<AnimationHandle11*>(&child)->SetStopFrame(1);
            }
            g_sound_manager.Queue(10, 0);
            room->SetTimerTarget(3);
        }
        break;
    }
    case 3:
        if (room->timer.current >= 14) {
            room->ClearAnimationSlot(99);
            room->DisableTimerWithOwner(8);
            int character = room->cursor.selection;
            int previous = g_globals_character;
            g_globals_character = character;
            room->cursor.PushSelection();
            room->cursor.item_count = 3;
            if (previous != character)
                SelectItem6(room->cursor, 0);
            else
                UpdateBoundedCounter(g_globals_shot_type, reinterpret_cast<unsigned int*>(&room->cursor));
        }
        break;
    case 4:
        if (room->timer.current >= 6) {
            room->ClearAnimationSlot(125);
            room->ClearAnimationSlot(99);
            room->DisableTimerWithOwner(6);
            g_globals_character = room->cursor.selection;
            room->cursor.PopSelection();
        }
        break;
    }
    return 1;
}
#pragma code_seg()
