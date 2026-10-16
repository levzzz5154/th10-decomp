// 0x00430A60..0x00430FEF: shot type selection screen of the title menu (and
// its five-entry phase table).
//
// Phase 0 offers the three shot types of the chosen character; for the extra
// stage a shot type that has not cleared the game is disabled and the cursor
// moved to one that has.  It installs and starts the character's selection
// animation, clears the hidden flag of the "cleared" mark of each shot type
// that has no clear on the chosen difficulty, and runs phase 1 on the same
// frame.  Phase 1 waits seven frames.  Phase 2 moves the cursor and handles
// cancel and confirm.  Phase 3 starts the fade at frame 10 and after forty
// frames starts the game (stage 1, or the extra stage 7), or for practice
// goes on to the stage selection.  Phase 4 goes back to the character
// selection after six frames.
//
// The room is a stack argument; the handler is linked with the title
// dispatcher and the real bodies of its leaves
// (build_support/layout/ltcg/difficulty_select_update.json).  The chosen
// character is read from its global at every use, as in the image.
#include "th10/game/shot_type_select_update.hpp"

// Select an item, clamped to the last one when the menu has items.
static __forceinline void SelectItem7(MenuCursor& cursor, int index) {
    if (cursor.item_count != 0)
        cursor.selection = index >= cursor.item_count ? cursor.item_count - 1 : index;
    else
        cursor.selection = index;
}

// MenuCursor::DisableItem (0x00434BC0) as it is inlined here.
static __forceinline void DisableItem4(MenuCursor& cursor, int item) {
    cursor.disabled_items[cursor.disabled_count] = item;
    ++cursor.disabled_count;
}

#pragma code_seg(".text$00430a60_fn")
__declspec(noinline) int __stdcall TitleMode8(Title* room) {
    switch (room->phase) {
    case 0:
        room->cursor.item_count = 3;
        if (g_globals_difficulty == 4) {
            ScoreFile4* score = g_score;
            if (!score->cleared[g_globals_character][0]) {
                if (room->cursor.selection == 0) {
                    if (score->cleared[g_globals_character][1])
                        SelectItem7(room->cursor, 1);
                    else
                        SelectItem7(room->cursor, 2);
                }
                DisableItem4(room->cursor, 0);
            }
            if (!score->cleared[g_globals_character][1]) {
                if (room->cursor.selection == 1) {
                    if (score->cleared[g_globals_character][0])
                        SelectItem7(room->cursor, 0);
                    else
                        SelectItem7(room->cursor, 2);
                }
                DisableItem4(room->cursor, 1);
            }
            if (!score->cleared[g_globals_character][2]) {
                if (room->cursor.selection == 2) {
                    if (score->cleared[g_globals_character][0])
                        SelectItem7(room->cursor, 0);
                    else
                        SelectItem7(room->cursor, 1);
                }
                DisableItem4(room->cursor, 2);
            }
        }
        RecoveryMusicInstallSlot(room, 100);
        room->ClearAnimationSlot(g_globals_character + 150);
        RecoveryMusicInstallSlot(room, g_globals_character + 150);
        AnimationManager_SetStopFrameAndRun(
            3, reinterpret_cast<RecoveryLookupContext*>(g_sprt_ctrl),
            *reinterpret_cast<RecoveryScriptId*>(&room->animation_slots[g_globals_character + 150]));
        room->SetSlotFrame(g_globals_character + 150, room->cursor.selection + 0x11);
        room->SetTimerTarget(1);
        if (g_score->shots[g_globals_character][0].clears[g_globals_difficulty] == 0) {
            AnimationRef2 child = reinterpret_cast<AnimationHandle15*>(
                &room->animation_slots[g_globals_character + 150])->FindChildRef(g_globals_character * 3 + 0x8a);
            reinterpret_cast<AnimationHandle12*>(&child)->ClearFlag();
        }
        if (g_score->shots[g_globals_character][1].clears[g_globals_difficulty] == 0) {
            AnimationRef2 child = reinterpret_cast<AnimationHandle15*>(
                &room->animation_slots[g_globals_character + 150])->FindChildRef(g_globals_character * 3 + 0x8b);
            reinterpret_cast<AnimationHandle12*>(&child)->ClearFlag();
        }
        if (g_score->shots[g_globals_character][2].clears[g_globals_difficulty] == 0) {
            AnimationRef2 child = reinterpret_cast<AnimationHandle15*>(
                &room->animation_slots[g_globals_character + 150])->FindChildRef(g_globals_character * 3 + 0x8c);
            reinterpret_cast<AnimationHandle12*>(&child)->ClearFlag();
        }
    case 1:
        if (room->timer.current > 6)
            room->SetTimerTarget(2);
        break;
    case 2: {
        MenuCursor* cursor = &room->cursor;
        cursor->previous_selection = cursor->selection;
        if ((short)g_input_keys_raw.InputMaskActive(0x10)) cursor->Advance(-1);
        if ((short)g_input_keys_raw.InputMaskActive(0x20)) cursor->Advance(1);
        if (cursor->previous_selection != cursor->selection) {
            g_sound_manager.Queue(12, 0);
            reinterpret_cast<TitleAnimationSlotView*>(room)->RestartSlot(g_globals_character + 150);
            room->SetSlotFrame(g_globals_character + 150, cursor->selection + 7);
        }
        if (g_input_keys_held & 0xa) {
            room->SetTimerTarget(4);
            g_sound_manager.Queue(11, 0);
        } else if (g_input_keys_held & 0x1001) {
            room->SetTimerTarget(3);
            g_sound_manager.Queue(10, 0);
            AnimationRef2 child = reinterpret_cast<AnimationHandle15*>(
                &room->animation_slots[g_globals_character + 150])->FindChildRef(
                    cursor->selection + (g_globals_character * 3 + 0x3f) * 2);
            reinterpret_cast<AnimationHandle11*>(&child)->SetStopFrame(6);
        }
        break;
    }
    case 3:
        if (room->timer.current == 10) {
            if ((g_globals_flags & 0x10) == 0) {
                g_ascii_manager->EnsureAnimationResource(480.0f, 392.0f);
                RecoveryAscii_Create(0x2b, 5, 0x20, 0, 0, 0);
            } else {
                g_globals_shot_type = room->cursor.selection;
                room->cursor.PushSelection();
                room->ClearAnimationSlot(100);
                room->DisableTimerWithOwner(9);
            }
        }
        if (room->timer.current >= 40) {
            g_globals_shot_type = room->cursor.selection;
            room->cursor.PushSelection();
            if ((g_globals_flags & 0x10) == 0) {
                room->DisableTimerWithOwner(3);
                if (g_globals_difficulty < 4) {
                    g_stage_route_current = g_stage_routes + 1 * 0x30;
                    g_globals_stage = 1;
                    g_globals_stage_shown = 1;
                } else {
                    g_stage_route_current = g_stage_routes + 7 * 0x30;
                    g_globals_stage = 7;
                    g_globals_stage_shown = 7;
                }
                g_main_state = 7;
                Music_FadeOut(6.0f);
            } else {
                room->ClearAnimationSlot(100);
                room->DisableTimerWithOwner(9);
            }
        }
        break;
    case 4:
        if (room->timer.current >= 6) {
            room->ClearAnimationSlot(g_globals_character + 150);
            room->ClearAnimationSlot(100);
            room->DisableTimerWithOwner(7);
            room->cursor.PopSelection();
        }
        break;
    }
    return 1;
}
#pragma code_seg()
