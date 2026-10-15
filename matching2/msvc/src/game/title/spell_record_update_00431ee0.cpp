// 0x00431EE0..0x0043268F: spell card record screen of the title menu (and its
// four-entry phase table).
//
// Phase 0 builds the screen for the first shot type and the Normal difficulty
// and runs phase 1 on the same frame.  Phase 1 waits seven frames.  Phase 2
// moves between difficulties (left/right) and shot types (up/down); confirm
// steps through the pages of ten cards, the first page being the summary.
// With Extra and the third shot type selected, typing the 22-key sequence on
// the keyboard unlocks every stage.  Cancel leaves through phase 3, which
// returns to the main menu after six frames.
//
// The room is a stack argument; the handler is linked with the title
// dispatcher and the real bodies of its leaves
// (build_support/layout/ltcg/difficulty_select_update_00430320.json).
#include <string.h>

#include "th10/game/spell_record_update_00431ee0.hpp"

// Select an item, clamped to the last one when the menu has items.
static __forceinline void SelectItem_00431ee0(MenuCursor& cursor, int index) {
    if (cursor.item_count != 0)
        cursor.selection = index >= cursor.item_count ? cursor.item_count - 1 : index;
    else
        cursor.selection = index;
}

// The number of pages a difficulty needs: the summary and ten cards a page.
static __forceinline int PageCount_00431ee0(int difficulty) {
    return (SpellCards_CountOfDifficulty_004088c0(difficulty) + 9) / 10 + 1;
}

// The animation a handle refers to, searching both of the manager's lists
// (0x004491C0 as it is inlined in phase 2).
static __forceinline RecoveryMusicVm_00433ef0* FindAnimation_00431ee0(
        RecoveryLookupContext_0040bd80* context, unsigned int handle) {
    if (handle == 0)
        return 0;
    RecoveryLookupNode_0040bd80* node;
    for (node = context->primary; node != 0; node = node->next)
        if (reinterpret_cast<RecoveryMusicVm_00433ef0*>(node->object)->id == handle)
            return reinterpret_cast<RecoveryMusicVm_00433ef0*>(node->object);
    for (node = context->secondary; node != 0; node = node->next)
        if (reinterpret_cast<RecoveryMusicVm_00433ef0*>(node->object)->id == handle)
            return reinterpret_cast<RecoveryMusicVm_00433ef0*>(node->object);
    return 0;
}

// Stop an animation and its children at a frame.
static __forceinline void SetTreeFrame_00431ee0(RecoveryMusicVm_00433ef0* object, unsigned short frame) {
    if (object != 0) {
        object->stop_frame = frame;
        if (object->children_flagged == 0) {
            for (RecoveryMusicChild_00433ef0* child = object->children; child != 0; child = child->next)
                child->object->stop_frame = frame;
        }
    }
}

