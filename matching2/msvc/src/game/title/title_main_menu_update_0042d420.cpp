// 0x0042D420..0x0042D91F: main menu of the title screen (its five-entry
// phase table and the two eight-entry item tables).
//
// Phase 0 offers the eight items (the extra start is disabled until some
// shot type has cleared the game), puts the cursor on "practice" when the
// game comes back from one, installs the backdrop and the cursor animation
// and runs phase 1 on the same frame.  Phase 1 waits eleven frames and starts
// the cursor animation.  Phase 2 moves the cursor; cancel moves it to "quit"
// (and quits when it is already there), confirm starts the leaving animation
// of the chosen item.  Phase 4 opens the chosen screen after twenty frames.
//
// The room arrives in EBX from the title dispatcher (0x0042CDF0); the handler
// is linked with the dispatcher and the real bodies of its leaves
// (build_support/layout/ltcg/difficulty_select_update_00430320.json).
//
// Shapes that are load-bearing (each measured against the image):
//
//  * Cancel on "quit" jumps into the quit case of the confirm switch.  As a
//    second copy of the two calls the sound request is hoisted above the
//    selection test.
//  * The room is loaded again for the slot restart that follows
//    SetTimerTarget in the "replay" case although that function leaves EAX
//    alone: SetTimerTarget is defined in the room's class, and the compiler
//    keeps no register summary for the out-of-line copy of an in-class member.
#include "th10/game/title_main_menu_update_0042d420.hpp"

// Select an item, clamped to the last one when the menu has items.
static __forceinline void SelectItem_0042d420(MenuCursor& cursor, int index) {
    if (cursor.item_count != 0)
        cursor.selection = index >= cursor.item_count ? cursor.item_count - 1 : index;
    else
        cursor.selection = index;
}

// MenuCursor::DisableItem (0x00434BC0) as it is inlined here.
static __forceinline void DisableItem_0042d420(MenuCursor& cursor, int item) {
    cursor.disabled_items[cursor.disabled_count] = item;
    ++cursor.disabled_count;
}

// Restart the cursor animation of slot 0.
static __forceinline void RunCursorSlot_0042d420(Title* room) {
    AnimationManager_SetStopFrameAndRun(
        3, reinterpret_cast<RecoveryLookupContext_0040bd80*>(g_sprt_ctrl),
        *reinterpret_cast<RecoveryScriptId_0040bd80*>(&room->animation_slots[0]));
}

#pragma code_seg(".text$0042d420_fn")
__declspec(noinline) int __stdcall TitleMainMenu_0042d420(Title* room) {
    switch (room->phase) {
    case 0:
        room->cursor.item_count = 8;
        if (!reinterpret_cast<ScoreFileProgress_0042c850*>(data_0047783c)->HasAnyClear())
            DisableItem_0042d420(room->cursor, 1);
        if (data_00474ca0 & 0x10) {
            SelectItem_0042d420(room->cursor, 2);
            data_00474ca0 &= ~0x10u;
        }
        if (reinterpret_cast<RecoveryLookup_0040bd80*>(g_sprt_ctrl)->Find(
                reinterpret_cast<RecoveryLookupContext_0040bd80*>(g_sprt_ctrl),
                *reinterpret_cast<RecoveryScriptId_0040bd80*>(&room->animation_slots[88])) == 0)
            RecoveryMusicInstallSlot_0042c670(room, 88);
        RecoveryMusicInstallSlot_0042c670(room, 0);
        room->SetTimerTarget(1);
    case 1:
        if (room->timer.current > 10) {
            room->SetTimerTarget(2);
            RunCursorSlot_0042d420(room);
            room->SetSlotFrame(0, room->cursor.selection + 0x11);
        }
        break;
    case 2: {
        MenuCursor* cursor = &room->cursor;
        cursor->previous_selection = cursor->selection;
        if ((short)data_00474e30.InputMaskActive(0x10)) cursor->Advance(-1);
        if ((short)data_00474e30.InputMaskActive(0x20)) cursor->Advance(1);
        if (cursor->previous_selection != cursor->selection) {
            data_00492590.Queue(12, 0);
            RunCursorSlot_0042d420(room);
            room->SetSlotFrame(0, cursor->selection + 7);
        }
        if (data_00474e36 & 0xa) {
            if (cursor->selection == 7)
                goto quit;
            data_00492590.Queue(11, 0);
            SelectItem_0042d420(*cursor, 7);
            reinterpret_cast<TitleAnimationSlotView*>(room)->RestartSlot(0);
            room->SetSlotFrame(0, cursor->selection + 7);
        }
        if (data_00474e36 & 0x1001) {
            room->SetSlotFrame(0, 6);
            switch (cursor->selection) {
            case 0:
            case 1:
            case 2:
            case 3:
            case 4:
                data_00492590.Queue(10, 0);
                room->SetSlotFrame(0x5a, 7);
                room->SetSlotFrame(0x5b, 7);
                room->SetTimerTarget(4);
                break;
            case 5:
                data_00492590.Queue(10, 0);
                room->SetSlotFrame(0x5a, 7);
                room->SetSlotFrame(0x5b, 7);
                room->SetTimerTarget(4);
                data_00492590.Queue(10, 0);
                break;
            case 6:
                data_00492590.Queue(10, 0);
                room->SetTimerTarget(4);
                reinterpret_cast<TitleAnimationSlotView*>(room)->RestartSlot(0x5a);
                reinterpret_cast<TitleAnimationSlotView*>(room)->RestartSlot(0x5b);
                break;
            case 7:
            quit:
                data_00492590.Queue(11, 0);
                room->SetTimerTarget(4);
                break;
            }
        }
        break;
    }
    case 4:
        if (room->timer.current >= 20) {
            MenuCursor* cursor = &room->cursor;
            switch (cursor->selection) {
            case 0:
                data_00474ca0 &= ~0x10u;
                room->ClearAnimationSlot(88);
                room->DisableTimerWithOwner(6);
                cursor->PushSelection();
                if (data_00474c74 >= 4)
                    data_00474c74 = 1;
                UpdateBoundedCounter(data_00474c74, reinterpret_cast<unsigned int*>(cursor));
                break;
            case 1:
                data_00474ca0 &= ~0x10u;
                room->ClearAnimationSlot(88);
                room->DisableTimerWithOwner(6);
                cursor->PushSelection();
                reinterpret_cast<TitleDifficultyView*>(room)->saved_difficulty = data_00474c74;
                data_00474c74 = 4;
                SelectItem_0042d420(*cursor, 0);
                break;
            case 2:
                data_00474ca0 |= 0x10;
                room->ClearAnimationSlot(88);
                room->DisableTimerWithOwner(6);
                cursor->PushSelection();
                if (data_00474c74 >= 4)
                    data_00474c74 = 1;
                UpdateBoundedCounter(data_00474c74, reinterpret_cast<unsigned int*>(cursor));
                break;
            case 3:
                room->ClearAnimationSlot(88);
                room->DisableTimerWithOwner(12);
                cursor->PushSelection();
                break;
            case 4:
                room->ClearAnimationSlot(88);
                room->DisableTimerWithOwner(11);
                cursor->PushSelection();
                break;
            case 5:
                room->ClearAnimationSlot(88);
                room->DisableTimerWithOwner(14);
                cursor->PushSelection();
                break;
            case 6:
                room->DisableTimerWithOwner(4);
                cursor->PushSelection();
                break;
            case 7:
                room->DisableTimerWithOwner(3);
                break;
            }
        }
        break;
    }
    return 1;
}
#pragma code_seg()
