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
// (layout/ltcg/difficulty_select_update_00430320.json).  The chosen
// character is read from its global at every use, as in the image.
#include "th10/game/shot_type_select_update_00430a60.hpp"

// Select an item, clamped to the last one when the menu has items.
static __forceinline void SelectItem_00430a60(MenuCursor& cursor, int index) {
    if (cursor.item_count != 0)
        cursor.selection = index >= cursor.item_count ? cursor.item_count - 1 : index;
    else
        cursor.selection = index;
}

// MenuCursor::DisableItem (0x00434BC0) as it is inlined here.
static __forceinline void DisableItem_00430a60(MenuCursor& cursor, int item) {
    cursor.disabled_items[cursor.disabled_count] = item;
    ++cursor.disabled_count;
}

#pragma code_seg(".text$00430a60_fn")
__declspec(noinline) int __stdcall TitleMode8_00430a60(RecoveryMusicRoom_00433ef0* room) {
    switch (room->phase) {
    case 0:
        room->cursor.item_count = 3;
        if (data_00474c74 == 4) {
            ScoreFile_00430a60* score = data_0047783c;
            if (!score->cleared[data_00474c68][0]) {
                if (room->cursor.selection == 0) {
                    if (score->cleared[data_00474c68][1])
                        SelectItem_00430a60(room->cursor, 1);
                    else
                        SelectItem_00430a60(room->cursor, 2);
                }
                DisableItem_00430a60(room->cursor, 0);
            }
            if (!score->cleared[data_00474c68][1]) {
                if (room->cursor.selection == 1) {
                    if (score->cleared[data_00474c68][0])
                        SelectItem_00430a60(room->cursor, 0);
                    else
                        SelectItem_00430a60(room->cursor, 2);
                }
                DisableItem_00430a60(room->cursor, 1);
            }
            if (!score->cleared[data_00474c68][2]) {
                if (room->cursor.selection == 2) {
                    if (score->cleared[data_00474c68][0])
                        SelectItem_00430a60(room->cursor, 0);
                    else
                        SelectItem_00430a60(room->cursor, 1);
                }
                DisableItem_00430a60(room->cursor, 2);
            }
        }
        RecoveryMusicInstallSlot_0042c670(room, 100);
        room->ClearAnimationSlot(data_00474c68 + 150);
        RecoveryMusicInstallSlot_0042c670(room, data_00474c68 + 150);
        AnimationManager_SetStopFrameAndRun(
            3, reinterpret_cast<RecoveryLookupContext_0040bd80*>(data_00491c10),
            *reinterpret_cast<RecoveryScriptId_0040bd80*>(&room->animation_slots[data_00474c68 + 150]));
        room->SetSlotFrame(data_00474c68 + 150, room->cursor.selection + 0x11);
        room->SetTimerTarget(1);
        if (data_0047783c->shots[data_00474c68][0].clears[data_00474c74] == 0) {
            AnimationRef_004497d0 child = reinterpret_cast<AnimationHandle_004497d0*>(
                &room->animation_slots[data_00474c68 + 150])->FindChildRef(data_00474c68 * 3 + 0x8a);
            reinterpret_cast<AnimationHandle_004495e0*>(&child)->ClearFlag();
        }
        if (data_0047783c->shots[data_00474c68][1].clears[data_00474c74] == 0) {
            AnimationRef_004497d0 child = reinterpret_cast<AnimationHandle_004497d0*>(
                &room->animation_slots[data_00474c68 + 150])->FindChildRef(data_00474c68 * 3 + 0x8b);
            reinterpret_cast<AnimationHandle_004495e0*>(&child)->ClearFlag();
        }
        if (data_0047783c->shots[data_00474c68][2].clears[data_00474c74] == 0) {
            AnimationRef_004497d0 child = reinterpret_cast<AnimationHandle_004497d0*>(
                &room->animation_slots[data_00474c68 + 150])->FindChildRef(data_00474c68 * 3 + 0x8c);
            reinterpret_cast<AnimationHandle_004495e0*>(&child)->ClearFlag();
        }
    case 1:
        if (room->timer.current > 6)
            room->SetTimerTarget(2);
        break;
    case 2: {
        MenuCursor* cursor = &room->cursor;
        cursor->previous_selection = cursor->selection;
        if ((short)data_00474e30.InputMaskActive(0x10)) cursor->Advance(-1);
        if ((short)data_00474e30.InputMaskActive(0x20)) cursor->Advance(1);
        if (cursor->previous_selection != cursor->selection) {
            data_00492590.Queue(12, 0);
            reinterpret_cast<AnimationSlotOwner_0042c750*>(room)->RestartSlot(data_00474c68 + 150);
            room->SetSlotFrame(data_00474c68 + 150, cursor->selection + 7);
        }
        if (data_00474e36 & 0xa) {
            room->SetTimerTarget(4);
            data_00492590.Queue(11, 0);
        } else if (data_00474e36 & 0x1001) {
            room->SetTimerTarget(3);
            data_00492590.Queue(10, 0);
            AnimationRef_004497d0 child = reinterpret_cast<AnimationHandle_004497d0*>(
                &room->animation_slots[data_00474c68 + 150])->FindChildRef(
                    cursor->selection + (data_00474c68 * 3 + 0x3f) * 2);
            reinterpret_cast<AnimationHandle_00449470*>(&child)->SetStopFrame(6);
        }
        break;
    }
    case 3:
        if (room->timer.current == 10) {
            if ((data_00474ca0 & 0x10) == 0) {
                data_004776e0->EnsureAnimationResource(480.0f, 392.0f);
                RecoveryAscii_Create_0043c8b0(0x2b, 5, 0x20, 0, 0, 0);
            } else {
                data_00474c6c = room->cursor.selection;
                room->cursor.PushSelection();
                room->ClearAnimationSlot(100);
                room->DisableTimerWithOwner(9);
            }
        }
        if (room->timer.current >= 40) {
            data_00474c6c = room->cursor.selection;
            room->cursor.PushSelection();
            if ((data_00474ca0 & 0x10) == 0) {
                room->DisableTimerWithOwner(3);
                if (data_00474c74 < 4) {
                    data_00477848 = data_00474788 + 1 * 0x30;
                    data_00474c7c = 1;
                    data_00474c80 = 1;
                } else {
                    data_00477848 = data_00474788 + 7 * 0x30;
                    data_00474c7c = 7;
                    data_00474c80 = 7;
                }
                data_00491fb8 = 7;
                Music_FadeOut(6.0f);
            } else {
                room->ClearAnimationSlot(100);
                room->DisableTimerWithOwner(9);
            }
        }
        break;
    case 4:
        if (room->timer.current >= 6) {
            room->ClearAnimationSlot(data_00474c68 + 150);
            room->ClearAnimationSlot(100);
            room->DisableTimerWithOwner(7);
            room->cursor.PopSelection();
        }
        break;
    }
    return 1;
}
#pragma code_seg()