#pragma code_seg(".text$00431ee0_fn")
__declspec(noinline) int __stdcall TitleMode11_00431ee0(Title* room) {
    TitleSpellRecordView* records = reinterpret_cast<TitleSpellRecordView*>(room);
    void* handle;
    void* line_handle;
    switch (room->phase) {
    case 0: {
        room->cursor.item_count = 6;
        SelectItem_00431ee0(room->cursor, 0);
        records->difficulty.item_count = 5;
        SelectItem_00431ee0(records->difficulty, 1);
        records->difficulty.wrap = 1;
        records->page.item_count = PageCount_00431ee0(records->difficulty.selection);
        SelectItem_00431ee0(records->page, 0);
        MenuCursor* page = &records->page;
        page->wrap = 1;
        if (reinterpret_cast<RecoveryLookup_0040bd80*>(g_sprt_ctrl)->Find(
                reinterpret_cast<RecoveryLookupContext_0040bd80*>(g_sprt_ctrl),
                *reinterpret_cast<RecoveryScriptId_0040bd80*>(&room->animation_slots[94])) == 0) {
            RecoveryMusicInstallSlot_0042c670(room, 94);
            void* resource = g_ascii_manager->animation_resource;
            void** result = AnimationManager_CreatePrimaryBack_00448d00(resource, &handle, 8, 15);
            room->fallback_handle.value = reinterpret_cast<unsigned int>(*result);
        }
        RecoveryMusicInstallSlot_0042c670(room, 102);
        room->SetTimerTarget(1);
        RecoveryMusicInstallSlot_0042c670(room, room->cursor.selection / 3 + 152);
        RecoveryMusicInstallSlot_0042c670(room, room->cursor.selection + 154);
        RecoveryMusicInstallSlot_0042c670(room, records->difficulty.selection + 160);
        RecoveryMusicInstallSlot_0042c670(room, 168);
        RecoveryMusicInstallSlot_0042c670(room, 169);
        RecoveryMusicInstallSlot_0042c670(room, 170);
        RecoveryMusicInstallSlot_0042c670(room, 171);
        RecoveryMusicInstallSlot_0042c670(room, 165);
        RecoveryMusicInstallSlot_0042c670(room, 166);
        RecoveryMusicInstallSlot_0042c670(room, 167);
        RecoveryMusicInstallSlot_0042c670(room, 172);
    }
    case 1:
        if (room->timer.current > 6)
            room->SetTimerTarget(2);
        break;
    case 2: {
        room->cursor.previous_selection = room->cursor.selection;
        MenuCursor* difficulty = &records->difficulty;
        difficulty->previous_selection = difficulty->selection;
        records->page.previous_selection = records->page.selection;
        if ((short)data_00474e30.InputMaskActive(0x10)) {
            difficulty->Advance(-1);
            AnimationManager_SetStopFrameAndRun(
                2, reinterpret_cast<RecoveryLookupContext_0040bd80*>(g_sprt_ctrl),
                *reinterpret_cast<RecoveryScriptId_0040bd80*>(&room->animation_slots[170]));
        }
        if ((short)data_00474e30.InputMaskActive(0x20)) {
            difficulty->Advance(1);
            AnimationManager_SetStopFrameAndRun(
                2, reinterpret_cast<RecoveryLookupContext_0040bd80*>(g_sprt_ctrl),
                *reinterpret_cast<RecoveryScriptId_0040bd80*>(&room->animation_slots[171]));
        }
        if (difficulty->previous_selection != difficulty->selection) {
            g_sound_manager.Queue(12, 0);
            room->ClearAnimationSlot(records->difficulty.previous_selection + 160);
            RecoveryMusicInstallSlot_0042c670(room, difficulty->selection + 160);
            if (records->page.selection > 0) {
                SelectItem_00431ee0(records->page, 1);
                reinterpret_cast<TitleDrawView*>(room)->BuildSpellList();
            }
            records->page.item_count = PageCount_00431ee0(difficulty->selection);
        }
        if ((short)data_00474e30.InputMaskActive(0x40)) {
            room->cursor.Advance(-1);
            AnimationManager_SetStopFrameAndRun(
                2, reinterpret_cast<RecoveryLookupContext_0040bd80*>(g_sprt_ctrl),
                *reinterpret_cast<RecoveryScriptId_0040bd80*>(&room->animation_slots[168]));
        }
        if ((short)data_00474e30.InputMaskActive(0x80)) {
            room->cursor.Advance(1);
            AnimationManager_SetStopFrameAndRun(
                2, reinterpret_cast<RecoveryLookupContext_0040bd80*>(g_sprt_ctrl),
                *reinterpret_cast<RecoveryScriptId_0040bd80*>(&room->animation_slots[169]));
        }
        if (room->cursor.previous_selection != room->cursor.selection) {
            g_sound_manager.Queue(12, 0);
            if (room->cursor.selection / 3 != room->cursor.previous_selection / 3) {
                room->ClearAnimationSlot(room->cursor.previous_selection / 3 + 152);
                RecoveryMusicInstallSlot_0042c670(room, room->cursor.selection / 3 + 152);
            }
            room->ClearAnimationSlot(room->cursor.previous_selection + 154);
            RecoveryMusicInstallSlot_0042c670(room, room->cursor.selection + 154);
            if (records->page.selection > 0)
                reinterpret_cast<TitleDrawView*>(room)->BuildSpellList();
        }
        if (data_00474e36 & 0x1001) {
            if (records->page.selection == 0) {
                int line = 0;
                do {
                    void* resource = g_ascii_manager->text_resource;
                    void** result = AnimationManager_CreatePrimaryBack_00448d00(resource, &line_handle, line + 23, 15);
                    records->lines[line].value = reinterpret_cast<unsigned int>(*result);
                    ++line;
                } while (line < 10);
            }
            MenuCursor* page = &records->page;
            page->Advance(1);
            if (page->selection == 0) {
                for (int line = 0; line < 10; ++line)
                    RecoveryMusicStopHandle_00409e50(&records->lines[line]);
            } else {
                reinterpret_cast<TitleDrawView*>(room)->BuildSpellList();
            }
            g_sound_manager.Queue(10, 0);
        }
        if (records->difficulty.selection == 4 && room->cursor.selection == 2) {
            // Any game key restarts the sequence.
            if (data_00474e36 & 0x160b) {
                data_004979a4 = 0;
                data_004979a0 = 0;
            }
            memcpy(data_00497d90, data_00497e90, sizeof(data_00497d90));
            if (Input_UpdateKeyboardState(data_00497e90)) {
                for (int key = 0; key < 256; ++key)
                    data_004979a8[key] = (data_00497d90[key] ^ data_00497e90[key]) & data_00497e90[key];
                if (data_004979a4 >= 22) {
                    UnlockAllStages_0042c8c0(reinterpret_cast<GameProgress_0042c8c0*>(data_0047783c));
                    g_sound_manager.Queue(44, 0);
                    data_004979a4 = 0;
                } else if (data_004979a8[data_0046ef10[data_004979a4]] & 0x80) {
                    ++data_004979a4;
                    data_004979a0 = 0;
                } else {
                    unsigned char any = 0;
                    for (int key = 0; key < 57; ++key)
                        any |= data_004979a8[key];
                    if (any & 0x80)
                        data_004979a4 = 0;
                }
            }
            ++data_004979a0;
            if (data_004979a0 > 300) {
                data_004979a4 = 0;
                data_004979a0 = 0;
            }
        }
        if (data_00474e36 & 0xa) {
            room->SetTimerTarget(3);
            g_sound_manager.Queue(11, 0);
            room->ClearAnimationSlot(records->difficulty.selection + 160);
            room->ClearAnimationSlot(room->cursor.selection + 154);
            room->ClearAnimationSlot(room->cursor.selection / 3 + 152);
            room->ClearAnimationSlot(168);
            room->ClearAnimationSlot(169);
            room->ClearAnimationSlot(170);
            room->ClearAnimationSlot(171);
            room->ClearAnimationSlot(165);
            room->ClearAnimationSlot(166);
            room->ClearAnimationSlot(167);
            room->ClearAnimationSlot(172);
            for (int line = 0; line < 10; ++line)
                SetTreeFrame_00431ee0(
                    FindAnimation_00431ee0(reinterpret_cast<RecoveryLookupContext_0040bd80*>(g_sprt_ctrl),
                                           records->lines[line].value), 1);
        }
        break;
    }
    case 3:
        if (room->timer.current >= 6) {
            room->ClearAnimationSlot(102);
            room->SetSlotFrame(90, 8);
            room->SetSlotFrame(91, 8);
            room->ClearAnimationSlot(94);
            RecoveryMusicStopHandle_00409e50(&room->fallback_handle);
            room->DisableTimerWithOwner(2);
            room->cursor.PopSelection();
        }
        break;
    }
    return 1;
}
#pragma code_seg()
